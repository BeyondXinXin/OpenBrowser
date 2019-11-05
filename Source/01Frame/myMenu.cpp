//01frame
#include "myMenu.h"

//02control
#include "screenwidget.h"

//04ui
#include "formtitle.h"

myMenu::myMenu(QWidget *parent, FormTitle *p)
    : QMenuBar(parent) {
    I_MainWindow = static_cast<FormTitle *>(p) ;
    Initial();
}
myMenu::~myMenu() {
}
//文件菜单
void myMenu::Menu_File() {
    QAction *Act_file_new = new QAction(QIcon(":/Image/New.png"),
                                        tr("新建"), this);
    Act_file_new->setShortcut(Qt::Key_Control & Qt::Key_I);
    Act_file_new->setStatusTip(("新建"));
    QAction *Act_file_open = new QAction(QIcon(":/Image/Open.png"),
                                         tr("打开"), this);
    Act_file_open->setShortcuts(QKeySequence::Open);
    Act_file_open->setStatusTip(("打开"));
    connect(Act_file_open, SIGNAL(triggered()),
            I_MainWindow, SIGNAL(SigalOpenFileOut()));
    QAction *Act_file_save = new QAction(QIcon(":/Image/Save.png"),
                                         tr("保存"), this);
    Act_file_save->setShortcuts(QKeySequence::Save);
    Act_file_save->setStatusTip(("保存"));
    QAction *Act_file_saveas = new QAction(QIcon(":/Image/SaveAs.png"),
                                           tr("另存为"), this);
    Act_file_new->setShortcut(Qt::Key_Control & Qt::Key_D);
    Act_file_saveas->setStatusTip(("另存为"));
    connect(Act_file_saveas, SIGNAL(triggered()), this, SLOT(File_open_database()));
    QAction *Act_file_close = new QAction(QIcon(":/Image/Close.png"),
                                          tr("关闭"), this);
    Act_file_close->setShortcuts(QKeySequence::Close);
    Act_file_close->setStatusTip(("关闭软件"));
    QMenu *file = addMenu(("文件"));
    file->addAction(Act_file_new);
    file->addAction(Act_file_open);
    file->addAction(Act_file_save);
    file->addAction(Act_file_saveas);
    file->addSeparator();						//添加一个分割器
    file->addAction(Act_file_close);
    toolbar_->addAction(Act_file_open);
    toolbar_->addAction(Act_file_save);
}
//编辑菜单
void myMenu::Menu_Edit() {
    QAction *Act_edit_full = new QAction(QIcon(":/Image/Edit_Full.png"),
                                         tr("全屏显示"), this);
    Act_edit_full->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    Act_edit_full->setStatusTip(("全屏显示"));
    connect(Act_edit_full, SIGNAL(triggered()), this, SLOT(qappfullScreen()));
    QAction *Act_edit_back = new QAction(QIcon(":/Image/Edit_Max.png"),
                                         tr("退出全屏"), this);
    Act_edit_back->setShortcut(QKeySequence(Qt::Key_Escape));
    connect(Act_edit_back, SIGNAL(triggered()), this, SLOT(qappmaxScreen()));
    Act_edit_back->setStatusTip(("退出全屏"));
    QAction *Act_edit_screenshot = new QAction(QIcon(":/Image/btndo2.png"),
            tr("截图"), this);
    Act_edit_screenshot->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    connect(Act_edit_screenshot, SIGNAL(triggered()), this, SLOT(Act_edit_screenshot()));
    Act_edit_screenshot->setStatusTip(("截图"));
    QAction *Act_edit_net1 = new QAction(QIcon(""), tr("打开网络——tcp服务器"), this);
    connect(Act_edit_net1, SIGNAL(triggered()), this, SLOT(qappNet()));
    QAction *Act_edit_net2 = new QAction(QIcon(""), tr("打开网络——tcp客户端"), this);
    connect(Act_edit_net2, SIGNAL(triggered()), this, SLOT(qappNet()));
    QAction *Act_edit_net3 = new QAction(QIcon(""), tr("打开网络——udp客户端"), this);
    connect(Act_edit_net3, SIGNAL(triggered()), this, SLOT(qappNet()));
    Act_edit_net1->setObjectName("Act_edit_net1");
    Act_edit_net2->setObjectName("Act_edit_net2");
    Act_edit_net3->setObjectName("Act_edit_net3");
    Act_edit_net1->setStatusTip(("打开网络——tcp服务器"));
    Act_edit_net2->setStatusTip(("打开网络——tcp客户端"));
    Act_edit_net3->setStatusTip(("打开网络——udp客户端"));
    QAction *Act_edit_com = new QAction(QIcon(""), tr("打开端口"), this);
    Act_edit_com->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    connect(Act_edit_com, SIGNAL(triggered()), this, SLOT(qappCom()));
    Act_edit_com->setStatusTip(("打开端口"));
    QMenu *Act_edit_net = new QMenu(("打开网络"));
    Act_edit_net->addAction(Act_edit_net1);
    Act_edit_net->addAction(Act_edit_net2);
    Act_edit_net->addAction(Act_edit_net3);
    Act_edit_net->setStatusTip(("打开网络"));
    QMenu *edit = addMenu(("编辑"));
    edit->addAction(Act_edit_full);
    edit->addAction(Act_edit_back);
    edit->addAction(Act_edit_screenshot);
    edit->addSeparator();
    edit->addMenu(Act_edit_net);
    edit->addAction(Act_edit_com);
    toolbar_->addAction(Act_edit_screenshot);
    toolbar_->insertSeparator(Act_edit_screenshot);
}

//帮助菜单
void myMenu::Menu_Help() {
    QAction *Act_about_info =
        new QAction(QIcon(":/ImageProcessing/Image/Help_Info.png"),
                    tr("关于"), this);
    connect(Act_about_info, SIGNAL(triggered()), this, SLOT(About_info()));
    Act_about_info->setStatusTip(("关于"));
    QAction *Act_help_info =
        new QAction(QIcon(":/ImageProcessing/Image/Help_Info.png"),
                    tr("帮助"), this);
    connect(Act_help_info, SIGNAL(triggered()), this, SLOT(Help_info()));
    Act_help_info->setStatusTip(("帮助"));
    Act_help_info->setStatusTip(("帮助"));
    QMenu *help = addMenu(("帮助"));
    help->addAction(Act_about_info);
    help->addAction(Act_help_info);
}


// -------------------槽函数-------------------------------------------
void myMenu::Act_edit_screenshot() { //截屏
    ScreenWidget::Instance()->showFullScreen();
}
void myMenu::qappclose() { // 退出
    qApp->quit();
}
void myMenu::File_open() {	// 打开图片
    QString path = QFileDialog::getOpenFileName(this,
                   tr("选择图像"), ".",
                   tr("Images(*.jpg *.png *.bmp)"));
    if (path.size() == 0) {
        return;
    }
    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string name = code->fromUnicode(path).data();
    QUIHelper::showMessageBoxInfo(QString("打开图片路径:%1").arg(path));
    QUIHelper::showMessageBoxQuestion("图片和数据库无法匹配打开失败");
}
void myMenu::File_save() {		// 保存文件
}
void myMenu::File_open_database() {		// 打开配置文件
    QString path = QFileDialog::getOpenFileName(this,
                   tr("选择图像"), ".",
                   tr("Images(*.ini)"));
    if (path.size() == 0) {
        return;
    }
    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string name = code->fromUnicode(path).data();
    QUIHelper::showMessageBoxInfo(QString("打开图片路径:%1").arg(path));
    QUIHelper::showMessageBoxQuestion("图片和数据库无法匹配打开失败");
}
void myMenu::qappfullScreen() { //全屏
    I_MainWindow->showFullScreen();
}
void myMenu::qappmaxScreen() { //退出全屏
    I_MainWindow->showNormal();
}

void myMenu::qappNet() { //网络
    QString a = sender()->objectName();
    QString b = QUIHelper::getLocalIP();
    if (a == "Act_edit_net1") {
        I_frmTcpClient->setWindowTitle("打开网络——tcp服务器    本机ip:" + b);
        I_frmTcpClient->show();
    } else if (a == "Act_edit_net2") {
        I_frmTcpServer->setWindowTitle("打开网络——tcp客户端    本机ip:" + b);
        I_frmTcpServer->show();
    } else if (a == "Act_edit_net3") {
        I_frmUdpServer->setWindowTitle("打开网络——udp客户端    本机ip:" + b);
        I_frmUdpServer->show();
    }
}

void myMenu::qappCom() { //打开串口
    com_Settings->show();
}

void myMenu::Initial() {
    I_frmTcpClient = new frmTcpClient();
    I_frmTcpServer = new frmTcpServer();
    I_frmUdpServer = new frmUdpServer();
    com_Settings  = new SettingsDialog();
    toolbar_ = new QToolBar(("工具栏01")) ;
    toolbar_->setObjectName("toolbar");
    Qt::ToolBarArea area;
    area = Qt::LeftToolBarArea;//设置停靠位置
    toolbar_-> setMovable(true);
    toolbar_-> setFixedWidth(300);
    Menu_File();
    Menu_Edit();
    Menu_Help();
    this->setFixedWidth(200);
}


// -------------------帮助-------------------------------------------
void myMenu::Help_info() {
}
// -------------------关于-------------------------------------------
void myMenu::About_info() {
}

