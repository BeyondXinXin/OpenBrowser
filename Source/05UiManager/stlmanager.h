﻿#ifndef STLMANAGER_H
#define STLMANAGER_H

/*
 * ModeBrowser 界面管理
*/

// 01 Frame includes
#include "stable.h"

// 03 VTK includes
#include "refinesurface.h"
#include "automaticdivision.h"
#include "customvtkrenderer.h"
#include "linesurfaceclipper.h"
#include "customsurfaceviewer.h"
#include "vtkthreadsubdivision.h"
#include "smoothsurfaceselector.h"
#include "vtkthreadpolydataread.h"
#include "vtkthreadimagedataread.h"
#include "vtkthreadpolydatawrite.h"
#include "vtkthreadmarchingcubes.h"

// 03 CGAL includes
#include "cgalthreadfill.h"
#include "cgalthreadsubdivision.h"

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
    void SlotVTKThreadMaskWidgetIn(int value = 1);
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
    QPointer<RefineSurface> surface_refine_;// vtk细化

    QPointer<FillSurfaceSelector> fill_surface_selector_;// CGAL细分
    QPointer<CGALThreadSubdivision> surface_cgal_subdivision_; // CGAL表面细分

};

#endif // STLMANAGER_H