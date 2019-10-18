﻿#ifndef FORMTITLE_H
#define FORMTITLE_H

// 01frame includes
#include "app.h"
#include "myMenu.h"



namespace Ui {
    class FormTitle;
}
class myMenu;

class FormTitle : public QDialog {
    Q_OBJECT

  public:
    explicit FormTitle(QWidget *parent = nullptr);
    ~FormTitle();
  public slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
    void SlotFullScreen();//全屏
    void SlotNormalScreen();//退出全屏
  Q_SIGNALS:
    void SigalOpenFileOut();
  protected:
    bool eventFilter(QObject *obj, QEvent *evt);
  private :
    void Initial();
  private:
    Ui::FormTitle *ui;
    bool full_screen_;// 是否全屏标识符
    myMenu *my_menu_;
};

#endif // FORMTITLE_H
