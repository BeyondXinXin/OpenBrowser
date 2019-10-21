#ifndef QOENCVSCROLLAREA_H
#define QOENCVSCROLLAREA_H

// 01frame includes
#include "app.h"

class QOencvScrollArea: public QScrollArea {
    Q_OBJECT

    Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
    qma


  public:
    explicit QOencvScrollArea(QWidget *parent = nullptr);
    ~QOencvScrollArea();
    QLabel   *label;
    bool canMove;//是否可以移动
    void set_image(QString filename);
    QImage get_image();
    bool mMoveStart;//是否移动开始
    bool mContinuousMove;


    int big_label_size;
    int small_label_size;
    int min_label_width;
    int min_label_heigh;

  protected:

    bool eventFilter(QObject *obj, QEvent *evt);
    QPoint mMousePoint;
    QImage *myScrollArea_img;//内部图片






};

#endif // QOENCVSCROLLAREA_H
