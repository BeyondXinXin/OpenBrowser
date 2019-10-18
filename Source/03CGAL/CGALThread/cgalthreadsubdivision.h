/*
 * CGAL 表面细分算法
 * */

#ifndef CGALTHREADSUBDIVISIONMETHODS_H
#define CGALTHREADSUBDIVISIONMETHODS_H

// 01frame includes
#include "app.h"

// 05CGALThread includes
#include "cgalthread.h"

class CGALThreadSubdivision : public CGALThread {
    Q_OBJECT
  public:
    explicit CGALThreadSubdivision(QObject *parent = nullptr);
    virtual ~CGALThreadSubdivision() override;
    void doWork();
    void SetSurface(const vtkSmartPointer<vtkPolyData> value);
    vtkSmartPointer<vtkPolyData> GetSurface();
  protected:
    virtual void run() override;
  private:
    bool CGALFunctionSubdivision();
};

#endif // CGALSURFACESUBDIVISIONMETHODS_H
