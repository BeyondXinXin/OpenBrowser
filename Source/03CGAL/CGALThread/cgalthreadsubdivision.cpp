// 01frame includes
#include "cgalthreadsubdivision.h"

// C++ includes
#include <string.h>
#include <fstream>
#include <iostream>

// VTK includes
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkSmartPointer.h>

// CGAL includes
#include <CGAL/Timer.h>
#include <CGAL/Surface_mesh.h>
#include <boost/lexical_cast.hpp>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/subdivision_method_3.h>
#include <CGAL/boost/graph/graph_traits_Surface_mesh.h>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/refine.h>
#include <CGAL/Polygon_mesh_processing/fair.h>
#include <fstream>
#include <map>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>  Polyhedron;
typedef Polyhedron::Vertex_handle   Vertex_handle;


// extract vertices which are at most k (inclusive)
// far from vertex v in the graph of edges
void extract_k_ring(Vertex_handle v,
                    int k,
                    std::vector<Vertex_handle> &qv) {
    std::map<Vertex_handle, int>  D;
    qv.push_back(v);
    D[v] = 0;
    std::size_t current_index = 0;
    int dist_v;
    while (current_index < qv.size() && (dist_v = D[qv[current_index]]) < k) {
        v = qv[current_index++];
        Polyhedron::Halfedge_around_vertex_circulator e(v->vertex_begin()), e_end(e);
        do {
            Vertex_handle new_v = e->opposite()->vertex();
            if (D.insert(std::make_pair(new_v, dist_v + 1)).second) {
                qv.push_back(new_v);
            }
        } while (++e != e_end);
    }
}


CGALThreadSubdivision::CGALThreadSubdivision(QObject *parent) :
    CGALThread(parent) {
    this->surface_ = nullptr;
}

CGALThreadSubdivision::~CGALThreadSubdivision() {
}

void CGALThreadSubdivision::doWork() {
    this->SetResult(false);
    QFile::remove("subdivision.off");
    if (STL2OFF("subdivision.off")) {
        if (CGALFunctionSubdivision()) {
            OFF2STL("subdivision.off");
            this->SetResult(true);
        } else {
            this->SetResult(false);
        }
    }
}

void CGALThreadSubdivision::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
    this->surface_ = value;
}

vtkSmartPointer<vtkPolyData> CGALThreadSubdivision::GetSurface() {
    return this->surface_;
}

void CGALThreadSubdivision::run() {
    this->InitialResult();
    this->doWork();
}

bool CGALThreadSubdivision::CGALFunctionSubdivision() {
//    typedef CGAL::Simple_cartesian<double>         Kernel;
//    typedef CGAL::Surface_mesh<Kernel::Point_3>    PolygonMesh;
//    using namespace std;
//    using namespace CGAL;
//    namespace params = CGAL::parameters;
//    PolygonMesh pmesh;
//    std::ifstream in("subdivision.off");
//    if (in.fail()) {
//        qWarning() << "Could not open input file ";
//        return false;
//    }
//    in >> pmesh;
//    Subdivision_method_3::CatmullClark_subdivision(
//        pmesh, params::number_of_iterations(1));
//    Timer t;
//    t.start();
//    Subdivision_method_3::CatmullClark_subdivision(
//        pmesh, params::number_of_iterations(1));
//    std::cerr << "Done (" << t.time() << " s)" << std::endl;
//    std::ofstream out("subdivision.off");
//    out << pmesh;
//    out.close();
//    return true;
    const char *filename = ("subdivision.off");
    std::ifstream input(filename);
    Polyhedron poly;
    if (!input) {
        std::cerr << "1   Not a valid input file." << std::endl;
        return false;
    }
    if (!(input >> poly)) {
        std::cerr << "2   Not a valid input file." << std::endl;
        return false;
    }
    if (poly.empty()) {
        std::cerr << "Not a valid input file." << std::endl;
        return false;
    }
    input.close();
    std::vector<Polyhedron::Facet_handle>  new_facets;
    std::vector<Vertex_handle> new_vertices;
    CGAL::Polygon_mesh_processing::refine(poly,
                                          faces(poly),
                                          std::back_inserter(new_facets),
                                          std::back_inserter(new_vertices),
                                          CGAL::Polygon_mesh_processing::
                                          parameters::density_control_factor(2.));
    std::ofstream refined_off("subdivision1.off");
    refined_off << poly;
    refined_off.close();
    std::cout << "Refinement added " << new_vertices.size()
              << " vertices." << std::endl;
    Polyhedron::Vertex_iterator v = poly.vertices_begin();
    std::advance(v, 82/*e.g.*/);
    std::vector<Vertex_handle> region;
    extract_k_ring(v, 12/*e.g.*/, region);
    bool success = CGAL::Polygon_mesh_processing::fair(poly, region);
    std::cout << "Fairing : " << (success ? "succeeded" : "failed") << std::endl;
    std::ofstream faired_off("subdivision.off");
    faired_off << poly;
    faired_off.close();
    return false;
}

bool CGALThreadSubdivision::STL2OFF(const QString off_filename) {
    qDebug();
    if (off_filename.isEmpty()) {
        return false;
    }
    if (this->surface_ == nullptr) {
        return false;
    }
    double x[3];
    QFile file(off_filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        stream.seek(file.size());
        stream << "OFF" << "\n";
        if (this->surface_->GetNumberOfPoints() == 0) {
            qDebug() << "vtkPolyData 为空";
            file.close();
            return false;
        }
        stream << this->surface_->GetNumberOfPoints() << " "
               << this->surface_->GetNumberOfCells() << " 0\n";
        for (qint32 ww = 0; ww < this->surface_->GetNumberOfPoints() ; ww++) {
            this->surface_->GetPoint(ww, x);
            stream << x[0] << " " << x[1] << " " << x[2] << "\n";
        }
        for (qint32 ww = 0; ww < this->surface_->GetNumberOfCells() ; ww++) {
            stream << this->surface_->GetCell(ww)->GetNumberOfPoints() << " ";
            for (qint32 i = 0; i <
                    this->surface_->GetCell(ww)->GetNumberOfPoints(); i++) {
                stream << this->surface_->GetCell(ww)->GetPointId(i) << " ";
            }
            stream << "\n";
        }
    }
    file.close();
    return true;
}

void CGALThreadSubdivision::OFF2STL(const QString off_filename) {
    std::string inputFilename = off_filename.toLocal8Bit().data();
    std::ifstream fin(inputFilename.c_str());
    if (this->surface_ == nullptr) {
        return;
    }
    this->surface_ = vtkSmartPointer<vtkPolyData>::Take(CustomReader(fin));
    fin.close();
}

vtkPolyData *CGALThreadSubdivision::CustomReader(istream &infile) {
    qDebug();
    char buf[1000];
    infile.getline(buf, 1000);
    if (strcmp(buf, "off") == 0 || strcmp(buf, "OFF") == 0) {
        vtkIdType number_of_points, number_of_triangles, number_of_lines;
        infile >> number_of_points >> number_of_triangles >> number_of_lines;
        vtkSmartPointer<vtkPoints> points
            = vtkSmartPointer<vtkPoints>::New();
        points->SetNumberOfPoints(number_of_points);
        for (vtkIdType i = 0; i < number_of_points; i++) {
            double x, y, z;
            infile >> x >> y >> z;
            points->SetPoint(i, x, y, z);
        }
        vtkSmartPointer<vtkCellArray> polys
            = vtkSmartPointer<vtkCellArray>::New();
        int n;
        vtkIdType type;
        for (vtkIdType i = 0; i < number_of_triangles; i++) {
            infile >> n;
            polys->InsertNextCell(n);
            for (; n > 0; n--) {
                infile >> type;
                polys->InsertCellPoint(type);
            }
        }
        vtkPolyData *polydata = vtkPolyData::New();
        polydata->SetPoints(points);
        polydata->SetPolys(polys);
        return polydata;
    }
    vtkPolyData *polydata = vtkPolyData::New();
    return polydata;
}







