/*
 * 表面细化
 */

#ifndef REFINESURFACE_H
#define REFINESURFACE_H

// 01frame includes
#include "app.h"

// VTK includes
#include <vtkPolyData.h>
#include <vtkSeedWidget.h>
#include <vtkEventQtSlotConnect.h>

class RefineSurface: public QObject {
    Q_OBJECT
  public:
    explicit RefineSurface(QObject *parent = nullptr);
    virtual ~RefineSurface() override;
    void Execute();
    void SetSurface(const vtkSmartPointer<vtkPolyData> value);
    vtkSmartPointer<vtkPolyData> GetSurface();
  signals:
    void SignalClippedFinish();
  private:
    void Initial();
  private:
    vtkSmartPointer<vtkPolyData> surface_;
};

#endif // REFINESURFACE_H
