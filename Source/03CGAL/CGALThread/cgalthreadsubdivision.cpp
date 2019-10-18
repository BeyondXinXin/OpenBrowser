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


CGALThreadSubdivision::CGALThreadSubdivision(QObject *parent) :
    CGALThread(parent) {
    this->polydata_ = nullptr;
}

CGALThreadSubdivision::~CGALThreadSubdivision() {
}

void CGALThreadSubdivision::doWork() {
    STL2OFF("subdivision.off");
    if (CGALFunctionSubdivision()) {
        OFF2STL("subdivision.off");
        this->SetResult(true);
    } else {
        this->SetResult(false);
    }
}

void CGALThreadSubdivision::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
    this->polydata_ = value;
}

vtkSmartPointer<vtkPolyData> CGALThreadSubdivision::GetSurface() {
    return this->polydata_;
}

void CGALThreadSubdivision::run() {
    this->InitialResult();
    this->doWork();
}


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/refine.h>
#include <CGAL/Polygon_mesh_processing/fair.h>
#include <fstream>
#include <map>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>  Polyhedron;
typedef Polyhedron::Vertex_handle   Vertex_handle;


bool CGALThreadSubdivision::CGALFunctionSubdivision() {
    typedef CGAL::Simple_cartesian<double>         Kernel;
    typedef CGAL::Surface_mesh<Kernel::Point_3>    PolygonMesh;
    using namespace std;
    using namespace CGAL;
    namespace params = CGAL::parameters;
    PolygonMesh pmesh;
    std::ifstream in("subdivision.off");
    if (in.fail()) {
        qWarning() << "Could not open input file ";
        return false;
    }
    in >> pmesh;
    Subdivision_method_3::CatmullClark_subdivision(
        pmesh, params::number_of_iterations(1));
    Timer t;
    t.start();
    Subdivision_method_3::CatmullClark_subdivision(
        pmesh, params::number_of_iterations(1));
    std::cerr << "Done (" << t.time() << " s)" << std::endl;
    std::ofstream out("subdivision.off");
    out << pmesh;
    out.close();
    return true;
}








