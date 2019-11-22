
#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

//01frame
#include "stable.h"

//02control
#include "frmtcpclient.h"
#include "settingsdialog.h"
#include "frmtcpserver.h"
#include "frmudpserver.h"


class FormTitle;

class QUIMenu : public QMenuBar {
    Q_OBJECT
  public:
    QUIMenu(QWidget *parent, FormTitle *p);
    ~QUIMenu();
    QToolBar *toolbar_;
  public slots :
    // 界面目录
    void File_open();		// 打开
    void File_save();		// 保存
    void File_open_database();		// 另存为
    void Help_info();		// 帮助
    void About_info();//关于
    void Act_edit_screenshot();//截图
    void qappclose();//退出
    void qappfullScreen();//全屏
    void qappmaxScreen();//退出全屏
    void qappNet();//打开网络
    void qappCom();//打开串口
  private:
    FormTitle *I_MainWindow;
    QStatusBar *T_StatusBa;
    QString currentPath;	// 当前图像路径
    frmTcpClient *I_frmTcpClient;
    frmTcpServer *I_frmTcpServer;
    frmUdpServer *I_frmUdpServer;
    QSerialPort *m_serialPort; //串口类
    SettingsDialog *com_Settings;
    void Initial();
    void Menu_File();		// 文件菜单
    void Menu_Edit();		// 编辑菜单
    void Menu_Help();		   // 帮助菜单
};


#endif // MYSCROLLAREA_H
