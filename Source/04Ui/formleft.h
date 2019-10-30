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
    void SlotPromptInformation(const QString &text);
    void SlotAllBtnEnabledFalse();
    void SlotAllBtnEnabledTrue();

  Q_SIGNALS:
    void SignalsPolyDataHandle(const int &operation);// Handle 信号处理
    void SingalSliderBarMovtToIn(int);// 界面切换信号
    void SingalSliderBarMovtToOut(int);// 界面切换信号

  private slots:
    void SlotMenuBarSwitching();

  private:
    void initFrom();

  private:
    Ui::FormLeft *ui;

};

#endif // FORMLEFT_H
