/**
 * qt UIWidget 框架
 */

#ifndef APP_H
#define APP_H
#include "stable.h"

// 仅能启动一个实例
class Application : public QApplication {
    Q_OBJECT

  public:
    Application(int &argc, char **argv);
    ~Application();

    bool lock();

  private:
    QSharedMemory *_singular; // shared memory !! SINGLE ACCESS
};

//界面拖拽
class AppInit : public QObject {
    Q_OBJECT
  public:
    static AppInit *Instance();
    explicit AppInit(QObject *parent = nullptr);
    void start();

  protected:
    bool eventFilter(QObject *obj, QEvent *evt);

  private:
    static AppInit *self;

  signals:

  public slots:
};

//弹出信息框类
class QUIMessageBox : public QDialog {
    Q_OBJECT

  public:
    static QUIMessageBox *Instance();
    explicit QUIMessageBox(QWidget *parent = nullptr);
    ~QUIMessageBox();

  protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *obj, QEvent *evt);

  private:
    static QScopedPointer<QUIMessageBox> self;

    QVBoxLayout *verticalLayout1;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout3;
    QLabel *labIco;
    QLabel *labTitle;
    QLabel *labTime;
    QWidget *widgetMenu;
    QHBoxLayout *horizontalLayout4;
    QPushButton *btnMenu_Close;
    QWidget *widgetMain;
    QVBoxLayout *verticalLayout2;
    QFrame *frame;
    QVBoxLayout *verticalLayout4;
    QHBoxLayout *horizontalLayout1;
    QLabel *labIcoMain;
    QSpacerItem *horizontalSpacer1;
    QLabel *labInfo;
    QHBoxLayout *horizontalLayout2;
    QSpacerItem *horizontalSpacer2;
    QPushButton *btnOk;
    QPushButton *btnCancel;

  private:
    int closeSec;                   //总显示时间
    int currentSec;                 //当前已显示时间

  private slots:
    void initControl();             //初始化控件
    void initForm();                //初始化窗体
    void checkSec();                //校验倒计时

  private slots:
    void on_btnOk_clicked();
    void on_btnMenu_Close_clicked();

  public Q_SLOTS:
    void setIconMain(const QChar &str, quint32 size = 12);
    void setMessage(const QString &msg, int type, int closeSec = 0);
};

//图形字体处理类
class IconHelper : public QObject {
    Q_OBJECT

  public:
    static IconHelper *Instance();
    explicit IconHelper(QObject *parent = nullptr);

    //获取图形字体
    QFont getIconFont();

    //设置图形字体到标签
    void setIcon(QLabel *lab, const QChar &str, quint32 size = 12);

    //设置图形字体到按钮
    void setIcon(QAbstractButton *btn, const QChar &str, quint32 size = 12);

    //获取指定图形字体,可以指定文字大小,图片宽高,文字对齐
    QPixmap getPixmap(const QColor &color, const QChar &str, quint32 size = 12,
                      quint32 pixWidth = 15, quint32 pixHeight = 15,
                      int flags = Qt::AlignCenter);

    //根据按钮获取该按钮对应的图标
    QPixmap getPixmap(QToolButton *btn, bool normal);

  protected:
    bool eventFilter(QObject *watched, QEvent *event);

  private:
    static QScopedPointer<IconHelper> self;

    QFont iconFont;             //图形字体
    QList<QToolButton *> btns;  //按钮队列
    QList<QPixmap> pixNormal;   //正常图片队列
    QList<QPixmap> pixDark;     //加深图片队列
};

//托盘图标类
class TrayIcon : public QObject {
    Q_OBJECT
  public:
    static TrayIcon *Instance();
    explicit TrayIcon(QObject *parent = nullptr);

  private:
    static QScopedPointer<TrayIcon> self;

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

//全局静态方法类
class QUIHelper : public QObject {
    Q_OBJECT
  public:
    //桌面宽度高度
    static int deskWidth();
    static int deskHeight();

    //程序本身文件名称
    static QString appName();
    //程序当前所在路径
    static QString appPath();

    //新建目录
    static void newDir(const QString &dirName);

    //写入消息到额外的的消息日志文件
    static void writeInfo(const QString &info, const QString &filePath = "log");
    static void writeError(const QString &info, const QString &filePath = "log");

    //设置全局样式
    static void setStyle(const QString &qssFile);

    //九宫格图片 horzSplit-宫格1/3/7/9宽度  vertSplit-宫格1/3/7/9高度
    //dstWidth-目标图片宽度  dstHeight-目标图片高度
    static QPixmap ninePatch(const QString &picName,
                             int horzSplit, int vertSplit,
                             int dstWidth, int dstHeight);
    static QPixmap ninePatch(const QPixmap &pix,
                             int horzSplit, int vertSplit,
                             int dstWidth, int dstHeight);

    //设置窗体居中显示
    static void setFormInCenter(QWidget *frm);

    //设置翻译文件
    static void setTranslator(const QString &qmFile = ":/Image/qt_zh_CN.qm");

    //设置编码
    static void setCode();

    //设置延时
    static void sleep(int sec);

    //设置开机自启动
    static void runWithSystem(const QString &strName,
                              const QString &strPath, bool autoRun = true);

    //判断是否是IP地址
    static bool isIP(const QString &ip);

    //判断是否是MAC地址
    static bool isMac(const QString &mac);

    //判断是否是合法的电话号码
    static bool isTel(const QString &tel);

    //判断是否是合法的邮箱地址
    static bool isEmail(const QString &email);


    //16进制字符串转10进制
    static int strHexToDecimal(const QString &strHex);

    //10进制字符串转10进制
    static int strDecimalToDecimal(const QString &strDecimal);

    //2进制字符串转10进制
    static int strBinToDecimal(const QString &strBin);

    //10进制转16进制字符串,补零.
    static QString decimalToStrHex(int decimal);

    //字节数组转ushort
    static int byteToUShort(const QByteArray &data);
    static int byteToUShortRec(const QByteArray &data);

    //异或加密算法
    static QString getXorEncryptDecrypt(const QString &str, char key);

    //异或校验
    static uchar getOrCode(const QByteArray &data);

    //计算校验码
    static uchar getCheckCode(const QByteArray &data);

    //字符串补全
    static QString getValue(quint8 value);

    //字节数组转Ascii字符串
    static QString byteArrayToAsciiStr(const QByteArray &data);

    //16进制字符串转字节数组
    static QByteArray hexStrToByteArray(const QString &str);
    static char convertHexChar(char ch);

    //Ascii字符串转字节数组
    static QByteArray asciiStrToByteArray(const QString &str);

    //字节数组转16进制字符串
    static QString byteArrayToHexStr(const QByteArray &data);

    //获取保存的文件
    static QString getSaveName(const QString &filter,
                               QString defaultDir =
                                   QCoreApplication::applicationDirPath());

    //获取选择的文件
    static QString getFileName(const QString &filter,
                               QString defaultDir =
                                   QCoreApplication::applicationDirPath());

    //获取选择的文件集合
    static QStringList getFileNames(const QString &filter,
                                    QString defaultDir =
                                        QCoreApplication::applicationDirPath());

    //获取选择的目录
    static QString getFolderName();

    //获取文件名,含拓展名
    static QString getFileNameWithExtension(const QString &strFilePath);

    //获取选择文件夹中的文件
    static QStringList getFolderFileNames(const QStringList &filter);

    //文件夹是否存在
    static bool folderIsExist(const QString &strFolder);

    //文件是否存在
    static bool fileIsExist(const QString &strFile);

    //复制文件
    static bool copyFile(const QString &sourceFile, const QString &targetFile);

    //删除文件夹下所有文件
    static void deleteDirectory(const QString &path);

    //判断IP地址及端口是否在线
    static bool ipLive(const QString &ip, int port, int timeout = 1000);

    //获取网页所有源代码
    static QString getHtml(const QString &url);

    //获取本机公网IP地址
    static QString getNetIP(const QString &webCode);

    //获取本机IP
    static QString getLocalIP();

    //Url地址转为IP地址
    static QString urlToIP(const QString &url);

    //判断是否通外网
    static bool isWebOk();

    //弹出消息框
    static void showMessageBoxInfo(const QString &info,
                                   int closeSec = 0, bool exec = false);
    //弹出错误框
    static void showMessageBoxError(const QString &info,
                                    int closeSec = 0, bool exec = false);
    //弹出询问框
    static int showMessageBoxQuestion(const QString &info);
};

//全局变量控制
class QUIConfig {
  public:
    //全局图标
};

#endif // APP_H
