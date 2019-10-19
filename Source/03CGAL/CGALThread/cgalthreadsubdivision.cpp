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
    this->surface_ = nullptr;
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

void CGALThreadSubdivision::STL2OFF(const QString off_filename, const int num) {
    qDebug();
    if (num == 0) {
        if (this->surface_ == nullptr) {
            return;
        }
        if (off_filename.isEmpty()) {
            return;
        }
        double x[3];
        QFile file(off_filename);
        file.open(QIODevice::WriteOnly);
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream << "OFF" << "\n";
            stream << this->surface_->GetNumberOfPoints() << " "
                   << this->surface_->GetNumberOfCells() << " 0\n";
            for (int ww = 0; ww < this->surface_->GetNumberOfPoints() ; ww++) {
                this->surface_->GetPoint(ww, x);
                stream << x[0] << " " << x[1] << " " << x[2] << "\n";
            }
            for (int ww = 0; ww < this->surface_->GetNumberOfCells() ; ww++) {
                stream << this->surface_->GetCell(ww)->GetNumberOfPoints() << " ";
                for (int i = 0; i <
                        this->surface_->GetCell(ww)->GetNumberOfPoints(); i++) {
                    stream << this->surface_->GetCell(ww)->GetPointId(i) << " ";
                }
                stream << "\n";
            }
            file.close();
        }
    } else if (num == 1) {
        if (this->surface_region_ == nullptr) {
            return;
        }
        if (off_filename.isEmpty()) {
            return;
        }
        double x[3];
        QFile file(off_filename);
        file.open(QIODevice::WriteOnly);
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream << "OFF" << "\n";
            stream << this->surface_region_->GetNumberOfPoints() << " "
                   << this->surface_region_->GetNumberOfCells() << " 0\n";
            for (int ww = 0; ww < this->surface_region_->GetNumberOfPoints() ; ww++) {
                this->surface_region_->GetPoint(ww, x);
                stream << x[0] << " " << x[1] << " " << x[2] << "\n";
            }
            for (int ww = 0; ww < this->surface_region_->GetNumberOfCells() ; ww++) {
                stream << this->surface_region_->GetCell(ww)->GetNumberOfPoints() << " ";
                for (int i = 0; i <
                        this->surface_region_->GetCell(ww)->GetNumberOfPoints(); i++) {
                    stream << this->surface_region_->GetCell(ww)->GetPointId(i) << " ";
                }
                stream << "\n";
            }
            file.close();
        }
    }
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







