// 01frame includes
#include "refinesurface.h"

// VTK includes
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataConnectivityFilter.h>

#include  <vtkXMLPolyDataReader.h>
#include  <vtkPolyData.h>
#include  <vtkSphereSource.h>
#include  <vtkTriangleFilter.h>
#include  <vtkDecimatePro.h>
#include  <vtkSmartPointer.h>
#include  <vtkPolyDataMapper.h>
#include  <vtkProperty.h>
#include  <vtkRenderWindow.h>
#include  <vtkRenderWindowInteractor.h>
#include  <vtkRenderer.h>
#include  <vtkCamera.h>
#include  <vtkNamedColors.h>

RefineSurface::RefineSurface(QObject *parent) : QObject(parent) {
    this->Initial();
}

RefineSurface::~RefineSurface() {
}

void RefineSurface::Execute() {
    if (this->surface_ != nullptr) {
        vtkNew<vtkDecimatePro> decimate ;
        decimate->SetInputData(this->surface_);
        decimate->SetTargetReduction(.9);
        decimate->PreserveTopologyOn();
        decimate->Update();
        this->surface_ = decimate->GetOutput();
        emit SignalClippedFinish();
    }
}

void RefineSurface::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
    this->surface_ = value;
}

vtkSmartPointer<vtkPolyData> RefineSurface::GetSurface() {
    return this->surface_;
}

void RefineSurface::Initial() {
    this->surface_ = nullptr;
}

