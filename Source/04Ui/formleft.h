#ifndef FORMLEFT_H
#define FORMLEFT_H

// 01frame includes
#include <app.h>

namespace Ui {
    class FormLeft;
}

class FormLeft : public QWidget {
    Q_OBJECT

  public:
    explicit FormLeft(QWidget *parent = nullptr);
    ~FormLeft();

  public slots:
    void SlotsSliderBarMovtToIn(int);
    void SlotPromptInformation(const QString &text);
    void SlotAllBtnEnabledFalse();
    void SlotAllBtnEnabledTrue();

  Q_SIGNALS:
    void SignalsMainOut(int, QString);// 算法处理信号
    void SignalsPolyDataHandle(const int &operation);// Handle 信号处理

  private slots:
    void SlotMenuBarSwitching();

  private:
    void initFrom();

  private:
    Ui::FormLeft *ui;

};

#endif // FORMLEFT_H
