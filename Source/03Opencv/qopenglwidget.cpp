#include "qopenglwidget.h"
#include "ui_qopenglwidget.h"

QOpenglWidget::QOpenglWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QOpenglWidget)
{
    ui->setupUi(this);
}

QOpenglWidget::~QOpenglWidget()
{
    delete ui;
}
