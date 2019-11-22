#include "readivus.h"
#include "ui_readivus.h"
#include "quihelper.h"


ReadIVUS::ReadIVUS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadIVUS) {
    ui->setupUi(this);
    this->setFixedSize(880, 570);
    angle = 0;

    ui->btn_angle0->move(470, 250);
    ui->btn_angle45->move(470, 10);
    ui->btn_angle90->move(250, 10);
    ui->btn_angle135->move(10, 10);
    ui->btn_angle180->move(10, 250);
    ui->label_angle0->move(460, 250);
    ui->slider->move(300, 0);
    connect(ui->slider, &QSlider::valueChanged,
            this, &ReadIVUS::SlotTransverseCurrentIndex);

    // 左侧
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow_transverse;
    imageViewer->SetRenderWindow(renderWindow_transverse);
    ui->transverse->SetRenderWindow(imageViewer->GetRenderWindow());
    imageViewer->SetupInteractor(
        ui->transverse->GetRenderWindow()->GetInteractor());
    imageViewer->GetRenderer()->SetBackground(90 / 255.0, 90 / 255.0, 90 / 255.0);
    vtkNew<vtkInteractorStyleImage> transverse_style;
    ui->transverse->GetRenderWindow()->GetInteractor()->
    SetInteractorStyle(transverse_style);
    vtk_connections_->Connect(transverse_style,
                              vtkCommand::MouseWheelForwardEvent,
                              this, SLOT(SlotLeftForward()));
    vtk_connections_->Connect(transverse_style,
                              vtkCommand::MouseWheelBackwardEvent,
                              this, SLOT(SlotLeftBackword()));

    // 右侧
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow_median_sagittal;
    ui->median_sagittal->SetRenderWindow(renderWindow_median_sagittal);
    ui->median_sagittal->GetRenderWindow()->AddRenderer(select_render_);
    select_render_->SetBackground(90 / 255.0, 90 / 255.0, 90 / 255.0);
    vtkNew<vtkInteractorStyleImage> median_sagittal_style;
    ui->median_sagittal->GetRenderWindow()->GetInteractor()->
    SetInteractorStyle(median_sagittal_style);
    vtk_connections_->Connect(median_sagittal_style,
                              vtkCommand::LeftButtonReleaseEvent,
                              this, SLOT(SlotEmpty()));
    vtk_connections_->Connect(median_sagittal_style,
                              vtkCommand::LeftButtonPressEvent,
                              this, SLOT(SlotEmpty()));
    vtk_connections_->Connect(median_sagittal_style,
                              vtkCommand::MouseWheelForwardEvent,
                              this, SLOT(SlotRightForward()));
    vtk_connections_->Connect(median_sagittal_style,
                              vtkCommand::MouseWheelBackwardEvent,
                              this, SLOT(SlotRightBackword()));

}

ReadIVUS::~ReadIVUS() {
    delete ui;
}



void ReadIVUS::on_pushButton_clicked() {

    QString tmp_file;
    tmp_file =
        QUIHelper::getFileName("*.dcm *.*");

    QFileInfo file_info(tmp_file);
    QString extension = file_info.path();
    using PixelType = float;
    constexpr unsigned int Dimension = 3;
    using ImageType = itk::Image< PixelType, Dimension >;
    using ReaderType = itk::ImageSeriesReader< ImageType >;
    using ImageIOType = itk::GDCMImageIO;
    using NamesGeneratorType = itk::GDCMSeriesFileNames;
    ReaderType::Pointer reader = ReaderType::New();
    ImageIOType::Pointer dicomIO = ImageIOType::New();
    reader->SetImageIO(dicomIO);
    NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
    nameGenerator->SetUseSeriesDetails(true);
    nameGenerator->SetDirectory(extension.toLocal8Bit().data());
    using SeriesIdContainer = std::vector< std::string >;
    const SeriesIdContainer &seriesUID = nameGenerator->GetSeriesUIDs();
    auto seriesItr = seriesUID.begin();
    auto seriesEnd = seriesUID.end();
    using FileNamesContainer = std::vector< std::string >;
    FileNamesContainer fileNames ;
    std::string seriesIdentifier;
    while (seriesItr != seriesEnd) {
        seriesIdentifier = seriesItr->c_str();
        fileNames = nameGenerator->GetFileNames(seriesIdentifier);
        ++seriesItr;
    }
    reader->SetFileNames(fileNames);
    try {
        reader->Update();
    } catch (itk::ExceptionObject &ex) {
        std::cout << ex << std::endl;
        return ;
    }
    typedef itk::ImageToVTKImageFilter< ImageType> itkTovtkFilterType;
    itkTovtkFilterType::Pointer itkTovtkImageFilter = itkTovtkFilterType::New();
    itkTovtkImageFilter->SetInput(reader->GetOutput());
    itkTovtkImageFilter->Update();

    int imageDims[3];
    imagedata_->DeepCopy(itkTovtkImageFilter->GetOutput());
    imagedata_->SetSpacing(1.5, 1.5, 0.5);
    imagedata_->GetDimensions(imageDims);//获取长宽高
    ui->slider->setMaximum(imageDims[2]);




    int extent[6];
    double spacing[3];
    double origin[3];
    imagedata_->GetExtent(extent);
    imagedata_->GetSpacing(spacing);
    imagedata_->GetOrigin(origin);
    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
    double axialElements[16] = {
        cos(angle * 180 / 3.14),   0,   sin(angle * 180 / 3.14),   0,
        sin(angle * 180 / 3.14),  0,   cos(angle * 180 / 3.14),   0,
        0,     -1,  0,     0,
        0,     0,   0,     1
    };
    vtkNew< vtkMatrix4x4 > resliceAxes ;
    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    reslice->SetInputData(imagedata_);
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();
    reslice->Update();

    imgActor->SetInputData(reslice->GetOutput());
    select_render_->AddActor(imgActor);

    // 左侧
    imageViewer->SetInputData(imagedata_);
    imageViewer->SetSlice(5000);
    ui->slider->setValue(imageViewer->GetSlice());
    vtkSmartPointer<vtkCamera> camera_reight = this->select_render_->GetActiveCamera();
    camera_reight->ParallelProjectionOn();
    double yd_right = (extent[5] - extent[4] + 1) * spacing[1];
    double d = camera_reight->GetDistance();
    camera_reight->SetFocalPoint(center[0], center[1], 0.0);
    camera_reight->SetPosition(center[0], center[1], d);
    camera_reight->SetParallelScale(0.5 * (yd_right - 1));
    ui->transverse->GetRenderWindow()->Render();

    // 右侧
    vtkSmartPointer<vtkCamera> camera_left = this->select_render_->GetActiveCamera();
    double origin_left[3];
    double spacing_left[3];
    int extent_left[6];
    reslice->GetOutput()->GetOrigin(origin_left);
    reslice->GetOutput()->GetSpacing(spacing_left);
    reslice->GetOutput()->GetExtent(extent_left);
    camera_left->ParallelProjectionOn();
    double xc_left =
        origin_left[0] + 0.5 * (extent_left[0] + extent_left[1]) * spacing_left[0];
    double yc_left =
        origin_left[1] + 0.5 * (extent_left[2] + extent_left[3]) * spacing_left[1];
    double yd_left = (extent_left[3] - extent_left[2] + 1) * spacing_left[1];
    double d_left = camera_left->GetDistance();
    camera_left->SetFocalPoint(xc_left, yc_left, 0.0);
    camera_left->SetPosition(xc_left, yc_left, d_left);
    camera_left->SetParallelScale(0.5 * (yd_left - 1));
    ui->median_sagittal->GetRenderWindow()->Render();
}



void ReadIVUS::SlotLeftForward() {
    imageViewer->SetSlice(imageViewer->GetSlice() + 1);
    ui->slider->setValue(imageViewer->GetSlice());
}

void ReadIVUS::SlotLeftBackword() {
    imageViewer->SetSlice(imageViewer->GetSlice() - 1);
    ui->slider->setValue(imageViewer->GetSlice());
}

void ReadIVUS::SlotRightForward() {
    if (angle < 180) {
        angle += 1;
    }
    LeftChangeAngle();
}

void ReadIVUS::SlotRightBackword() {
    if (angle > 2) {
        angle -= 1;
    }
    LeftChangeAngle();
}

void ReadIVUS::SlotTransverseCurrentIndex(const int value) {
    imageViewer->SetSlice(value);
}

void ReadIVUS::LeftChangeAngle() {
    int extent[6];
    double spacing[3];
    double origin[3];
    imagedata_->GetExtent(extent);
    imagedata_->GetSpacing(spacing);
    imagedata_->GetOrigin(origin);
    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
    double axialElements[16] = {
        cos(angle * 180 / 3.14),   0,   sin(angle * 180 / 3.14),   0,
        sin(angle * 180 / 3.14),  0,   cos(angle * 180 / 3.14),   0,
        0,     -1,  0,     0,
        0,     0,   0,     1
    };
    vtkNew< vtkMatrix4x4 > resliceAxes ;
    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);
    reslice->SetInputData(imagedata_);
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();
    reslice->Update();
    imgActor->SetInputData(reslice->GetOutput());
    ui->median_sagittal->GetRenderWindow()->Render();

}



