#include "qopencvwidget.h"
#include "ui_qopencvwidget.h"

QOpencvWidget::QOpencvWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QOpencvWidget) {
    ui->setupUi(this);
    this->Initial();
}

QOpencvWidget::~QOpencvWidget() {
    delete ui;
}

void QOpencvWidget::Initial() {
    opencv_pixmap_ = new QOpencvPixmapItem;
    opencv_scene_ = new QOpencvScene;
    opencv_pixmap_->setZValue(0);
    opencv_pixmap_->setPixmap(QPixmap("000.jpg"));
    opencv_scene_->addItem(opencv_pixmap_);
    ui->graphicsView->setScene(opencv_scene_);
    ui->graphicsView->show();
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->scale(1.1, 1.1);
}





QOpencvPixmapItem::QOpencvPixmapItem(QGraphicsPixmapItem *parent):
    QGraphicsPixmapItem(parent) {
}

QOpencvPixmapItem::~QOpencvPixmapItem() {

}
QOpencvScene::QOpencvScene(QGraphicsScene *parent):
    QGraphicsScene(parent) {
}

QOpencvScene::~QOpencvScene() {

}

QOpencvView::QOpencvView(QWidget *parent):
    QGraphicsView(parent) {
}

QOpencvView::~QOpencvView() {
}

void QOpencvView::wheelEvent(QWheelEvent *event) {
    if (event->delta() > 0) {
        this->scale(1.1, 1.1);
    } else {
        this->scale(0.9, 0.9);
    }
}
