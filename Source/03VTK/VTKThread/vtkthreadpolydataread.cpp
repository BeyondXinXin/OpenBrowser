// 01 Frame includes
#include "vtkthreadpolydataread.h"

// VTK includes
#include <vtkCommand.h>
#include <vtkSTLReader.h>
#include <vtkMarchingCubes.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkMassProperties.h>

VtkThreadPolyDataRead::VtkThreadPolyDataRead(QObject *parent) :
    VtkThread(parent) {
    this->Initial();
}

VtkThreadPolyDataRead::~VtkThreadPolyDataRead() {
}

void VtkThreadPolyDataRead::SetInputFileName(const QString &value) {
    this->input_file_name_ = value;
}

QString VtkThreadPolyDataRead::GetVolumeSurfaaceArea() {
    vtkSmartPointer<vtkTriangleFilter> triangleFilter =
        vtkSmartPointer<vtkTriangleFilter>::New();
    triangleFilter->SetInputData(this->surface_);
    vtkSmartPointer<vtkPolyDataNormals> normals =
        vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputConnection(triangleFilter->GetOutputPort());
    normals->ConsistencyOn();
    normals->SplittingOff();
    vtkSmartPointer<vtkMassProperties> massProperties =
        vtkSmartPointer<vtkMassProperties>::New();
    massProperties->SetInputConnection(normals->GetOutputPort());
    massProperties->Update();
    return QString("体积  : %1 立方厘米\n表面积: %2 平方厘米")
           .arg(massProperties->GetVolume() / 1000000000, 0, 'f', 2)
           .arg(massProperties->GetSurfaceArea() / 1000000, 0, 'f', 2);
}

vtkSmartPointer<vtkPolyData> VtkThreadPolyDataRead::GetOutput() {
    return this->output_;
}

void VtkThreadPolyDataRead::run() {
    this->InitialResult();
    this->Execute();
}

void VtkThreadPolyDataRead::Initial() {
    this->format_ = UNKNOW;
    this->input_file_name_ = "";
    this->surface_ = nullptr;
    this->output_ = nullptr;
    this->setObjectName("vmtksurfacereader");
}

bool VtkThreadPolyDataRead::ReadStlSurfaceFile() {
    if (this->input_file_name_.isEmpty()) {
        qWarning() << "no InputFileName";
        return false;
    }
    emit SignalVtkThreadProgressOut("正在打开模型", -1);
    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(this->input_file_name_.toLocal8Bit().data());
    reader->AddObserver(vtkCommand::ProgressEvent,
                        this, &VtkThreadPolyDataRead::PrintProgress);
    reader->Update();
    this->surface_ = reader->GetOutput();
    return true;
}

void VtkThreadPolyDataRead::Execute() {
    QFileInfo file_info(input_file_name_);
    QString extension = file_info.suffix();
    if (extension == "vtp") {
        this->format_ = Format::VTKXML;
    } else if (extension == "vtkxml") {
        this->format_ = Format::VTKXML;
    } else if (extension == "vtk") {
        this->format_ = Format::VTK;
    } else if (extension == "stl") {
        this->format_ = Format::STL;
    } else if (extension == "ply") {
        this->format_ = Format::PLY;
    } else if (extension == "tec") {
        this->format_ = Format::TECPLOT;
    } else {
        this->format_ = Format::UNKNOW;
    }
    if (this->format_ == STL) {
        if (!this->ReadStlSurfaceFile()) {
            return ;
        }
    }
    this->output_ = this->surface_;
    this->SetResult(true);
}
















