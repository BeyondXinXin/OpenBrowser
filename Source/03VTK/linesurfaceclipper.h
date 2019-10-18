/*
 * polydata矩形剪裁
 */


#ifndef LINESURFACECLIPPER_H
#define LINESURFACECLIPPER_H

// 01frame includes
#include "app.h"

// 05customvtk includes
#include "customvtkrenderer.h"

// VTK includes
#include <vtkPolyData.h>
#include <vtkSeedWidget.h>
#include <vtkEventQtSlotConnect.h>

class LineSurfaceClipper : public QObject {
    Q_OBJECT
  public:
    explicit LineSurfaceClipper(QObject *parent = nullptr);
    virtual ~LineSurfaceClipper() override;
    void Execute();
    void SetVmtkRenderer(const QPointer<CustomVtkRenderer> value);
    void SetSurface(const vtkSmartPointer<vtkPolyData> value);
    vtkSmartPointer<vtkPolyData> GetSurface();
  signals:
    void SignalClippedFinish();
  private:
    void Initial();
    void ClipCallback();
  private slots:
    void SlotKeyPressed(const QString &key);
    void SlotSeedChanged(vtkObject *caller, unsigned long vtk_event,
                         void *client_data, void *call_data);
  private:
    bool first_connect_;
    bool own_renderer_;
    QPointer<CustomVtkRenderer> renderer_;
    vtkSmartPointer<vtkEventQtSlotConnect> vtk_connections_;
    vtkSmartPointer<vtkSeedWidget> seed_widget_;
    vtkSmartPointer<vtkPolyData> surface_;
};

#endif // LINESURFACECLIPPER_H
