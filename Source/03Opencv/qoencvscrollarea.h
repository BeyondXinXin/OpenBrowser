#ifndef QOENCVSCROLLAREA_H
#define QOENCVSCROLLAREA_H

// 01frame includes
#include "app.h"

class QOencvScrollArea: public QScrollArea {
    Q_OBJECT
  public:
    explicit QOencvScrollArea(QWidget *parent = nullptr);
    ~QOencvScrollArea();

  public:
    void SetImage(const QString filename);// 设置显示图片
    QImage GetImage();// 获取图片
    void SetCanMove(const bool can_move);

  protected:
    bool eventFilter(QObject *obj, QEvent *evt);

  private:
    QLabel *label_;// 显示图片
    QImage *img_;// 显示label
    bool can_move_;// 是否可以移动
    bool move_star_;// 是否移动开始
    bool continuous_move_;// 是否正在连续移动
    QSize min_label_size_;// 图片最小尺寸
    QPoint mouse_point_;// 鼠标点击位置
    qint32 big_label_size_; // 滚轮放大增加尺寸
    qint32 small_label_size_;// 滚轮缩小增加尺寸


};

#endif // QOENCVSCROLLAREA_H
