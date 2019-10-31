#include "qoencvscrollarea.h"


QOpencvScrollArea::QOpencvScrollArea(QWidget *parent) :
    QScrollArea(parent) {
    //初始化
    this->can_move_ = false;
    this->move_star_ = false;
    this->continuous_move_ = false;
    this->mouse_point_ = QPoint(0, 0);
    this->setAlignment(Qt::AlignCenter);
//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //绑定事件过滤器
    installEventFilter(this);
}


QOpencvScrollArea::~QOpencvScrollArea() {

}



void QOpencvScrollArea::SetCanMove(const bool can_move) {
    this->can_move_ = can_move;
}

//事件过滤器
bool QOpencvScrollArea::eventFilter(QObject *obj, QEvent *evt) {
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
                    if (!continuous_move_
                            && (offsetx > -10 && offsetx < 10)
                            && (offsety > -10 && offsety < 10)) {
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
            if (wheelEvent->delta() > 100) {
                emit SignalBigOut();
                return true;
            } else if (wheelEvent->delta() < -100) {
                emit SignalSmallOut();
                return true;
            } else {
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, evt);
}

QOpencvLbel::QOpencvLbel(QWidget *parent): QLabel(parent) {
    this->setMouseTracking(true);

}

void QOpencvLbel::SetImage(QImage img) {
    image_ = img;
}


QImage QOpencvLbel::GetImage() {
    return image_;
}

void QOpencvLbel::mouseMoveEvent(QMouseEvent *event) {
    QColor color = image_.pixel(event->pos());
    int mousedPressed_R = color.red();
    int mousedPressed_G = color.green();
    int mousedPressed_B = color.blue();
    QString text = QString("%1,%2,%3")
                   .arg(mousedPressed_R).arg(mousedPressed_G).arg(mousedPressed_B);
    emit SignalImgPointOut(event->pos(), text);
    event->accept();
}

void QOpencvLbel::leaveEvent(QEvent *) {
    emit SignalLeaveOut();
}
