#ifndef QUITRAYICON_H
#define QUITRAYICON_H

#include "stable.h"

//托盘图标类
class QUITrayIcon : public QObject {
    Q_OBJECT
  public:
    static QUITrayIcon *Instance();
    explicit QUITrayIcon(QObject *parent = nullptr);

  private:
    static QScopedPointer<QUITrayIcon> self;

    QWidget *mainWidget;            //对应所属主窗体
    QSystemTrayIcon *trayIcon;      //托盘对象
    QMenu *menu;                    //右键菜单
    bool exitDirect;                //是否直接退出

  private slots:
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);

  public Q_SLOTS:
    //设置是否直接退出,如果不是直接退出则发送信号给主界面
    void setExitDirect(bool exitDirect);

    //设置所属主窗体
    void setMainWidget(QWidget *mainWidget);

    //显示消息
    void showMessage(const QString &title, const QString &msg,
                     QSystemTrayIcon::MessageIcon
                     icon = QSystemTrayIcon::Information, int msecs = 5000);
    //设置图标
    void setIcon(const QString &strIcon);
    //设置提示信息
    void setToolTip(const QString &tip);
    //设置是否可见
    void setVisible(bool visible);
    //退出所有
    void closeAll() __attribute__((noreturn));

  Q_SIGNALS:
    void trayIconExit();
};

#endif // QUITRAYICON_H
