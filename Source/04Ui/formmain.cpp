// 01frame includes
#include "formmain.h"
#include "ui_formmain.h"
#include "myMenu.h"
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
    SlotSetMainWindos(4);
    image_manager_ = new ImageBrowserManager(*ui->image_window, this);
    // modle 初始化
    mode_manager_ = new STLManager(*ui->mainwindow1, this);
    connect(ui->left_form, &FormLeft::SignalsModeBrowserOut, // PolyData Handle操作
            this->mode_manager_, &STLManager::SlotPolyDataHandle);
    connect(this->mode_manager_, &STLManager::SignalPromptInformationOut,// 信息
            ui->left_form, &FormLeft::SlotPromptInformation);
    connect(this->mode_manager_, &STLManager::SingnalFinished,// Handle操作完成
            ui->left_form, &FormLeft::SlotModeBrowserBtnEnabledTrue);
    // dcm 初始化
    dcm_manager_ = new DcmManager(ui->view1, ui->view2, ui->view3, ui->view4, this);
    QList<QPushButton *> btns =
        ui->mainwindow2->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
        IconHelper::Instance()->setIcon(
            btn, 0xf009, static_cast<quint32>(btn->size().height() - 10));
        connect(btn, &QPushButton::toggled,
                dcm_manager_, &DcmManager::SlotViewMaximization);
    }
    // ui界面初始化
    connect(ui->left_form, &FormLeft::SingalSliderBarMovtToOut,
            this, &FormMain::SlotSetMainWindos);
    connect(this, &FormMain::SignalMainWindosChangeOut,
            this, &FormMain::SlotSetMainWindos);
    connect(this, &FormMain::SignalMainWindosChangeOut,
            ui->left_form, &FormLeft::SingalSliderBarMovtToIn);

}


void FormMain::SlotOpenFileIn(QString tmp_file) {
    if (tmp_file.isEmpty()) {
        tmp_file =
            QUIHelper::getFileName("*.dcm "
                                   "*.stl "
                                   "*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm ");
    }
    QFileInfo file_info(tmp_file);
    QString extension = file_info.suffix();
    if (extension == "dcm") {
        dcm_manager_->OpenStlFile(tmp_file);
        SlotSetMainWindos(2);
    } else if (extension == "stl") {
        mode_manager_->OpenStlFile(tmp_file);
        SlotSetMainWindos(1);
    } else if (extension == "bmp" ||
               extension == "jpg" ||
               extension == "pbm" ||
               extension == "pgm" ||
               extension == "png" ||
               extension == "ppm" ||
               extension == "xbm" ||
               extension == "xpm") {
        image_manager_->OpenStlFile(tmp_file);
        SlotSetMainWindos(0);
    }
}

void FormMain::SlotSetMainWindos(const int mainwindow) {
    ui->main_stacked_widget->setCurrentIndex(mainwindow);
}

















