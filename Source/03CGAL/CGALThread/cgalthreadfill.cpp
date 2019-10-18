// 01 frame includes
#include "cgalthreadfill.h"

// C++ includes
#include <fstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/foreach.hpp>

// CGAL includes
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/read_vtk_image_data.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/triangulate_hole.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

// VTK includes
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkThreshold.h>
#include <vtkPropPicker.h>
#include <vtkNamedColors.h>
#include <vtkGenericCell.h>
#include <vtkCellIterator.h>
#include <vtkAppendFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkTriangleFilter.h>
#include <vtkGeometryFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkFillHolesFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkUnstructuredGrid.h>
#include <vtkConnectivityFilter.h>

CGALThreadFill::CGALThreadFill(QObject *parent) :
    CGALThread(parent) {
    this->polydata_ = nullptr;
}

CGALThreadFill::~CGALThreadFill() {
}

void CGALThreadFill::doWork() {
    STL2OFF("fill.off", 0);
    STL2OFF("fill_region.off", 1);
    if (CGALFunctionFill()) {
        OFF2STL("fill.off");
        this->SetResult(true);
    } else {
        this->SetResult(false);
    }
}

void CGALThreadFill::SetSurface(const vtkSmartPointer<vtkPolyData> value, int num) {
    if (0 == num) {
        this->polydata_ = value;
    } else if (1 == num) {
        this->polydata_region_ = value;
    }
}

vtkSmartPointer<vtkPolyData> CGALThreadFill::GetSurface() {
    return this->polydata_;
}

void CGALThreadFill::run() {
    this->InitialResult();
    this->doWork();
}

bool CGALThreadFill::CGALFunctionFill() {
    typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
    typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;
    typedef Polyhedron::Halfedge_handle    Halfedge_handle;
    typedef Polyhedron::Facet_handle       Facet_handle;
    typedef Polyhedron::Vertex_handle      Vertex_handle;
    typedef Kernel::Point_3 Point;
    typedef Polyhedron::Halfedge_iterator         Iterator;
    std::ifstream input;
    input.open("fill_region.off");
    Polyhedron poly_region;
    if (!(input >> poly_region)) {
        std::cerr << "01 Not a valid off file." << std::endl;
        return false;
    }
    input.close();
    input.open("fill.off");
    Polyhedron poly;
    if (!(input >> poly)) {
        std::cerr << "02 Not a valid off file." << std::endl;
        return false;
    }
    input.close();
    QList<Point> region_list;
    Halfedge_handle region;
    for (Iterator e = poly_region.halfedges_begin();
            e != poly_region.halfedges_end(); ++e) {
        region_list.push_back(e ->vertex()->point());
    }
    BOOST_FOREACH(Halfedge_handle h, halfedges(poly)) {
        if (h->is_border()) {
            Point tmp;
            foreach (tmp, region_list) {
                if (h->vertex()->point() == tmp) {
                    std::vector<Facet_handle>  patch_facets;
                    std::vector<Vertex_handle> patch_vertices;
                    if (CGAL::cpp11::get<0>(
                                CGAL::Polygon_mesh_processing::
                                triangulate_refine_and_fair_hole(
                                    poly, h,
                                    std::back_inserter(patch_facets),
                                    std::back_inserter(patch_vertices),
                                    CGAL::Polygon_mesh_processing::parameters::
                                    vertex_point_map(get(CGAL::vertex_point, poly)).
                                    geom_traits(Kernel())))) {
                    }
                    if (patch_facets.size() > 0) {
                        std::ofstream out("fill.off");
                        out << poly ;
                        out.close();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


CGALThreadFillChoice::CGALThreadFillChoice(QObject *parent) : QObject(parent) {
    this->Initial();
}

CGALThreadFillChoice::~CGALThreadFillChoice() {
    if (this->own_renderer_ == true) {
        this->renderer_->deleteLater();
    }
}

void CGALThreadFillChoice::Execute() {
    qDebug();
    if (this->renderer_ == nullptr) {
        this->renderer_ = new CustomVtkRenderer();
        this->renderer_->Execute();
        this->own_renderer_ = true;
    }
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkFillHolesFilter> fill_holes_filter;
    fill_holes_filter->SetInputData(this->surface_);
    fill_holes_filter->SetHoleSize(100000.0);
    fill_holes_filter->Update();
    vtkNew<vtkPolyDataNormals> normals;
    normals->SetInputData(fill_holes_filter->GetOutput());
    normals->ConsistencyOn();
    normals->SplittingOff();
    normals->Update();
    normals->GetOutput()->GetPointData()->SetNormals(
        this->surface_->GetPointData()->GetNormals());
    vtkIdType num_original_cells = this->surface_->GetNumberOfCells();
    vtkIdType num_new_cells = normals->GetOutput()->GetNumberOfCells();
    vtkSmartPointer<vtkCellIterator> it = normals->GetOutput()->NewCellIterator();
    vtkIdType num_cells = 0;
    for (it->InitTraversal();
            !it->IsDoneWithTraversal() && num_cells < num_original_cells;
            it->GoToNextCell(), ++num_cells) {
    }
    vtkNew<vtkPolyData> hole_poly_data;
    hole_poly_data->Allocate(
        normals->GetOutput(), num_new_cells - num_original_cells);
    hole_poly_data->SetPoints(normals->GetOutput()->GetPoints());
    vtkNew<vtkGenericCell> cell;
    for (; !it->IsDoneWithTraversal(); it->GoToNextCell()) {
        it->GetCell(cell);
        hole_poly_data->InsertNextCell(it->GetCellType(), cell->GetPointIds());
    }
    hole_poly_data->Modified();
    vtkNew<vtkConnectivityFilter> connectivity;
    connectivity->SetInputData(hole_poly_data);
    connectivity->SetExtractionModeToAllRegions();
    connectivity->ColorRegionsOn();
    connectivity->Update();
    if (this->first_connect_) {
        connect(this->renderer_, &CustomVtkRenderer::SignalMouseClicked,
                this, &CGALThreadFillChoice::SlotMouseClicked);
        connect(this->renderer_, &CustomVtkRenderer::SignalKeyPressed,
                this, &CGALThreadFillChoice::SlotKeyPressed);
    }
    while (this->filled_actor_list_.size() > 0) {
        vtkSmartPointer<vtkActor> actor = filled_actor_list_.takeFirst();
        this->renderer_->GetRenderer()->RemoveActor(actor);
    }
    this->filled_surface_list_.clear();
    this->fill_id_ = -1;
    for (qint32 i = 0; i < connectivity->GetNumberOfExtractedRegions(); ++i) {
        vtkNew<vtkThreshold> threshold;
        threshold->SetInputData(connectivity->GetOutput());
        threshold->ThresholdBetween(i - 0.5, i + 0.5);
        threshold->SetInputArrayToProcess(0, 0, 0,
                                          vtkDataObject::FIELD_ASSOCIATION_POINTS,
                                          "RegionId");
        threshold->Update();
        vtkNew<vtkGeometryFilter> geometry_filter;
        geometry_filter->SetInputData(threshold->GetOutput());
        geometry_filter->Update();
        vtkNew<vtkTriangleFilter> triangle_filter;
        triangle_filter->SetInputData(geometry_filter->GetOutput());
        triangle_filter->Update();
        vtkNew<vtkCleanPolyData> clean_poly_data;
        clean_poly_data->SetInputData(triangle_filter->GetOutput());
        clean_poly_data->Update();
        this->filled_surface_list_.append(clean_poly_data->GetOutput());
        vtkNew<vtkPolyDataMapper> filled_mapper;
        filled_mapper->SetInputData(geometry_filter->GetOutput());
        filled_mapper->SetScalarRange(geometry_filter->GetOutput()->GetPointData()
                                      ->GetArray("RegionId")->GetRange());
        filled_mapper->SetArrayId(i);
        filled_mapper->ScalarVisibilityOff();
        filled_mapper->Update();
        vtkNew<vtkActor> filled_actor;
        filled_actor->SetMapper(filled_mapper);
        filled_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        this->renderer_->GetRenderer()->AddActor(filled_actor);
        this->filled_actor_list_.append(filled_actor);
    }
    this->enable_ = true;
    this->renderer_->Render();
    if (this->own_renderer_) {
        this->renderer_->Deallocate();
    }
}

void CGALThreadFillChoice::SelectorOff() {
    for (const vtkSmartPointer<vtkActor> &actor : this->filled_actor_list_) {
        this->renderer_->GetRenderer()->RemoveActor(actor);
    }
    this->last_picked_actor_ = nullptr;
    this->last_picked_property_ = vtkSmartPointer<vtkProperty>::New();
    enable_ = false;
}

void CGALThreadFillChoice::SelectorOn() {
    for (const vtkSmartPointer<vtkActor> &actor : this->filled_actor_list_) {
        this->renderer_->GetRenderer()->AddActor(actor);
    }
    enable_ = true;
}

void CGALThreadFillChoice::SetVmtkRenderer(const QPointer<CustomVtkRenderer> value) {
    this->renderer_ = value;
}

void CGALThreadFillChoice::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
    this->result_ = false;
    this->surface_ = value;
}

vtkSmartPointer<vtkPolyData> CGALThreadFillChoice::GetSurface() {
    return this->surface_;
}

qint32 CGALThreadFillChoice::GetFillCount() {
    return this->filled_actor_list_.size();
}

bool CGALThreadFillChoice::GetResult() {
    return this->result_;
}

void CGALThreadFillChoice::Initial() {
    this->result_ = false;
    this->enable_ = false;
    this->first_connect_ = true;
    this->own_renderer_ = false;
    this->fill_id_ = -1;
    this->renderer_ = nullptr;
    this->surface_ = nullptr;
    this->last_picked_actor_ = nullptr;
    this->last_picked_property_ = vtkSmartPointer<vtkProperty>::New();
}

void CGALThreadFillChoice::FillerCallback() {
    qDebug();
    if (fill_id_ >= 0) {
        vtkNew<vtkAppendFilter> append_filter;
        append_filter->AddInputData(this->filled_surface_list_.at(this->fill_id_));
        append_filter->Update();
        vtkNew<vtkGeometryFilter> geometry_filter;
        geometry_filter->SetInputData(append_filter->GetOutput());
        geometry_filter->Update();
        vtkNew<vtkCleanPolyData> clean_filter;
        clean_filter->SetInputConnection(geometry_filter->GetOutputPort());
        clean_filter->Update();
        this->surface_ = clean_filter->GetOutput();
    }
    this->SelectorOff();
}

void CGALThreadFillChoice::SlotKeyPressed(const QString &key) {
    if (this->enable_) {
        if (key == "space") {
            this->result_ = true;
            this->FillerCallback();
            emit SignalFillFinish();
        } else if (key == "q" || key == "Q") {
            this->result_ = false;
            this->SelectorOff();
            emit SignalFillFinish();
        }
    }
}

void CGALThreadFillChoice::SlotMouseClicked(const qint32 x, const qint32 y) {
    if (!this->enable_) {
        return ;
    }
    vtkNew<vtkPropPicker> picker;
    picker->Pick(x, y, 0, this->renderer_->GetRenderer());
    if (!this->filled_actor_list_.contains(picker->GetActor())) {
        return ;
    }
    if (this->last_picked_actor_) {
        this->last_picked_actor_->GetProperty()->DeepCopy(
            this->last_picked_property_);
    }
    this->last_picked_actor_ = picker->GetActor();
    if (this->last_picked_actor_) {
        this->last_picked_property_->DeepCopy(
            this->last_picked_actor_->GetProperty());
        this->last_picked_actor_->GetProperty()->SetColor(0.0, 1.0, 0.0);
        this->last_picked_actor_->GetProperty()->SetDiffuse(1.0);
        this->last_picked_actor_->GetProperty()->SetSpecular(0.0);
        fill_id_ = this->last_picked_actor_->GetMapper()->GetArrayId();
    }
}
