#ifndef QOENCVWIDGET_H
#define QOENCVWIDGET_H

#include <QWidget>
#include "qoencvscrollarea.h"
#include "qt_opencv.h"

namespace Ui {
    class QOencvWidget;
}

class QOpencvWidget : public QWidget {
    Q_OBJECT

  public:
    explicit QOpencvWidget(QWidget *parent = nullptr);
    ~QOpencvWidget();

  Q_SIGNALS:
    void unChecket();
  private:
    void Initialization();
  private Q_SLOTS:
    void SlotImgBigIn();
    void SlotImgSmallIn();
    void SlotImgPointIn(const QPoint, const QString);
    void SlotLeaveIn();
  private:
    Ui::QOencvWidget *ui;
    QOpencvScrollArea *scrollarea_;
    QOpencvLbel *label_;
    double img_zoomsize_;
    QImage img_;


};

#endif // QOENCVWIDGET_H
