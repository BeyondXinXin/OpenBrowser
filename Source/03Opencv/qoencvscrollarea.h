#ifndef QOENCVSCROLLAREA_H
#define QOENCVSCROLLAREA_H

// 01frame includes
#include "app.h"
class QOpencvScrollArea: public QScrollArea {
    Q_OBJECT
  public:
    explicit QOpencvScrollArea(QWidget *parent = nullptr);
    ~QOpencvScrollArea() ;

  public:
    void SetCanMove(const bool can_move);
  Q_SIGNALS:
    void SignalBigOut();
    void SignalSmallOut();
  protected:
    bool eventFilter(QObject *obj, QEvent *evt) ;
  private:
    bool can_move_;// 是否可以移动
    bool move_star_;// 是否移动开始
    bool continuous_move_;// 是否正在连续移动
    QPoint mouse_point_;// 鼠标点击位置

};


class QOpencvLbel : public QLabel {
    Q_OBJECT        //信号槽相关
  public:
    explicit QOpencvLbel(QWidget *parent = nullptr);
    void SetImage(QImage img);
    QImage GetImage();
  Q_SIGNALS:
    void  SignalImgPointOut(const QPoint, const QString);
    void  SignalLeaveOut();
  protected:
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *);
  private:
    QImage image_;
};






#endif // QOENCVSCROLLAREA_H
