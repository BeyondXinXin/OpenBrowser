//01frame
#include "cgalthread.h"

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



CGALThread::CGALThread(QObject *parent) : QThread(parent) {
    this->InitialResult();
}

CGALThread::~CGALThread() {

}

bool CGALThread::GetThreadResult() const {
    return this->result_;
}

void CGALThread::run() {

}

void CGALThread::InitialResult() {
    this->result_ = false;
}

void CGALThread::SetResult(const bool result) {
    result_ |= result;
}

void CGALThread::STL2OFF(const QString off_filename, const int num) {
    qDebug();
    if (num == 0) {
        if (this->polydata_ == nullptr) {
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
            stream << this->polydata_->GetNumberOfPoints() << " "
                   << this->polydata_->GetNumberOfCells() << " 0\n";
            for (int ww = 0; ww < this->polydata_->GetNumberOfPoints() ; ww++) {
                this->polydata_->GetPoint(ww, x);
                stream << x[0] << " " << x[1] << " " << x[2] << "\n";
            }
            for (int ww = 0; ww < this->polydata_->GetNumberOfCells() ; ww++) {
                stream << this->polydata_->GetCell(ww)->GetNumberOfPoints() << " ";
                for (int i = 0; i <
                        this->polydata_->GetCell(ww)->GetNumberOfPoints(); i++) {
                    stream << this->polydata_->GetCell(ww)->GetPointId(i) << " ";
                }
                stream << "\n";
            }
            file.close();
        }
    } else if (num == 1) {
        if (this->polydata_region_ == nullptr) {
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
            stream << this->polydata_region_->GetNumberOfPoints() << " "
                   << this->polydata_region_->GetNumberOfCells() << " 0\n";
            for (int ww = 0; ww < this->polydata_region_->GetNumberOfPoints() ; ww++) {
                this->polydata_region_->GetPoint(ww, x);
                stream << x[0] << " " << x[1] << " " << x[2] << "\n";
            }
            for (int ww = 0; ww < this->polydata_region_->GetNumberOfCells() ; ww++) {
                stream << this->polydata_region_->GetCell(ww)->GetNumberOfPoints() << " ";
                for (int i = 0; i <
                        this->polydata_region_->GetCell(ww)->GetNumberOfPoints(); i++) {
                    stream << this->polydata_region_->GetCell(ww)->GetPointId(i) << " ";
                }
                stream << "\n";
            }
            file.close();
        }
    }
}

void CGALThread::OFF2STL(const QString off_filename) {
    std::string inputFilename = off_filename.toLocal8Bit().data();
    std::ifstream fin(inputFilename.c_str());
    if (this->polydata_ == nullptr) {
        return;
    }
    this->polydata_ = vtkSmartPointer<vtkPolyData>::Take(CustomReader(fin));
    fin.close();
}

vtkPolyData *CGALThread::CustomReader(istream &infile) {
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



