/*
 * CGAL线程   操作基类
 * 仅有run函数在子线程,其余均在主线程
*/

#ifndef CGALTHREAD_H
#define CGALTHREAD_H

//01frame
#include "app.h"

// VTK includes
#include <vtkPolyData.h>

class CGALThread : public QThread {
    Q_OBJECT
  public:
    explicit CGALThread(QObject *parent = nullptr);
    virtual ~CGALThread() override;
    bool GetThreadResult() const;//获取结果
  protected:
    virtual void run() override;//线程
    void InitialResult();//初始化
    void SetResult(const bool result);//设置结果
    void STL2OFF(const QString off_filename, const int num = 0);
    void OFF2STL(const QString off_filename);
    vtkPolyData *CustomReader(std::istream &infile);
  protected:
    bool result_;// 执行结果
    vtkSmartPointer<vtkPolyData> polydata_;// polydata 数据
    vtkSmartPointer<vtkPolyData> polydata_region_;// polydata 数据
};

#endif // CGALTHREAD_H
