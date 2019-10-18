/**
 * 遮挡罩控件
 */

#ifndef MASKWIDGET_H
#define MASKWIDGET_H

//01frame
#include "app.h"

class MaskWidget : public QWidget {
    Q_OBJECT
  public:
    explicit MaskWidget(QWidget *parent = nullptr);

    static MaskWidget *Instance() {
        static QMutex mutex;
        if (!self) {
            QMutexLocker locker(&mutex);
            if (!self) {
                self = new MaskWidget;
            }
        }
        return self;
    }

  protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

  private:
    static MaskWidget *self;
    QWidget *mainWidget;
    QStringList dialogNames;

  public slots:
    void setMainWidget(QWidget *mainWidget);
    void setDialogNames(const QStringList &dialogNames);
    void setBgColor(const QColor &bgColor);
    void setOpacity(double opacity);
};

#endif // MASKWIDGET_H
