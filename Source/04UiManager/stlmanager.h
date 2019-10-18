/*
 * STL 界面管理
 * std::cout << "几何数据(点数)：" << surface_->GetNumberOfPoints() << std::endl;
 * std::cout << "拓扑数据(单元)：" << surface_->GetNumberOfCells() << std::endl;
*/

#ifndef STLMANAGER_H
#define STLMANAGER_H

// 01 frame includes
#include <app.h>

// 05 includes
#include "cgalthreadfill.h"
#include "automaticdivision.h"
#include "customvtkrenderer.h"
#include "linesurfaceclipper.h"
#include "fillsurfaceselector.h"
#include "customsurfaceviewer.h"
#include "vtkthreadsubdivision.h"
#include "smoothsurfaceselector.h"
#include "cgalthreadsubdivision.h"

// 05 vtkthread includes
#include "vtkthreadpolydataread.h"
#include "vtkthreadimagedataread.h"
#include "vtkthreadpolydatawrite.h"
#include "vtkthreadmarchingcubes.h"

// VTL includes
#include <QVTKOpenGLWidget.h>



class STLManager: public QObject {
    Q_OBJECT
  public:
    explicit STLManager(QVTKOpenGLWidget &vtk_widget,
                        QObject *parent = nullptr);
    virtual ~STLManager() override;
    void OpenStlFile(const QString &file_path,
                     vtkSmartPointer<vtkImageData> value = nullptr);
  public slots:
    void SlotPolyDataHandle(const int &operation);
  Q_SIGNALS:
    void SingnalFinished();
    void SignalPromptInformationOut(const QString &text);
    void SignalVtkThreadProgressOut(const QString str, const int value);

  private:
    void Initial();

  private Q_SLOTS:
    void SlotRunFinished();
    void SlotVTKThreadMaskWidgetIn(int value = 2);
    void SlotCGLAThreadMaskWidgetIn();

  private:
    QVTKOpenGLWidget &vtk_widget_; // qt窗口
    QPointer< VtkThreadPolyDataRead > reade_; // stl 读取
    QPointer< VtkThreadPolyDataWrite >write_;// stl 保存

    QList<vtkSmartPointer<vtkPolyData>> polydata_list_;// polydata数据
    QPointer<CustomVtkRenderer> renderer_;// 渲染器
    QPointer<CustomSurfaceViewer> viewer_;//模型

    QPointer< VtkThreadMarchingCubes > marching_cubes_;//imagedata转polydata

    QPointer<AutomaticDivision> surface_auto_division_;// 提取最大连通域
    QPointer<LineSurfaceClipper> surface_line_clipper_;// 线性剪裁
    QPointer<SmoothSurfaceSelector> surface_smooth_selector_;// 区域平滑和修剪
    QPointer<VtkThreadSubdivision> surface_subdivision_;// vtk细分
    QPointer<FillSurfaceSelector> surface_fill_selector_;// 封闭

    QPointer<CGALThreadSubdivision> surface_cgal_subdivision_; // CGAL表面细分
    QPointer<CGALThreadFill> surface_cgal_fill_; // CGAL封闭
    QPointer<CGALThreadFillChoice> surface_cgal_fillchoice_; // CGAL封闭选择器

};

#endif // STLMANAGER_H
