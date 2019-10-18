// 01frame includes
#include "formmain.h"
#include "ui_formmain.h"
#include "myMenu.h"

// 04ui includes
#include "formmaskwidget.h"

// VTK includes
#include <vtkPlane.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkStripper.h>
#include <vtkProperty.h>
#include <vtkSTLWriter.h>
#include <vtkSTLReader.h>
#include <vtkImageData.h>
#include <vtkImageCast.h>
#include <vtkCellPicker.h>
#include <vtkNamedColors.h>
#include <vtkLookupTable.h>
#include <vtkPlaneSource.h>
#include <vtkImageViewer2.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataReader.h>
#include <vtkMetaImageReader.h>
#include <vtkImageSlabReslice.h>
#include <vtkDICOMImageReader.h>
#include <vtkResliceCursorActor.h>
#include <vtkResliceCursorWidget.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkHandleRepresentation.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDistanceRepresentation.h>
#include <vtkBoundedPlanePointPlacer.h>
#include <vtkDistanceRepresentation2D.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkPointHandleRepresentation3D.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkResliceCursorLineRepresentation.h>


FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain) {
    ui->setupUi(this);
    initFrom();
}

FormMain::~FormMain() {
    delete ui;
}

void FormMain::initFrom() {
    //dcm界面初始化
    dcm_manager_ = new DcmManager(ui->view1, ui->view2, ui->view3, ui->view4, this);
    //ui界面初始化
    SlotLaftIn(0, "PageNumber");
    QList<QPushButton *> btns =
        ui->page->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
        IconHelper::Instance()->setIcon(
            btn, 0xf009, static_cast<quint32>(btn->size().height() - 10));
        connect(btn, &QPushButton::toggled,
                dcm_manager_, &DcmManager::SlotViewMaximization);
    }
    // stl manager 初始化
    stl_manager_ = new STLManager(*ui->view5, this);
    connect(ui->left_form, &FormLeft::SignalsPolyDataHandle, // PolyData Handle操作
            this->stl_manager_, &STLManager::SlotPolyDataHandle);
    connect(this->stl_manager_, &STLManager::SignalPromptInformationOut,// 信息
            ui->left_form, &FormLeft::SlotPromptInformation);
    connect(this->stl_manager_, &STLManager::SingnalFinished,// Handle操作完成
            ui->left_form, &FormLeft::SlotAllBtnEnabledTrue);
    // 计算 png转stl dcm提取png manager 初始化
    connect(ui->left_form, &FormLeft::SignalsMainOut,
            this, &FormMain::SlotLaftIn);
}


void FormMain::SlotLaftIn(const int int_tmp, const QString qstr_tmp) {
    if (qstr_tmp == "PageNumber") {
        ui->formmain_stackedWidget->setCurrentIndex(int_tmp);
    }
}

void FormMain::SlotOpenFileIn(QString tmp_file) {
    if (tmp_file.isEmpty()) {
        tmp_file = QUIHelper::getFileName("*.dcm *.stl");
    }
    QFileInfo file_info(tmp_file);
    QString extension = file_info.suffix();
    if (extension == "dcm") {
        dcm_manager_->OpenStlFile(tmp_file);
        SlotLaftIn(0, "PageNumber");
        ui->left_form->SlotsSliderBarMovtToIn(0);
    } else if (extension == "stl") {
        stl_manager_->OpenStlFile(tmp_file);
        SlotLaftIn(1, "PageNumber");
        ui->left_form->SlotsSliderBarMovtToIn(1);
    }
}
























