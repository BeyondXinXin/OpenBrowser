/*
 * Mode Browser
 * 1--自动提取连通域 2--直线剪裁 3--修剪  4--平滑 5--细分 6--细化
 * 11--细分 12--自相交 13--封闭
 * 21--载入文件 22--保存 23--撤销
 */



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
    void SlotModeBrowserAllBtnEnabledFalse();
    void SlotModeBrowserBtnEnabledTrue();

  Q_SIGNALS:
    void SignalsModeBrowserOut(const int &operation);// Handle 信号处理
    void SingalSliderBarMovtToIn(int);// 界面切换信号
    void SingalSliderBarMovtToOut(int);// 界面切换信号

  private slots:
    void SlotLeftShowChangeIn();

  private:
    void initFrom();
    void LeftFormShow(const int browser);

  private:
    Ui::FormLeft *ui;

};

#endif // FORMLEFT_H
