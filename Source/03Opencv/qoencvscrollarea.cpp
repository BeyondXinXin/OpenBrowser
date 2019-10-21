#include "qoencvscrollarea.h"


QOencvScrollArea::QOencvScrollArea(QWidget *parent) :
    QScrollArea(parent)
    , canMove(true)
    , mMoveStart(false)
    , min_label_width(100)
    , min_label_heigh(100)
    , big_label_size(100)
    , small_label_size(100)
    , mContinuousMove(false)
    , mMousePoint(QPoint(0, 0)) {
    label = new QLabel();
    label->setFixedSize(500, 500);
    this->setWidget(label);
    this->setMaximumHeight(768);
    this->setMaximumWidth(1024);
    installEventFilter(this);
}

QOencvScrollArea::~QOencvScrollArea() {
    if (label) {
        delete label;
    }
}

void QOencvScrollArea::set_image(QString filename) {
    myScrollArea_img = new QImage(filename);
    label->setPixmap(QPixmap::fromImage(*myScrollArea_img));
    return;
}

QImage QOencvScrollArea::get_image() {
    return *myScrollArea_img;
}

//事件过滤器
bool QOencvScrollArea::eventFilter(QObject *obj, QEvent *evt) {
    if (canMove) {
        //鼠标拖动移动
        if (evt->type() == QEvent::MouseMove) {
            QMouseEvent *me = (QMouseEvent *) evt;
            if (me->buttons() & Qt::LeftButton) {
                if (!mMoveStart) {
                    mMoveStart = true;
                    mContinuousMove = false;
                    mMousePoint = me->globalPos();
                } else {
                    QScrollBar *scrollBarx = horizontalScrollBar();
                    QScrollBar *scrollBary = verticalScrollBar();
                    QPoint p = me->globalPos();
                    int offsetx = p.x() - mMousePoint.x();
                    int offsety = p.y() - mMousePoint.y();
                    if (!mContinuousMove && (offsetx > -10 && offsetx < 10) && (offsety > -10 && offsety < 10)) {
                        return false;
                    }
                    mContinuousMove = true;
                    scrollBarx->setValue(scrollBarx->value() - offsetx);
                    scrollBary->setValue(scrollBary->value() - offsety);
                    mMousePoint = p;
                    setCursor(Qt::SizeAllCursor);
                }
                return true;
            }
        } else if (evt->type() == QEvent::MouseButtonRelease) {
            mMoveStart = false;
            setCursor(Qt::ArrowCursor);
        }
        //滚轮放大缩小
        if (evt->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(evt);
            QScrollBar *scrollBarx = horizontalScrollBar();
            QScrollBar *scrollBary = verticalScrollBar();
            if (wheelEvent->delta() > 100) {
                scrollBarx->setValue(scrollBarx->value() + big_label_size / 2);
                scrollBary->setValue(scrollBary->value() + big_label_size / 2);
                label->setFixedSize(label->width() + big_label_size, label->height() + big_label_size);
                return true;
            } else if (wheelEvent->delta() < -100) {
                if (label->width() < min_label_width) {
                    return true;
                }
                if (label->height() < min_label_heigh) {
                    return true;
                }
                scrollBarx->setValue(scrollBarx->value() - small_label_size / 2);
                scrollBary->setValue(scrollBary->value() - small_label_size / 2);
                label->setFixedSize(label->width() - small_label_size, label->height() - small_label_size);
                return true;
            } else {
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, evt);
}
