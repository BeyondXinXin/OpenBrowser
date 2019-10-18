/*
 * polydata开口区域封闭
 */


#ifndef FILLSURFACESELECTOR_H
#define FILLSURFACESELECTOR_H

// 01 frame includes
#include "app.h"

// 05 customvtk includes
#include "customvtkrenderer.h"

// VTK includes
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>

class FillSurfaceSelector : public QObject {
    Q_OBJECT
  public:
    explicit FillSurfaceSelector(QObject *parent = nullptr);
    virtual ~FillSurfaceSelector() override;

    void Execute();
    void SelectorOff();
    void SelectorOn();
    void SetVmtkRenderer(const QPointer<CustomVtkRenderer> value);
    void SetSurface(const vtkSmartPointer<vtkPolyData> value);
    vtkSmartPointer<vtkPolyData> GetSurface();
    qint32 GetFillCount();
  signals:
    void SignalFillFinish();
  public slots:

  private:
    void Initial();
    void FillerCallback();
  private slots:
    void SlotKeyPressed(const QString &key);
    void SlotMouseClicked(const qint32 x, const qint32 y);
  private:
    bool enable_;
    bool first_connect_;
    bool own_renderer_;
    qint32 fill_id_;
    QPointer<CustomVtkRenderer> renderer_;
    vtkSmartPointer<vtkPolyData> surface_;
    QList<vtkSmartPointer<vtkActor>> filled_actor_list_;
    QList<vtkSmartPointer<vtkPolyData>> filled_surface_list_;
    vtkSmartPointer<vtkActor> last_picked_actor_;
    vtkSmartPointer<vtkProperty> last_picked_property_;
};

#endif // FILLSURFACESELECTOR_H
