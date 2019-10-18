#ifndef FRM1_H
#define FRM1_H

//01frame
#include "app.h"

namespace Ui {
    class FormMaskWidget;
}

class FormMaskWidget : public QWidget {
    Q_OBJECT
  public:
    explicit FormMaskWidget(QWidget *parent = nullptr);
    ~FormMaskWidget();

  public Q_SLOTS:
    void SlotsStackedWidgetNum(const int &num);
    void SlotThisCloseIn();
    void SlotThreadAICurrent(const QString, const qint32);
    void SetCancleHide();
  Q_SIGNALS:
    void SingnalCancel(int, QString);
  Q_SIGNALS:
    void SingnalCancelOut();
    void SingnalEndOut();

  public slots:
    void Slotsignout();
  private:
    Ui::FormMaskWidget *ui;
};

#endif // FRM1_H
