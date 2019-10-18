// 01frame includes
#include "automaticdivision.h"

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

AutomaticDivision::AutomaticDivision(QObject *parent) : QObject(parent) {
    this->Initial();
}

AutomaticDivision::~AutomaticDivision() {
}

void AutomaticDivision::Execute() {
    if (this->surface_ != nullptr) {
        vtkNew<vtkPolyDataConnectivityFilter> connectivity_filter;
        connectivity_filter->SetInputData(this->surface_);
        connectivity_filter->SetExtractionModeToLargestRegion();
        connectivity_filter->AddSeed(100);
        connectivity_filter->Update();
        this->surface_ = connectivity_filter->GetOutput();
        emit SignalClippedFinish();
    }
}

void AutomaticDivision::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
    this->surface_ = value;
}

vtkSmartPointer<vtkPolyData> AutomaticDivision::GetSurface() {
    return this->surface_;
}

void AutomaticDivision::Initial() {
    this->surface_ = nullptr;
}
