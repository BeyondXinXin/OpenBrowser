#ifndef QUIWIDGETMOVE_H
#define QUIWIDGETMOVE_H

//界面拖拽
#include "stable.h"

class QUIWidgetMove : public QObject {
    Q_OBJECT
  public:
    static QUIWidgetMove *Instance();
    explicit QUIWidgetMove(QObject *parent = nullptr);
    void start();

  protected:
    bool eventFilter(QObject *obj, QEvent *evt);

  private:
    static QUIWidgetMove *self;

  signals:

  public slots:
};

#endif // QUIWIDGETMOVE_H
