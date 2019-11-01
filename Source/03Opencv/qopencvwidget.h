/**
 * qt opencv widget
 * 试过各种图片浏览方式,感觉还是用现成的scene好一些,很多借口qt已经封装好了
 *
 */


#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <app.h>

namespace Ui {
    class QOpencvWidget;
}

class QOpencvPixmapItem : public QGraphicsPixmapItem {
  public:
    explicit QOpencvPixmapItem(QGraphicsPixmapItem *parent = nullptr);
    ~QOpencvPixmapItem();
//  protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


class QOpencvScene : public QGraphicsScene {
    Q_OBJECT
  public:
    explicit QOpencvScene(QGraphicsScene *parent = nullptr);
    ~QOpencvScene();
//  protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//    void leaveEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);
};

class QOpencvView : public QGraphicsView {
  public:
    explicit QOpencvView(QWidget *parent = nullptr);
    ~QOpencvView();
  protected:
    void wheelEvent(QWheelEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
};

class QOpencvWidget : public QWidget {
    Q_OBJECT

  public:
    explicit QOpencvWidget(QWidget *parent = nullptr);
    ~QOpencvWidget();
  private:
    void Initial();
  private:
    Ui::QOpencvWidget *ui;
    QOpencvPixmapItem  *opencv_pixmap_;
    QOpencvScene *opencv_scene_;
};

#endif // QOPENCVWIDGET_H
