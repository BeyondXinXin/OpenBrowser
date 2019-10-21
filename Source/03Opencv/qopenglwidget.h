#ifndef QOPENGLWIDGET_H
#define QOPENGLWIDGET_H

#include <QWidget>

namespace Ui {
class QOpenglWidget;
}

class QOpenglWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QOpenglWidget(QWidget *parent = nullptr);
    ~QOpenglWidget();

private:
    Ui::QOpenglWidget *ui;
};

#endif // QOPENGLWIDGET_H
