#ifndef FORMIMAGEHANDLE_H
#define FORMIMAGEHANDLE_H

// 01frame includes
#include <app.h>

namespace Ui {
    class FormImageHandle;
}

class FormImageHandle : public QWidget {
    Q_OBJECT

  public:
    explicit FormImageHandle(QWidget *parent = nullptr);
    ~FormImageHandle();
    void ShowImageHandel(const int num);

  Q_SIGNALS:
    void SingalImageMenuOut(const int &operation);// 界面切换信号
    void SignalPromptInformationOut(const QString &text);
  private:
    void WinGeom();								// 几何变换窗口
    void WinGray();								// 灰度变换窗口
    void WinEnhance();							// 图像增强窗口
    void WinMorp();								// 形态学处理窗口
    void WinColor();							// 颜色模型窗口
    void WinTest();							    // 测试窗口
  private:
    Ui::FormImageHandle *ui;

    QWidget *dock_Geom;
    QWidget *dock_Gray;
    QWidget *dock_Enhance;
    QWidget *dock_Morp;
    QWidget *dock_Color;
    QWidget *dock_Test;
};

#endif // FORMIMAGEHANDLE_H
