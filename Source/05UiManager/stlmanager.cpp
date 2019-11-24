// 01 Frame includes
#include "stlmanager.h"
#include "quihelper.h"

// 04 Ui includes
#include "formmaskwidget.h"

// VTK includes
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkFillHolesFilter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtksys/SystemTools.hxx>

STLManager::STLManager(QVTKOpenGLWidget &vtk_widget,
                       QObject *parent) :
    QObject(parent), vtk_widget_(vtk_widget) {
    this->Initial();
}

STLManager::~STLManager() {// 析构
    reade_->deleteLater();
    write_->deleteLater();
    surface_line_clipper_->deleteLater();
    surface_auto_division_->deleteLater();
    surface_refine_->deleteLater();
    surface_smooth_selector_->deleteLater();
    surface_subdivision_->deleteLater();
    surface_cgal_subdivision_->deleteLater();
    fill_surface_selector_->deleteLater();
}

void STLManager::Initial() {// 初始化
    this->renderer_ = new CustomVtkRenderer(&this->vtk_widget_);
    this->renderer_->SetBackground({90 / 255.0, 90 / 255.0, 90 / 255.0});
    this->renderer_->Execute();
    this->viewer_ = new CustomSurfaceViewer();
    this->viewer_ ->SetVmtkRenderer(renderer_);
    // 读取
    this->reade_ = new VtkThreadPolyDataRead();
    connect(this->reade_,
            &VtkThreadPolyDataRead::finished,
            this, &STLManager::SlotRunFinished);
    connect(this->reade_,
            &VtkThreadPolyDataRead::SignalVtkThreadProgressOut,
            this, &STLManager::SignalVtkThreadProgressOut);
    // 等值面提取
    marching_cubes_ = new VtkThreadMarchingCubes();
    connect(marching_cubes_, &VtkThreadImageDataRead::finished,
            this, &STLManager::SlotRunFinished);
    // 保存
    this->write_ = new VtkThreadPolyDataWrite();
    connect(write_, &VtkThreadPolyDataWrite::finished,
            this, &STLManager::SlotRunFinished);
    connect(this->write_,
            &VtkThreadPolyDataWrite::SignalVtkThreadProgressOut,
            this, &STLManager::SignalVtkThreadProgressOut);
    // 自动提取连通域
    this->surface_auto_division_ = new AutomaticDivision();
    connect(surface_auto_division_,
            &AutomaticDivision::SignalClippedFinish,
            this, &STLManager::SlotRunFinished);
    // 线性剪裁
    this->surface_line_clipper_ = new LineSurfaceClipper();
    this->surface_line_clipper_->SetVmtkRenderer(renderer_);
    connect(surface_line_clipper_,
            &LineSurfaceClipper::SignalClippedFinish,
            this, &STLManager::SlotRunFinished);
    // 区域平滑和修剪
    this->surface_smooth_selector_ = new SmoothSurfaceSelector();
    this->surface_smooth_selector_->SetVmtkRenderer(renderer_);
    connect(surface_smooth_selector_,
            &SmoothSurfaceSelector::SignalSelectorFinish,
            this, &STLManager::SlotRunFinished);
    // vtk细分
    this->surface_subdivision_ = new VtkThreadSubdivision();
    connect(this->surface_subdivision_,
            &VtkThreadSubdivision::finished,
            this, &STLManager::SlotRunFinished);
    connect(this->surface_subdivision_,
            &VtkThreadSubdivision::SignalVtkThreadProgressOut,
            this, &STLManager::SignalVtkThreadProgressOut);
    // 细化
    this->surface_refine_ = new RefineSurface();
    connect(surface_refine_, &RefineSurface::SignalClippedFinish,
            this, &STLManager::SlotRunFinished);
    // CGAL表面细分
    this->surface_cgal_subdivision_ = new CGALThreadSubdivision();
    connect(this->surface_cgal_subdivision_, &CGALThreadSubdivision::finished,
            this, &STLManager::SlotRunFinished);
    // CGAL封闭
    fill_surface_selector_ = new FillSurfaceSelector();
    fill_surface_selector_->SetVmtkRenderer(renderer_);
    connect(fill_surface_selector_, &FillSurfaceSelector::SignalFillFinish,
            this, &STLManager::SlotRunFinished);
}

void STLManager::SlotVTKThreadMaskWidgetIn(int value) {// 遮层罩
    FormMaskWidget *w = new FormMaskWidget;
    w->SlotsStackedWidgetNum(value);
    connect(this, &STLManager::SignalVtkThreadProgressOut,
            w, &FormMaskWidget::SlotThreadAICurrent);
    connect(this, &STLManager::SingnalFinished,
            w, &FormMaskWidget::SlotThisCloseIn);
    w->SetCancleHide();
    w->show();
    qDebug();
    QThread::msleep(100);
}

void STLManager::SlotCGLAThreadMaskWidgetIn() {// 遮层罩
    FormMaskWidget *w = new FormMaskWidget;
    w->SlotsStackedWidgetNum(0);
    connect(this, &STLManager::SingnalFinished,
            w, &FormMaskWidget::SlotThisCloseIn);
    w->SetCancleHide();
    w->show();
    qDebug();
    QThread::msleep(100);
}

void STLManager::OpenStlFile(const QString &file_path,
                             vtkSmartPointer<vtkImageData> value) {// 打开文件
    if (nullptr != value) {
        marching_cubes_->Setnum(500);
        marching_cubes_->SetInputImageData(value);
        marching_cubes_->start();
    }
    reade_->SetInputFileName(file_path);
    SlotVTKThreadMaskWidgetIn();
    reade_->start();
}

void STLManager::SlotPolyDataHandle(const int &operation) {// polydata 处理
    if (this->polydata_list_.size() == 0 && operation != 21) {
        emit SingnalFinished();
        emit SignalPromptInformationOut(QString("PolyData 数据错误"));
        return;
    }
    switch (operation) {
        case 1: {// 自动提取连通域
                surface_auto_division_->SetSurface(this->polydata_list_.back());
                surface_auto_division_->Execute();
                break;
            }
        case 2: {// 直线剪裁
                surface_line_clipper_->SetSurface(this->polydata_list_.back());
                surface_line_clipper_->Execute();
                emit SignalPromptInformationOut(QString("左键：选取剪制区域\n"
                                                        "空格：确认选取区域\n"
                                                        " Q ：取消选区区域"));
                break;
            }
        case 3: {// 修剪
                this->surface_smooth_selector_->SetMethod(SmoothSurfaceSelector::CUT);
                this->surface_smooth_selector_->SetSurface(this->polydata_list_.back());
                this->surface_smooth_selector_->Execute();
                emit SignalPromptInformationOut(QString("左键：选取修剪区域\n空格：确认选取区域\n"
                                                        " Q ：取消选区区域\n"));
                break;
            }
        case 4: {// 平滑
                this->surface_smooth_selector_->SetMethod(SmoothSurfaceSelector::SMOOTH);
                this->surface_smooth_selector_->SetSurface(this->polydata_list_.back());
                this->surface_smooth_selector_->Execute();
                emit SignalPromptInformationOut(QString("左键：选取平滑区域\n空格：确认选取区域\n"
                                                        " Q ：取消选区区域\n"));
                break;
            }
        case 5: {// 细分
                emit SignalPromptInformationOut(QString("正在细分模型"));
                surface_subdivision_->SetSurface(this->polydata_list_.back());
                surface_subdivision_->SetMethod(VtkThreadSubdivision::LINEAR);
                SlotVTKThreadMaskWidgetIn();
                surface_subdivision_->start();
                break;
            }
        case 6: {// 表面细化
                surface_refine_->SetSurface(this->polydata_list_.back());
                surface_refine_->Execute();
                break;
            }
        case 11: {// CGAL细分
                surface_cgal_subdivision_->SetSurface(this->polydata_list_.back());
                SlotCGLAThreadMaskWidgetIn();
                surface_cgal_subdivision_->start();
                break;
            }
        case 12: {// CGAL自相交检测
                emit SingnalFinished();
                break;
            }
        case 13: {// CGAL封闭
                fill_surface_selector_->SetSurface(
                    this->polydata_list_.back());
                fill_surface_selector_->Execute();
                emit SignalPromptInformationOut(
                    QString(QString("共有%1个未封闭区域"
                                    "\n左键：选取封闭区域\n空格：确认选取区域\nEsc：取消选区区域"
                                    "\n前处理完成请单击#选择主动脉入口#"))
                    .arg(fill_surface_selector_->GetFillCount()));
                break;
            }
        case 21: { // 打开文件
                emit SingnalFinished();
                QString tmp_file = QUIHelper::GetFileName("*.stl");
                if (tmp_file.isEmpty()) {
                    break;
                }
                QFileInfo file_info(tmp_file);
                if (file_info.suffix() == "stl") {
                    OpenStlFile(tmp_file);
                } else {
                    emit SignalPromptInformationOut(QString("文件错误"));
                }
                break;
            }
        case 22: {// 保存文件
                emit SingnalFinished();
                QString tmp_file = QUIHelper::GetSaveName("*.stl *.vtk", "***.stl");
                if (tmp_file.isEmpty()) {
                    break;
                }
                this->write_->SetOutputFileName(tmp_file);
                this->write_->SetSurface(this->polydata_list_.back());
                SlotVTKThreadMaskWidgetIn(0);
                this->write_->start();
            }
            break;
        case 23: {// 撤销
                if (this->polydata_list_.size() == 1) {
                    emit SingnalFinished();
                    emit SignalPromptInformationOut(QString("PolyData 数据错误"));
                    return;
                }
                this->polydata_list_.pop_back();
                this->viewer_->SetSurface(this->polydata_list_.back());
                this->viewer_ ->Execute();
                this->renderer_->ResetCamera();
                emit SignalPromptInformationOut(QString("已撤销"));
                emit SingnalFinished();
                break;
            }
        default: {
                emit SingnalFinished();
                break;
            }
    }
}

void STLManager::SlotRunFinished() {// Handle PolyData操作完成
    emit SingnalFinished();
    if (QObject::sender() == reade_) {// 读取stl
        if (!reade_->GetThreadResult()) {
            emit SignalPromptInformationOut(QString("stl模型载入失败"));
            return;
        }
        if (this->polydata_list_.size() != 0) {
            this->polydata_list_.clear();
        }
        this->polydata_list_.push_back(this->reade_->GetOutput());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        this->renderer_->ResetCamera();
        this->renderer_->GetRenderer()->GetActiveCamera()->SetParallelProjection(1);
        emit SignalPromptInformationOut(QString("stl模型载入成功\n") +
                                        reade_->GetVolumeSurfaaceArea());
    } else if (QObject::sender() == this->marching_cubes_) { // imagedata 转 polydata
        if (!marching_cubes_->GetThreadResult()) {
            return;
        }
        this->polydata_list_.push_back(this->marching_cubes_->
                                       Getmarchingcubes()->GetOutput());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        this->renderer_->ResetCamera();
        this->renderer_->GetRenderer()->GetActiveCamera()->SetParallelProjection(1);
        emit SignalPromptInformationOut(QString(""));
    } else if (QObject::sender() == this->write_) { // stl 保存
        if (!this->write_->GetThreadResult()) {
            emit SignalPromptInformationOut(QString("stl模型保存失败"));
            return;
        }
        emit SignalPromptInformationOut(QString("stl模型保存成功"));
    } else if (QObject::sender() == surface_auto_division_) { // 提取最大连通域
        this->polydata_list_.push_back(this->surface_auto_division_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("自动分割完毕"));
    } else if (QObject::sender() == surface_line_clipper_) { // 线性剪裁
        this->polydata_list_.push_back(this->surface_line_clipper_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("手动剪裁完毕"));
    } else if (QObject::sender() == surface_smooth_selector_) { // 修剪 平滑
        this->polydata_list_.push_back(this->surface_smooth_selector_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("手动修剪 平滑完毕"));
    } else if (QObject::sender() == surface_subdivision_) { // 细分
        if (!surface_subdivision_->GetThreadResult()) {
            emit SignalPromptInformationOut(QString("模型细化失败"));
            return;
        }
        this->polydata_list_.push_back(this->surface_subdivision_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("自动细分完毕"));
    }  else if (QObject::sender() == surface_refine_) { // 表面细分
        this->polydata_list_.push_back(this->surface_refine_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("自动细分完毕"));
    } else if (QObject::sender() == surface_cgal_subdivision_) { // CGAL表面细分
        if (!surface_cgal_subdivision_->GetThreadResult()) {
            emit SignalPromptInformationOut(QString("CGAL表面细分失败"));
            return;
        }
        this->polydata_list_.push_back(
            this->surface_cgal_subdivision_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("CGAL表面细分成功"));
    } else if (QObject::sender() == fill_surface_selector_) { // CGAL 封闭
        this->polydata_list_.push_back(
            this->fill_surface_selector_->GetSurface());
        this->viewer_->SetSurface(this->polydata_list_.back());
        this->viewer_ ->Execute();
        emit SignalPromptInformationOut(QString("CGAL表面封闭成功"));
    }
}













