#include "formimagehandle.h"
#include "ui_formimagehandle.h"

FormImageHandle::FormImageHandle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormImageHandle) {
    ui->setupUi(this);
    WinGeom();// 几何变换窗口
    WinGray();// 灰度变换窗口
    WinEnhance();// 图像增强窗口
    WinMorp();// 形态学处理窗口
    WinColor();// 颜色模型窗口
    WinTest();// 测试窗口
}

FormImageHandle::~FormImageHandle() {
    delete ui;
}

void FormImageHandle::ShowImageHandel(const int num) {
    ui->image_stackedwidget->setCurrentIndex(num);
    show();
}

void FormImageHandle::WinGeom() {// 几何变换
    dock_Geom = new QWidget(this);
    //QSpinBox *spinbox_size;						// 缩放微调框
    //QSpinBox *spinbox_rotate;					// 旋转微调框
    //QSpinBox *spinbox_leanX, *spinbox_leanY;	// 图像移动距离
    QLineEdit *line_L, *line_W;					// 设置长宽
    QSpinBox *line_times;
    QSpinBox *line_degree;
    QSpinBox *line_leanX, *line_leanY;			// 倾斜角度
    //QButtonGroup *preButtonGroup;
    // 图像大小
    QLabel *null = new QLabel(tr("	"));
    QLabel *label_area = new QLabel(tr("图像大小"));
    QLabel *labelL = new QLabel(tr("图像长度:"));
    QLabel *labelW = new QLabel(tr("图像宽度:"));
    QPushButton *buttonDefault = new QPushButton(tr("默认"));
    QPushButton *buttonOK = new QPushButton(tr("确认"));
    line_L = new QLineEdit("512");
    line_L->setValidator(new QIntValidator(1, 10000));		// 只能输入数字
    line_L->setAlignment(Qt::AlignCenter);
    line_L->setStyleSheet("min-width: 50px;");
    line_W = new QLineEdit("512");
    line_W->setValidator(new QIntValidator(1, 10000));
    line_W->setAlignment(Qt::AlignCenter);

    connect(buttonDefault, SIGNAL(clicked(bool)), this, SLOT(autoSize(bool)));
    connect(buttonOK, SIGNAL(clicked()), this, SLOT(changeImageSize()));

    // 图像缩放
    QLabel *label_size = new QLabel(tr("图像缩放"));
    QLabel *label_times = new QLabel(tr("缩放倍数:"));
    QPushButton *button_size = new QPushButton(tr("确认"));
    QPushButton *buttonPre_size = new QPushButton(tr("预览"));
    line_times = new QSpinBox();
    line_times->setAlignment(Qt::AlignCenter);
    line_times->setRange(-10, 10);
    line_times->setValue(0);
    connect(button_size, SIGNAL(clicked()), this, SLOT(enlargeReduceOK()));

    // 图像旋转
    QLabel *label_rotate = new QLabel(tr("图像旋转"));
    QLabel *label_degree = new QLabel(tr("旋转角度:"));
    QPushButton *button_rotate = new QPushButton(tr("确认"));
    QPushButton *buttonPre_rotate = new QPushButton(tr("预览"));
    QPushButton *button_left = new QPushButton(tr("顺时针90"));
    QPushButton *button_right = new QPushButton(tr("逆时针90"));
    QPushButton *button_180 = new QPushButton(tr("旋转180"));
    line_degree = new QSpinBox();
    line_degree->setAlignment(Qt::AlignCenter);
    line_degree->setRange(-360, 360);
    line_degree->setValue(0);
    connect(button_rotate, SIGNAL(clicked()), this, SLOT(rotateImageOK()));
    connect(button_left, SIGNAL(clicked()), this, SLOT(rotateImage_270()));
    connect(button_right, SIGNAL(clicked()), this, SLOT(rotateImage_90()));
    connect(button_180, SIGNAL(clicked()), this, SLOT(rotateImage_180()));

    // 图像倾斜
    QLabel *label_lean = new QLabel(tr("图像倾斜"));
    QLabel *label_leanX = new QLabel(tr("水平角度:"));
    QLabel *label_leanY = new QLabel(tr("垂直角度:"));
    QPushButton *button_lean = new QPushButton(tr("确认"));
    QPushButton *buttonPre_lean = new QPushButton(tr("预览"));
    line_leanX = new QSpinBox();
    line_leanX->setAlignment(Qt::AlignCenter);
    line_leanX->setRange(0, 89);
    line_leanX->setValue(0);
    line_leanY = new QSpinBox();
    line_leanY->setAlignment(Qt::AlignCenter);
    line_leanY->setRange(0, 89);
    line_leanY->setValue(0);
    connect(button_lean, SIGNAL(clicked()), this, SLOT(LeanImageOK()));

    // 图像翻转
    QLabel *label_reverse = new QLabel(tr("图像翻转"));
    QPushButton *button_H = new QPushButton(tr("水平翻转"));
    QPushButton *button_V = new QPushButton(tr("垂直翻转"));
    connect(button_H, SIGNAL(clicked()), this, SLOT(flipImage_H()));
    connect(button_V, SIGNAL(clicked()), this, SLOT(flipImage_V()));

    // 预览按钮组
//    preButtonGroup->addButton(buttonPre_size, 0);
//    preButtonGroup->addButton(buttonPre_rotate, 1);
//    preButtonGroup->addButton(buttonPre_lean, 2);

    // 格栅布局
    QGridLayout *geomLayout = new QGridLayout();
    geomLayout->setAlignment(Qt::AlignTop);
    geomLayout->setMargin(30);

    geomLayout->addWidget(label_area, 0, 0, 1, 1);// 图像大小
    geomLayout->addWidget(labelL, 1, 1, 1, 1);
    geomLayout->addWidget(line_L, 1, 2, 1, 1);
    geomLayout->addWidget(labelW, 2, 1, 1, 1);
    geomLayout->addWidget(line_W, 2, 2, 1, 1);
    geomLayout->addWidget(buttonOK, 1, 3, 1, 1);
    geomLayout->addWidget(buttonDefault, 1, 4, 1, 1);

    geomLayout->addWidget(null, 10, 0, 1, 1);// 图像缩放
    geomLayout->addWidget(label_size, 11, 0, 1, 1);
    geomLayout->addWidget(label_times, 12, 1, 1, 1);
    geomLayout->addWidget(line_times, 12, 2, 1, 1);
    geomLayout->addWidget(button_size, 12, 3, 1, 1);
    geomLayout->addWidget(buttonPre_size, 12, 4, 1, 1);
    geomLayout->addWidget(null, 14, 0, 1, 1);

    geomLayout->addWidget(null, 20, 0, 1, 1);// 图像旋转
    geomLayout->addWidget(label_rotate, 21, 0, 1, 1);
    geomLayout->addWidget(label_degree, 22, 1, 1, 1);
    geomLayout->addWidget(line_degree, 22, 2, 1, 1);
    geomLayout->addWidget(button_rotate, 22, 3, 1, 1);
    geomLayout->addWidget(buttonPre_rotate, 22, 4, 1, 1);
    geomLayout->addWidget(button_180, 23, 2, 1, 1);
    geomLayout->addWidget(button_left, 23, 3, 1, 1);
    geomLayout->addWidget(button_right, 23, 4, 1, 1);

    geomLayout->addWidget(null, 30, 0, 1, 1);// 图像倾斜
    geomLayout->addWidget(label_lean, 31, 0, 1, 1);
    geomLayout->addWidget(label_leanX, 32, 1, 1, 1);
    geomLayout->addWidget(line_leanX, 32, 2, 1, 1);
    geomLayout->addWidget(label_leanY, 33, 1, 1, 1);
    geomLayout->addWidget(line_leanY, 33, 2, 1, 1);
    geomLayout->addWidget(button_lean, 32, 3, 1, 1);
    geomLayout->addWidget(buttonPre_lean, 32, 4, 1, 1);

    geomLayout->addWidget(null, 40, 0, 1, 1);// 图像翻转
    geomLayout->addWidget(label_reverse, 41, 0, 1, 1);
    geomLayout->addWidget(button_H, 42, 1, 1, 2);
    geomLayout->addWidget(button_V, 42, 3, 1, 2);

    dock_Geom->setFixedWidth(420);
    dock_Geom->setLayout(geomLayout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(dock_Geom);
    ui->image_stackedwidget->addWidget(scrollArea);
}

void FormImageHandle::WinGray() {// 灰度变换窗口
    dock_Gray = new QWidget(this);
    // Gray
    //QSpinBox *spinbox_bin;
    //QSpinBox *spinbox_alpha, *spinbox_beta;		// 图像灰度变换
    //QSpinBox *spinbox_gamma, *spinbox_c;		// 图像灰度变换
    QSpinBox *line_bin;
    QSpinBox *line_alpha, *line_beta;
    QSpinBox *line_gamma, *line_c;

    QLabel *label_linear = new QLabel(tr("线性变换"));
    QLabel *label_alpha = new QLabel(tr("Alpha:"));
    QLabel *label_beta = new QLabel(tr(" Beta:"));
    QPushButton *button_linear = new QPushButton(tr("确认"));
    QPushButton *buttonPre_linear = new QPushButton(tr("预览"));
    line_alpha = new QSpinBox();
    line_alpha->setAlignment(Qt::AlignCenter);
    line_alpha->setRange(0, 500);
    line_alpha->setValue(100);
    line_beta = new QSpinBox();
    line_beta->setAlignment(Qt::AlignCenter);
    line_beta->setRange(0, 200);
    line_beta->setValue(100);

    QLabel *label_log = new QLabel(tr("对数变换"));
    QLabel *label_c = new QLabel(tr("  Log:"));
    QPushButton *button_log = new QPushButton(tr("确认"));
    QPushButton *buttonPre_log = new QPushButton(tr("预览"));
    line_c = new QSpinBox();
    line_c->setAlignment(Qt::AlignCenter);
    line_c->setRange(0, 200);
    line_c->setValue(100);

    QLabel *label_gamma = new QLabel(tr("伽马变换"));
    QLabel *label_gam = new QLabel(tr("Gamma:"));
    QPushButton *button_gamma = new QPushButton(tr("确认"));
    QPushButton *buttonPre_gamma = new QPushButton(tr("预览"));
    line_gamma = new QSpinBox();
    line_gamma->setAlignment(Qt::AlignCenter);
    line_gamma->setRange(0, 200);
    line_gamma->setValue(100);

    // 二值图像
    QLabel *null = new QLabel(tr("	"));
    QLabel *label_bin = new QLabel(tr("二值图像"));
    QLabel *label_threshold = new QLabel(tr(" 阈值:"));
    QPushButton *button_bin = new QPushButton(tr("确认"));
    QPushButton *buttonPre_bin = new QPushButton(tr("预览"));
    line_bin = new QSpinBox();
    line_bin->setAlignment(Qt::AlignCenter);
    line_bin->setRange(0, 255);
    line_bin->setValue(100);

    QLabel *label_graylevel = new QLabel(tr("灰度图像"));
    QPushButton *button_graylevel = new QPushButton(tr("灰度图像"));

    QLabel *label_reverse = new QLabel(tr("反转变换"));
    QPushButton *button_reverse = new QPushButton(tr("图像反转"));

    QLabel *label_histeq = new QLabel();
    label_histeq->setText(tr("直方图"));
    QPushButton *button_histeq = new QPushButton();
    button_histeq->setText(tr("灰度直方图均衡化"));

//    preButtonGroup->addButton(buttonPre_bin, 3);
//    preButtonGroup->addButton(buttonPre_linear, 4);
//    preButtonGroup->addButton(buttonPre_gamma, 5);
//    preButtonGroup->addButton(buttonPre_log, 6);

    connect(button_bin, SIGNAL(clicked()), this, SLOT(binImageOK()));
    connect(button_graylevel, SIGNAL(clicked()), this, SLOT(grayImage()));
    connect(button_reverse, SIGNAL(clicked()), this, SLOT(reverseImage()));
    connect(button_linear, SIGNAL(clicked()), this, SLOT(linearImageOK()));
    connect(button_gamma, SIGNAL(clicked()), this, SLOT(gammaImageOK()));
    connect(button_log, SIGNAL(clicked()), this, SLOT(logImageOK()));
    connect(button_histeq, SIGNAL(clicked()), this, SLOT(histeqImage()));

    // 格栅布局
    QGridLayout *grayLayout = new QGridLayout();
    grayLayout->setAlignment(Qt::AlignTop);
    grayLayout->setMargin(30);

    grayLayout->addWidget(label_linear, 16, 0, 1, 1);
    grayLayout->addWidget(label_alpha, 17, 1, 1, 1);
    grayLayout->addWidget(line_alpha, 17, 2, 1, 1);
    grayLayout->addWidget(label_beta, 18, 1, 1, 1);
    grayLayout->addWidget(line_beta, 18, 2, 1, 1);
    grayLayout->addWidget(button_linear, 17, 3, 1, 1);
    grayLayout->addWidget(buttonPre_linear, 17, 4, 1, 1);

    grayLayout->addWidget(null, 20, 0, 1, 1);
    grayLayout->addWidget(label_log, 21, 0, 1, 1);
    grayLayout->addWidget(label_c, 22, 1, 1, 1);
    grayLayout->addWidget(line_c, 22, 2, 1, 1);
    grayLayout->addWidget(button_log, 22, 3, 1, 1);
    grayLayout->addWidget(buttonPre_log, 22, 4, 1, 1);

    grayLayout->addWidget(null, 25, 0, 1, 1);
    grayLayout->addWidget(label_gamma, 26, 0, 1, 1);
    grayLayout->addWidget(label_gam, 27, 1, 1, 1);
    grayLayout->addWidget(line_gamma, 27, 2, 1, 1);
    grayLayout->addWidget(button_gamma, 27, 3, 1, 1);
    grayLayout->addWidget(buttonPre_gamma, 27, 4, 1, 1);

    grayLayout->addWidget(null, 30, 0, 1, 1);
    grayLayout->addWidget(label_bin, 31, 0, 1, 1);
    grayLayout->addWidget(label_threshold, 32, 1, 1, 1);
    grayLayout->addWidget(line_bin, 32, 2, 1, 1);
    grayLayout->addWidget(button_bin, 32, 3, 1, 1);
    grayLayout->addWidget(buttonPre_bin, 32, 4, 1, 1);

    grayLayout->addWidget(null, 35, 0, 1, 1);
    grayLayout->addWidget(label_graylevel, 36, 0, 1, 1);
    grayLayout->addWidget(button_graylevel, 37, 1, 1, 4);

    grayLayout->addWidget(null, 40, 0, 1, 1);
    grayLayout->addWidget(label_reverse, 41, 0, 1, 1);
    grayLayout->addWidget(button_reverse, 42, 1, 1, 4);

    grayLayout->addWidget(null, 45, 0, 1, 1);
    grayLayout->addWidget(label_histeq, 46, 0, 1, 1);
    grayLayout->addWidget(button_histeq, 47, 1, 1, 4);

    dock_Gray->setFixedWidth(420);
    dock_Gray->setLayout(grayLayout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(dock_Gray);
    ui->image_stackedwidget->addWidget(scrollArea);

}

void FormImageHandle::WinEnhance() {// 图像增强窗口
    dock_Enhance =  new QWidget(this);
    // Enhance
    QSpinBox *spinbox_canny;					// canny微调框
    QSpinBox *spinbox_lineThreshold, *spinbox_minLineLength, *spinbox_maxLineGap;// Line
    QSpinBox *spinbox_minRadius, *spinbox_maxRadius;	// circle
    QComboBox *combo_smooth, *combo_sharpen;	// 下拉选择框

    QLabel *label_smooth = new QLabel(tr("图像平滑"));
    QLabel *label_coreSmooth = new QLabel(tr("模板大小"));
    QPushButton *button_Normalized = new QPushButton(tr("简单滤波"));
    QPushButton *button_Gaussian = new QPushButton(tr("高斯滤波"));
    QPushButton *button_Median = new QPushButton(tr("中值滤波"));
    combo_smooth = new QComboBox();
    combo_smooth->addItem(tr("3×3"));
    combo_smooth->addItem(tr("5×5"));
    combo_smooth->addItem(tr("7×7"));
    combo_smooth->addItem(tr("9×9"));
    combo_smooth->addItem(tr("11×11"));
    combo_smooth->addItem(tr("13×13"));
    combo_smooth->addItem(tr("15×15"));
    combo_smooth->addItem(tr("17×17"));
    combo_smooth->addItem(tr("19×19"));
    combo_smooth->addItem(tr("21×21"));

    connect(button_Normalized, SIGNAL(clicked()), this, SLOT(normalizedImage()));
    connect(button_Gaussian, SIGNAL(clicked()), this, SLOT(gaussianImage()));
    connect(button_Median, SIGNAL(clicked()), this, SLOT(medianImage()));


    QLabel *label_sharpen = new QLabel(tr("图像锐化"));
    QLabel *label_coreSharpen = new QLabel(tr("模板大小"));
    QPushButton *button_sobel = new QPushButton(tr("Sobel边缘检测"));
    QPushButton *button_laplacian = new QPushButton(tr("Laplacian检测"));
    QPushButton *button_canny = new QPushButton(tr("Canny边缘检测"));
    QPushButton *button_line = new QPushButton(tr("Hough线检测"));
    QPushButton *button_circle = new QPushButton(tr("Hough圆检测"));
    combo_sharpen = new QComboBox();
    combo_sharpen->addItem(tr("3×3"));
    combo_sharpen->addItem(tr("5×5"));
    combo_sharpen->addItem(tr("7×7"));
    combo_sharpen->addItem(tr("9×9"));
    combo_sharpen->addItem(tr("11×11"));
    combo_sharpen->addItem(tr("13×13"));
    combo_sharpen->addItem(tr("15×15"));
    combo_sharpen->addItem(tr("17×17"));
    combo_sharpen->addItem(tr("19×19"));
    combo_sharpen->addItem(tr("21×21"));

    QLabel *label_canny = new QLabel(tr("Canny阈值"));
    spinbox_canny = new QSpinBox;							// 微调框
    spinbox_canny->setRange(0, 100);
    spinbox_canny->setValue(20);

    QSlider *slider_canny = new QSlider(Qt::Horizontal);		// 滑动条
    slider_canny->setRange(0, 100);
    slider_canny->setValue(20);

    connect(button_sobel, SIGNAL(clicked()), this, SLOT(sobelImage()));
    connect(button_laplacian, SIGNAL(clicked()), this, SLOT(laplacianImage()));
    connect(button_canny, SIGNAL(clicked()), this, SLOT(cannyImage()));
    connect(button_line, SIGNAL(clicked()), this, SLOT(lineImage()));
    connect(button_circle, SIGNAL(clicked()), this, SLOT(circleImage()));
    connect(spinbox_canny, SIGNAL(valueChanged(int)), slider_canny, SLOT(setValue(int)));
    connect(slider_canny, SIGNAL(valueChanged(int)), spinbox_canny, SLOT(setValue(int)));

    QLabel *label_lineThreshold = new QLabel(tr("线检测阈值"));
    spinbox_lineThreshold = new QSpinBox;						// HoughLine
    spinbox_lineThreshold->setRange(0, 500);
    spinbox_lineThreshold->setValue(50);
    QSlider *slider_lineThreshold = new QSlider(Qt::Horizontal);
    slider_lineThreshold->setRange(0, 500);
    slider_lineThreshold->setValue(50);
    connect(spinbox_lineThreshold, SIGNAL(valueChanged(int)), slider_lineThreshold, SLOT(setValue(int)));
    connect(slider_lineThreshold, SIGNAL(valueChanged(int)), spinbox_lineThreshold, SLOT(setValue(int)));
    QLabel *label_minLineLength = new QLabel(tr("线段最小长度"));
    spinbox_minLineLength = new QSpinBox;
    spinbox_minLineLength->setRange(0, 500);
    spinbox_minLineLength->setValue(50);
    QSlider *slider_minLineLength = new QSlider(Qt::Horizontal);
    slider_minLineLength->setRange(0, 500);
    slider_minLineLength->setValue(50);
    connect(spinbox_minLineLength, SIGNAL(valueChanged(int)), slider_minLineLength, SLOT(setValue(int)));
    connect(slider_minLineLength, SIGNAL(valueChanged(int)), spinbox_minLineLength, SLOT(setValue(int)));

    QLabel *label_maxLineGap = new QLabel(tr("允许最大间隔"));
    spinbox_maxLineGap = new QSpinBox;
    spinbox_maxLineGap->setRange(0, 500);
    spinbox_maxLineGap->setValue(10);
    QSlider *slider_maxLineGap = new QSlider(Qt::Horizontal);
    slider_maxLineGap->setRange(0, 500);
    slider_maxLineGap->setValue(50);
    connect(spinbox_maxLineGap, SIGNAL(valueChanged(int)), slider_maxLineGap, SLOT(setValue(int)));
    connect(slider_maxLineGap, SIGNAL(valueChanged(int)), spinbox_maxLineGap, SLOT(setValue(int)));

    QLabel *label_minRadius = new QLabel(tr("最小半径"));
    spinbox_minRadius = new QSpinBox;
    spinbox_minRadius->setRange(0, 1000);
    spinbox_minRadius->setValue(1);
    QSlider *slider_minRadius = new QSlider(Qt::Horizontal);
    slider_minRadius->setRange(0, 1000);
    slider_minRadius->setValue(1);
    connect(spinbox_minRadius, SIGNAL(valueChanged(int)), slider_minRadius, SLOT(setValue(int)));
    connect(slider_minRadius, SIGNAL(valueChanged(int)), spinbox_minRadius, SLOT(setValue(int)));

    QLabel *label_maxRadius = new QLabel(tr("最大半径"));
    spinbox_maxRadius = new QSpinBox;
    spinbox_maxRadius->setRange(0, 1000);
    spinbox_maxRadius->setValue(100);
    QSlider *slider_maxRadius = new QSlider(Qt::Horizontal);
    slider_maxRadius->setRange(0, 1000);
    slider_maxRadius->setValue(100);
    connect(spinbox_maxRadius, SIGNAL(valueChanged(int)), slider_maxRadius, SLOT(setValue(int)));
    connect(slider_maxRadius, SIGNAL(valueChanged(int)), spinbox_maxRadius, SLOT(setValue(int)));

    // 格栅布局
    QGridLayout *enhanceLayout = new QGridLayout();
    enhanceLayout->setAlignment(Qt::AlignTop);
    enhanceLayout->setMargin(30);

    enhanceLayout->addWidget(label_smooth, 0, 0, 1, 1);
    enhanceLayout->addWidget(label_coreSmooth, 1, 1, 1, 1);
    enhanceLayout->addWidget(combo_smooth, 1, 2, 1, 1);
    enhanceLayout->addWidget(button_Normalized, 2, 2, 1, 1);
    enhanceLayout->addWidget(button_Gaussian, 3, 2, 1, 1);
    enhanceLayout->addWidget(button_Median, 4, 2, 1, 1);

    enhanceLayout->addWidget(label_sharpen, 5, 0, 1, 1);
    enhanceLayout->addWidget(label_coreSharpen, 6, 1, 1, 1);
    enhanceLayout->addWidget(combo_sharpen, 6, 2, 1, 1);
    enhanceLayout->addWidget(button_sobel, 7, 2, 1, 1);
    enhanceLayout->addWidget(button_laplacian, 8, 2, 1, 1);
    enhanceLayout->addWidget(button_canny, 9, 2, 1, 1);

    enhanceLayout->addWidget(label_canny, 10, 1, 1, 1);
    enhanceLayout->addWidget(slider_canny, 10, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_canny, 10, 3, 1, 1);

    enhanceLayout->addWidget(button_line, 11, 2, 1, 1);
    enhanceLayout->addWidget(label_lineThreshold, 12, 1, 1, 1);
    enhanceLayout->addWidget(slider_lineThreshold, 12, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_lineThreshold, 12, 3, 1, 1);

    enhanceLayout->addWidget(label_minLineLength, 13, 1, 1, 1);
    enhanceLayout->addWidget(slider_minLineLength, 13, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_minLineLength, 13, 3, 1, 1);

    enhanceLayout->addWidget(label_maxLineGap, 14, 1, 1, 1);
    enhanceLayout->addWidget(slider_maxLineGap, 14, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_maxLineGap, 14, 3, 1, 1);

    enhanceLayout->addWidget(button_circle, 15, 2, 1, 1);
    enhanceLayout->addWidget(label_minRadius, 16, 1, 1, 1);
    enhanceLayout->addWidget(slider_minRadius, 16, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_minRadius, 16, 3, 1, 1);

    enhanceLayout->addWidget(label_maxRadius, 17, 1, 1, 1);
    enhanceLayout->addWidget(slider_maxRadius, 17, 2, 1, 1);
    enhanceLayout->addWidget(spinbox_maxRadius, 17, 3, 1, 1);

    dock_Enhance->setFixedWidth(420);
    dock_Enhance->setLayout(enhanceLayout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(dock_Enhance);
    ui->image_stackedwidget->addWidget(scrollArea);
}

void FormImageHandle::WinMorp() {// 形态学处理窗口
    dock_Morp = new QWidget(this);
    // Morp
    QSpinBox *spinbox_erode, *spinbox_dilate;
    QSpinBox *spinbox_open, *spinbox_close;
    //QSpinBox *spinbox_tophat, *spinbox_blackhat;
    //QSpinBox *spinbox_hitmiss;
    QComboBox *combo_kernel, *combo_elem;


    QLabel *label_kernel = new QLabel();
    label_kernel->setText(tr("模板大小"));
    combo_kernel = new QComboBox();
    combo_kernel->addItem(tr("3×3"));
    combo_kernel->addItem(tr("5×5"));
    combo_kernel->addItem(tr("7×7"));
    combo_kernel->addItem(tr("9×9"));
    combo_kernel->addItem(tr("11×11"));
    combo_kernel->addItem(tr("13×13"));
    combo_kernel->addItem(tr("15×15"));
    combo_kernel->addItem(tr("17×17"));
    combo_kernel->addItem(tr("19×19"));
    combo_kernel->addItem(tr("21×21"));

    QLabel *label_elem = new QLabel();
    label_elem->setText(tr("结构元素"));
    combo_elem = new QComboBox();
    combo_elem->addItem(tr("矩形"));
    combo_elem->addItem(tr("十字形"));
    combo_elem->addItem(tr("椭圆形"));

    QLabel *label_erode = new QLabel();
    label_erode->setText(tr("腐蚀"));
    QLabel *label_erodeCount = new QLabel();
    label_erodeCount->setText(tr("次"));
    spinbox_erode = new QSpinBox;
    spinbox_erode->setRange(1, 50);
    spinbox_erode->setValue(1);
    QPushButton *button_erode = new QPushButton();			// 确定按钮
    button_erode->setText(tr("腐蚀"));

    QLabel *label_dilate = new QLabel();
    label_dilate->setText(tr("膨胀"));
    QLabel *label_dilateCount = new QLabel();
    label_dilateCount->setText(tr("次"));
    spinbox_dilate = new QSpinBox;
    spinbox_dilate->setRange(1, 50);
    spinbox_dilate->setValue(1);
    QPushButton *button_dilate = new QPushButton();			// 确定按钮
    button_dilate->setText(tr("膨胀"));

    QLabel *label_open = new QLabel();
    label_open->setText(tr("开运算"));
    QLabel *label_openCount = new QLabel();
    label_openCount->setText(tr("次"));
    spinbox_open = new QSpinBox;
    spinbox_open->setRange(1, 50);
    spinbox_open->setValue(1);
    QPushButton *button_open = new QPushButton();			// 确定按钮
    button_open->setText(tr("开运算"));

    QLabel *label_close = new QLabel();
    label_close->setText(tr("闭运算"));
    QLabel *label_closeCount = new QLabel();
    label_closeCount->setText(tr("次"));
    spinbox_close = new QSpinBox;
    spinbox_close->setRange(1, 50);
    spinbox_close->setValue(1);
    QPushButton *button_close = new QPushButton();			// 确定按钮
    button_close->setText(tr("闭运算"));

    QLabel *label_grad = new QLabel();
    label_grad->setText(tr("形态学梯度"));
    QPushButton *button_grad = new QPushButton();			// 确定按钮
    button_grad->setText(tr("形态学梯度"));

    QLabel *label_tophat = new QLabel();
    label_tophat->setText(tr("顶帽操作"));
    QPushButton *button_tophat = new QPushButton();			// 确定按钮
    button_tophat->setText(tr("顶帽操作"));

    QLabel *label_blackhat = new QLabel();
    label_blackhat->setText(tr("黑帽操作"));
    QPushButton *button_blackhat = new QPushButton();			// 确定按钮
    button_blackhat->setText(tr("黑帽操作"));

    connect(button_erode, SIGNAL(clicked()), this, SLOT(erodeImage()));
    connect(button_dilate, SIGNAL(clicked()), this, SLOT(dilateImage()));
    connect(button_open, SIGNAL(clicked()), this, SLOT(openImage()));
    connect(button_close, SIGNAL(clicked()), this, SLOT(closeImage()));
    connect(button_grad, SIGNAL(clicked()), this, SLOT(gradImage()));
    connect(button_tophat, SIGNAL(clicked()), this, SLOT(tophatImage()));
    connect(button_blackhat, SIGNAL(clicked()), this, SLOT(blackhatImage()));

    QGridLayout *morpLayout = new QGridLayout();
    morpLayout->setAlignment(Qt::AlignTop);
    morpLayout->setMargin(30);

    morpLayout->addWidget(label_kernel, 0, 1, 1, 1);
    morpLayout->addWidget(combo_kernel, 0, 2, 1, 1);
    morpLayout->addWidget(label_elem, 1, 1, 1, 1);
    morpLayout->addWidget(combo_elem, 1, 2, 1, 1);

    morpLayout->addWidget(label_erode, 2, 0, 1, 1);
    morpLayout->addWidget(button_erode, 3, 1, 1, 1);
    morpLayout->addWidget(spinbox_erode, 3, 2, 1, 1);
    morpLayout->addWidget(label_erodeCount, 3, 3, 1, 1);

    morpLayout->addWidget(label_dilate, 4, 0, 1, 1);
    morpLayout->addWidget(button_dilate, 5, 1, 1, 1);
    morpLayout->addWidget(spinbox_dilate, 5, 2, 1, 1);
    morpLayout->addWidget(label_dilateCount, 5, 3, 1, 1);

    morpLayout->addWidget(label_open, 6, 0, 1, 1);
    morpLayout->addWidget(button_open, 7, 1, 1, 1);
    morpLayout->addWidget(spinbox_open, 7, 2, 1, 1);
    morpLayout->addWidget(label_openCount, 7, 3, 1, 1);

    morpLayout->addWidget(label_close, 8, 0, 1, 1);
    morpLayout->addWidget(button_close, 9, 1, 1, 1);
    morpLayout->addWidget(spinbox_close, 9, 2, 1, 1);
    morpLayout->addWidget(label_closeCount, 9, 3, 1, 1);

    morpLayout->addWidget(label_tophat, 10, 0, 1, 1);
    morpLayout->addWidget(button_tophat, 11, 1, 1, 1);
    morpLayout->addWidget(label_blackhat, 12, 0, 1, 1);
    morpLayout->addWidget(button_blackhat, 13, 1, 1, 1);
    morpLayout->addWidget(label_grad, 14, 0, 1, 1);
    morpLayout->addWidget(button_grad, 15, 1, 1, 1);

    dock_Morp->setFixedWidth(420);
    dock_Morp->setLayout(morpLayout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(dock_Morp);
    ui->image_stackedwidget->addWidget(scrollArea);
}

void FormImageHandle::WinColor() {// 颜色模型窗口
    dock_Color = new QWidget(this);

    QLabel *null = new QLabel(tr("	"));
    QLabel *label_RGB = new QLabel(tr("RGB模型"));
    QPushButton *button_R = new QPushButton(tr("R分量图"));
    QPushButton *button_G = new QPushButton(tr("G分量图"));
    QPushButton *button_B = new QPushButton(tr("B分量图"));

    connect(button_R, SIGNAL(clicked()), this, SLOT(splitR()));
    connect(button_G, SIGNAL(clicked()), this, SLOT(splitG()));
    connect(button_B, SIGNAL(clicked()), this, SLOT(splitB()));

    QLabel *label_HSV = new QLabel(tr("HSV模型"));
    QPushButton *button1_H = new QPushButton(tr("H分量图"));
    QPushButton *button1_S = new QPushButton(tr("S分量图"));
    QPushButton *button1_V = new QPushButton(tr("V分量图"));

    connect(button1_H, SIGNAL(clicked()), this, SLOT(splitH_HSV()));
    connect(button1_S, SIGNAL(clicked()), this, SLOT(splitS_HSV()));
    connect(button1_V, SIGNAL(clicked()), this, SLOT(splitV_HSV()));

    QLabel *label_YUV = new QLabel(tr("YUV模型"));
    QPushButton *button2_Y = new QPushButton(tr("Y分量图"));
    QPushButton *button2_U = new QPushButton(tr("U分量图"));
    QPushButton *button2_V = new QPushButton(tr("V分量图"));

    connect(button2_Y, SIGNAL(clicked()), this, SLOT(splitY_YUV()));
    connect(button2_U, SIGNAL(clicked()), this, SLOT(splitU_YUV()));
    connect(button2_V, SIGNAL(clicked()), this, SLOT(splitV_YUV()));

    QLabel *label_HLS = new QLabel(tr("HLS模型"));
    QPushButton *button3_H = new QPushButton(tr("H分量图"));
    QPushButton *button3_L = new QPushButton(tr("L分量图"));
    QPushButton *button3_S = new QPushButton(tr("S分量图"));

    connect(button3_H, SIGNAL(clicked()), this, SLOT(splitH_HLS()));
    connect(button3_L, SIGNAL(clicked()), this, SLOT(splitL_HLS()));
    connect(button3_S, SIGNAL(clicked()), this, SLOT(splitS_HLS()));

    QGridLayout *colorLayout = new QGridLayout();
    colorLayout->setAlignment(Qt::AlignTop);
    colorLayout->setMargin(30);

    colorLayout->addWidget(label_RGB, 0, 0, 1, 1);
    colorLayout->addWidget(button_R, 1, 1, 1, 1);
    colorLayout->addWidget(button_G, 1, 2, 1, 1);
    colorLayout->addWidget(button_B, 1, 3, 1, 1);

    colorLayout->addWidget(null, 5, 0, 1, 1);
    colorLayout->addWidget(label_HSV, 6, 0, 1, 1);
    colorLayout->addWidget(button1_H, 7, 1, 1, 1);
    colorLayout->addWidget(button1_S, 7, 2, 1, 1);
    colorLayout->addWidget(button1_V, 7, 3, 1, 1);

    colorLayout->addWidget(null, 10, 0, 1, 1);
    colorLayout->addWidget(label_YUV, 11, 0, 1, 1);
    colorLayout->addWidget(button2_Y, 12, 1, 1, 1);
    colorLayout->addWidget(button2_U, 12, 2, 1, 1);
    colorLayout->addWidget(button2_V, 12, 3, 1, 1);

    colorLayout->addWidget(null, 15, 0, 1, 1);
    colorLayout->addWidget(label_HLS, 16, 0, 1, 1);
    colorLayout->addWidget(button3_H, 17, 1, 1, 1);
    colorLayout->addWidget(button3_L, 17, 2, 1, 1);
    colorLayout->addWidget(button3_S, 17, 3, 1, 1);

    dock_Color->setFixedWidth(420);
    dock_Color->setLayout(colorLayout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(dock_Color);
    ui->image_stackedwidget->addWidget(scrollArea);
}

void FormImageHandle::WinTest() {// 测试窗口
    dock_Test = new QWidget(this);
    QLabel *label_RGB = new QLabel(tr("测试"));
    QPushButton *button_R = new QPushButton(tr("最短路径提取控件"));
    QPushButton *button_G = new QPushButton(tr("边缘修正控件"));
    connect(button_R, &QPushButton::clicked,
    this, [ = ] {
        emit SingalImageMenuOut(601);
    });
    connect(button_G, &QPushButton::clicked,
    this, [ = ] {
        emit SingalImageMenuOut(602);
    });


    QGridLayout *testLayout = new QGridLayout();
    testLayout->setAlignment(Qt::AlignTop);
    testLayout->setMargin(30);

    testLayout->addWidget(label_RGB, 0, 0);
    testLayout->addWidget(button_R, 1, 1);
    testLayout->addWidget(button_G, 2, 1);

    dock_Test->setFixedWidth(420);
    dock_Test->setLayout(testLayout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(dock_Test);
    ui->image_stackedwidget->addWidget(scrollArea);
}
