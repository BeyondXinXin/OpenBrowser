#include "qopencvwidget.h"

QOpencvWidget::QOpencvWidget(QWidget *parent) :
    QWidget(parent) {
    this->Initial();
}

QOpencvWidget::~QOpencvWidget() {

}

void QOpencvWidget::SetSurface(const QImage value) {
    img_ = value;
    opencv_pixmap_->setPixmap(QPixmap::fromImage(img_));
}

QImage QOpencvWidget::GetSurface() {
    return img_;
}

void QOpencvWidget::Initial() {

    this->setObjectName(QStringLiteral("QOpencvWidget"));
    this->resize(1002, 647);

    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    graphicsView = new QOpencvView(this);
    gridLayout->addWidget(graphicsView, 0, 0, 1, 1);
    opencv_scene_ = new QOpencvScene;
    opencv_pixmap_ = new QOpencvPixmapItem;
    opencv_pixmap_->setZValue(0);
    opencv_scene_->addItem(opencv_pixmap_);
    graphicsView->setScene(opencv_scene_);
    graphicsView->show();
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->scale(1.1, 1.1);
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
