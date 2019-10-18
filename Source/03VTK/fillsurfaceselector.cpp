// 01frame includes
#include "fillsurfaceselector.h"

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



FillSurfaceSelector::FillSurfaceSelector(QObject *parent) : QObject(parent) {
    this->Initial();
}

FillSurfaceSelector::~FillSurfaceSelector() {
    if (this->own_renderer_ == true) {
        this->renderer_->deleteLater();
    }
}

void FillSurfaceSelector::Execute() {
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
                this, &FillSurfaceSelector::SlotMouseClicked);
        connect(this->renderer_, &CustomVtkRenderer::SignalKeyPressed,
                this, &FillSurfaceSelector::SlotKeyPressed);
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

void FillSurfaceSelector::SelectorOff() {
    for (const vtkSmartPointer<vtkActor> &actor : this->filled_actor_list_) {
        this->renderer_->GetRenderer()->RemoveActor(actor);
    }
    this->last_picked_actor_ = nullptr;
    this->last_picked_property_ = vtkSmartPointer<vtkProperty>::New();
    enable_ = false;
}

void FillSurfaceSelector::SelectorOn() {
    for (const vtkSmartPointer<vtkActor> &actor : this->filled_actor_list_) {
        this->renderer_->GetRenderer()->AddActor(actor);
    }
    enable_ = true;
}

void FillSurfaceSelector::SetVmtkRenderer(const QPointer<CustomVtkRenderer> value) {
    this->renderer_ = value;
}

void FillSurfaceSelector::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
    this->surface_ = value;
}

vtkSmartPointer<vtkPolyData> FillSurfaceSelector::GetSurface() {
    return this->surface_;
}

qint32 FillSurfaceSelector::GetFillCount() {
    return this->filled_actor_list_.size();
}

void FillSurfaceSelector::Initial() {
    this->enable_ = false;
    this->first_connect_ = true;
    this->own_renderer_ = false;
    this->fill_id_ = -1;
    this->renderer_ = nullptr;
    this->surface_ = nullptr;
    this->last_picked_actor_ = nullptr;
    this->last_picked_property_ = vtkSmartPointer<vtkProperty>::New();
}

void FillSurfaceSelector::FillerCallback() {
    qDebug();
    if (fill_id_ >= 0) {
        vtkNew<vtkAppendFilter> append_filter;
        append_filter->AddInputData(this->surface_);
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

void FillSurfaceSelector::SlotKeyPressed(const QString &key) {
    if (this->enable_) {
        if (key == "space") {
            this->FillerCallback();
            emit SignalFillFinish();
        } else if (key == "q" || key == "Q") {
            this->SelectorOff();
            emit SignalFillFinish();
        }
    }
}

void FillSurfaceSelector::SlotMouseClicked(const qint32 x, const qint32 y) {
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
