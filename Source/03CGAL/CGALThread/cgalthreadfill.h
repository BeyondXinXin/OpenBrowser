/*
 * CGAL +VTK *
 * 表面补洞
 * vtk交互寻找需要补的洞
 * CGAL负责补洞
 *
 * CGALThreadFill 类
 * 补洞
 *
 * CGALThreadFillChoice 类
 * 交互选择
 *
 * */


#ifndef CGALTHREADFILL_H
#define CGALTHREADFILL_H

// 01 frame includes
#include "app.h"

// 05 CGALThread includes
#include "cgalthread.h"

// 05 customvtk includes
#include "customvtkrenderer.h"

// VTK includes
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>

class CGALThreadFill : public CGALThread {
    Q_OBJECT
  public:
    explicit CGALThreadFill(QObject *parent = nullptr);
    virtual ~CGALThreadFill() override;
    void doWork();
    void SetSurface(const vtkSmartPointer<vtkPolyData> value, int num = 0);
    vtkSmartPointer<vtkPolyData> GetSurface();
  protected:
    virtual void run() override;
  private:
    bool CGALFunctionFill();
};

class CGALThreadFillChoice : public QObject {
    Q_OBJECT
  public:
    explicit CGALThreadFillChoice(QObject *parent = nullptr);
    virtual ~CGALThreadFillChoice() override;

    void Execute();
    void SelectorOff();
    void SelectorOn();
    void SetVmtkRenderer(const QPointer<CustomVtkRenderer> value);
    void SetSurface(const vtkSmartPointer<vtkPolyData> value);
    vtkSmartPointer<vtkPolyData> GetSurface();
    qint32 GetFillCount();
    bool GetResult();
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
    bool result_;
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

#endif // CGALTHREADFILL_H
