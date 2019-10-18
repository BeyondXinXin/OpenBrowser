/*
 * 提取最大连通域
 */

#ifndef AUTOMATICDIVISION_H
#define AUTOMATICDIVISION_H

// 01frame includes
#include "app.h"

// VTK includes
#include <vtkPolyData.h>
#include <vtkSeedWidget.h>
#include <vtkEventQtSlotConnect.h>

class AutomaticDivision: public QObject {
    Q_OBJECT
  public:
    explicit AutomaticDivision(QObject *parent = nullptr);
    virtual ~AutomaticDivision() override;
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

#endif // AUTOMATICDIVISION_H
