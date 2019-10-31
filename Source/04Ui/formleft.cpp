//01frame
#include "formleft.h"
#include "ui_formleft.h"

FormLeft::FormLeft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLeft) {
    ui->setupUi(this);
    initFrom();
}

void FormLeft::initFrom() {
    // CPU内存显示控件
    ui->label_cpu->start(1000);
    // 滑动导航条控件
    ui->slider_bar->setItems("Image      Brower;"
                             "Mode        Brower;"
                             "Dcm          Brower;"
                             "Images    Brower");
    connect(ui->slider_bar, &SliderBar::currentItemChanged,
            this, &FormLeft::SingalSliderBarMovtToOut);
    connect(this, &FormLeft::SingalSliderBarMovtToIn,
            ui->slider_bar, &SliderBar::setCurrentIndex);

    // 按钮逻辑
    QList<QPushButton *> btns = ui->widget_menubar3->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        connect(btn, &QPushButton::clicked,
                this, &FormLeft::SlotAllBtnEnabledFalse);
    }
    // 菜单栏显示隐藏逻辑
    SlotMenuBarSwitching();
    connect(ui->btn_menubar1, &QPushButton::clicked,
            this, &FormLeft::SlotMenuBarSwitching);
    connect(ui->btn_menubar2, &QPushButton::clicked,
            this, &FormLeft::SlotMenuBarSwitching);
    connect(ui->btn_menubar3, &QPushButton::clicked,
            this, &FormLeft::SlotMenuBarSwitching);

    // stl操作
    connect(ui->btn_division, &QPushButton::clicked, this, [ = ] { // v自动提取连通域
        emit SignalsPolyDataHandle(1);
    });
    connect(ui->btn_line_clipper, &QPushButton::clicked, this,  [ = ] { // v直线剪裁
        emit SignalsPolyDataHandle(2);
    });
    connect(ui->btn_cut, &QPushButton::clicked, this,  [ = ] { // v修剪
        emit SignalsPolyDataHandle(3);
    });
    connect(ui->btn_smoothing, &QPushButton::clicked, this, [ = ] { // v平滑
        emit SignalsPolyDataHandle(4);
    });
    connect(ui->btn_subdivision, &QPushButton::clicked, this, [ = ] { // v细分
        emit SignalsPolyDataHandle(5);
    });
    connect(ui->btn_refine, &QPushButton::clicked, this, [ = ] { // v细化
        emit SignalsPolyDataHandle(6);
    });
    connect(ui->btn_cgal_subdivision, &QPushButton::clicked, this,  [ = ] {// C细分
        emit SignalsPolyDataHandle(11);
    });
    connect(ui->btn_cgal_intersection, &QPushButton::clicked, this,  [ = ] { // 相交
        emit SignalsPolyDataHandle(12);
    });
    connect(ui->btn_cgal_fill, &QPushButton::clicked, this,  [ = ] { // C封闭
        emit SignalsPolyDataHandle(13);
    });
    connect(ui->btn_readstl, &QPushButton::clicked, this,  [ = ] { // 载入文件
        emit SignalsPolyDataHandle(21);
        emit SingalSliderBarMovtToIn(1);
        emit SingalSliderBarMovtToOut(1);
    });
    connect(ui->btn_writestl, &QPushButton::clicked, this,  [ = ] { // 保存
        emit SignalsPolyDataHandle(22);
    });
    connect(ui->btn_undo, &QPushButton::clicked, this,  [ = ] { // 撤销
        emit SignalsPolyDataHandle(23);
    });
}

void FormLeft::SlotMenuBarSwitching() {
    if (ui->btn_menubar1->isChecked()) {
        ui->widget_menubar1->show();
    } else {
        ui->widget_menubar1->hide();
    }
    if (ui->btn_menubar2->isChecked()) {
        ui->widget_menubar2->show();
    } else {
        ui->widget_menubar2->hide();
    }
    if (ui->btn_menubar3->isChecked()) {
        ui->widget_menubar3->show();
    } else {
        ui->widget_menubar3->hide();
    }
    if (ui->btn_menubar1->isChecked() ||
            ui->btn_menubar2->isChecked() ||
            ui->btn_menubar3->isChecked()) {
        ui->label_menubar1->show();
        ui->label_menubar2->show();
        ui->label_menubar3->show();
        ui->textedit_information->show();
        ui->slider_bar->show();
    } else {
        ui->widget_menubar1->hide();
        ui->widget_menubar2->hide();
        ui->widget_menubar3->hide();
        ui->textedit_information->hide();
        ui->label_menubar1->hide();
        ui->label_menubar2->hide();
        ui->label_menubar3->hide();
        ui->slider_bar->hide();
    }
}

FormLeft::~FormLeft() {
    delete ui;
}

void FormLeft::SlotAllBtnEnabledFalse() {
    QList<QPushButton *> btns = ui->widget_menubar3->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setEnabled(false);
    }
}


void FormLeft::SlotAllBtnEnabledTrue() {
    QList<QPushButton *> btns = ui->widget_menubar3->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setEnabled(true);
    }
}

// 正常提示信息(白色)
void FormLeft::SlotPromptInformation(const QString &text) {
    QString output = QString("<font color=\"white\">%1</font><br>")
                     .arg(text);
    output = output.replace("\n", "<br/>");
    ui->textedit_information->setText(output);
}






