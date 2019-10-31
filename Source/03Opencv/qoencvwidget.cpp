#include "qoencvwidget.h"
#include "ui_qoencvwidget.h"

QOpencvWidget::QOpencvWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QOencvWidget) {
    ui->setupUi(this);
    this->Initialization();
}

QOpencvWidget::~QOpencvWidget() {
    delete ui;
}

void QOpencvWidget::Initialization() {
    scrollarea_ = new QOpencvScrollArea;
    label_ = new QOpencvLbel;
    img_zoomsize_ = 1.0;
    /*图片显示初始化*/
    img_ =  QImage("0.png");
    label_->SetImage(img_);
    label_->setPixmap(QPixmap::fromImage(img_));
    label_->setFixedSize(img_.width(), img_.height());
    label_->setScaledContents(1);

    scrollarea_->setWidget(label_);
    scrollarea_->SetCanMove(1);
    QVBoxLayout *layout_1 = new QVBoxLayout(ui->img_widget);
    layout_1->addWidget(scrollarea_);

    connect(scrollarea_, &QOpencvScrollArea::SignalBigOut,
            this, &QOpencvWidget::SlotImgBigIn);
    connect(scrollarea_, &QOpencvScrollArea::SignalSmallOut,
            this, &QOpencvWidget::SlotImgSmallIn);

    connect(label_, &QOpencvLbel::SignalImgPointOut,
            this, &QOpencvWidget::SlotImgPointIn);
    connect(label_, &QOpencvLbel::SignalLeaveOut,
            this, &QOpencvWidget::SlotLeaveIn);

}

void QOpencvWidget::SlotImgBigIn() {
    if (img_zoomsize_ > 2) {
        return;
    }
    img_zoomsize_ += .01;
    label_->setFixedSize(static_cast<int>(img_.width() * img_zoomsize_),
                         static_cast<int>(img_.height() * img_zoomsize_));
}

void QOpencvWidget::SlotImgSmallIn() {
    if (img_zoomsize_ < 0.5) {
        return;
    }
    img_zoomsize_ -= .01;
    label_->setFixedSize(static_cast<int>(img_.width() * img_zoomsize_),
                         static_cast<int>(img_.height() * img_zoomsize_));
}

void QOpencvWidget::SlotImgPointIn(const QPoint poi, const QString text) {
    int x = poi.x();
    int y = poi.y();
    ui->current_linedit_rgb->setText(text);
    ui->current_linedit_x->setText(QString::number(x));
    ui->current_linedit_y->setText(QString::number(y));
}

void QOpencvWidget::SlotLeaveIn() {
    ui->current_linedit_rgb->setText("");
    ui->current_linedit_x->setText("");
    ui->current_linedit_y->setText("");
}








































