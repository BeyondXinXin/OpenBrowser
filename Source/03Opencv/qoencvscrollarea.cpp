#include "qoencvscrollarea.h"


QOencvScrollArea::QOencvScrollArea(QWidget *parent) :
    QScrollArea(parent) {
    //初始化
    label_ = new QLabel();
    label_->setFixedSize(500, 500);
    this->setWidget(label_);
    this->setMaximumHeight(768);
    this->setMaximumWidth(1024);
    this->can_move_ = true;
    this->move_star_ = false;
    this->continuous_move_ = false;
    this->big_label_size_ = 100;
    this->small_label_size_ = 100;
    this->mouse_point_ = QPoint(0, 0);
    //绑定事件过滤器
    installEventFilter(this);
}

QOencvScrollArea::~QOencvScrollArea() {
    if (label_) {
        delete label_;
    }
}

void QOencvScrollArea::SetImage(const QString filename) {
    img_ = new QImage(filename);
    label_->setPixmap(QPixmap::fromImage(*img_));
    return;
}

QImage QOencvScrollArea::GetImage() {
    return *img_;
}

void QOencvScrollArea::SetCanMove(const bool can_move) {
    this->can_move_ = can_move;
}

//事件过滤器
bool QOencvScrollArea::eventFilter(QObject *obj, QEvent *evt) {
    if (can_move_) {
        //鼠标拖动移动
        if (evt->type() == QEvent::MouseMove) {
            QMouseEvent *me =  static_cast<QMouseEvent *>(evt);
            if (me->buttons() & Qt::LeftButton) {
                if (!move_star_) {
                    move_star_ = true;
                    continuous_move_ = false;
                    mouse_point_ = me->globalPos();
                } else {
                    QScrollBar *scrollBarx = horizontalScrollBar();
                    QScrollBar *scrollBary = verticalScrollBar();
                    QPoint p = me->globalPos();
                    int offsetx = p.x() - mouse_point_.x();
                    int offsety = p.y() - mouse_point_.y();
                    if (!continuous_move_ && (offsetx > -10 && offsetx < 10) && (offsety > -10 && offsety < 10)) {
                        return false;
                    }
                    continuous_move_ = true;
                    scrollBarx->setValue(scrollBarx->value() - offsetx);
                    scrollBary->setValue(scrollBary->value() - offsety);
                    mouse_point_ = p;
                    setCursor(Qt::SizeAllCursor);
                }
                return true;
            }
        } else if (evt->type() == QEvent::MouseButtonRelease) {
            move_star_ = false;
            setCursor(Qt::ArrowCursor);
        }
        //滚轮放大缩小
        if (evt->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(evt);
            QScrollBar *scrollBarx = horizontalScrollBar();
            QScrollBar *scrollBary = verticalScrollBar();
            if (wheelEvent->delta() > 100) {
                scrollBarx->setValue(scrollBarx->value() + big_label_size_ / 2);
                scrollBary->setValue(scrollBary->value() + big_label_size_ / 2);
                label_->setFixedSize(label_->width() + big_label_size_, label_->height() + big_label_size_);
                return true;
            } else if (wheelEvent->delta() < -100) {
                if (label_->width() < min_label_size_.width()) {
                    return true;
                }
                if (label_->height() < min_label_size_.height()) {
                    return true;
                }
                scrollBarx->setValue(scrollBarx->value() - small_label_size_ / 2);
                scrollBary->setValue(scrollBary->value() - small_label_size_ / 2);
                label_->setFixedSize(label_->width() - small_label_size_, label_->height() - small_label_size_);
                return true;
            } else {
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, evt);
}
