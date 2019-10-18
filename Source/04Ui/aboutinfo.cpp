#include "aboutinfo.h"
#include "ui_aboutinfo.h"

AboutInfo::AboutInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutInfo) {
    ui->setupUi(this);
    this->Initial();
}

AboutInfo::~AboutInfo() {
    delete ui;
}

void AboutInfo::Initial() {
    ui->logo_label->setFixedSize(50, 50);
    this->setFixedSize(300, 75);
}
