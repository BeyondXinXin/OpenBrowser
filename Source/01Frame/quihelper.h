#ifndef QUIHELPER_H
#define QUIHELPER_H

#include "stable.h"

//全局静态方法类
class QUIHelper : public QObject {
    Q_OBJECT
  public:
    // 获取全局路径
    static QString GetFullPath(const QString &path);
    // 新建路径（相对路径在程序目录，全局路径在全局目录）
    static bool DirMake(const QString &path);
    // 获取保存的文件
    static QString getSaveName(const QString &filter,
                               QString defaultDir =
                                   QCoreApplication::applicationDirPath());
    // 获取选择的文件
    static QString getFileName(const QString &filter,
                               QString defaultDir =
                                   QCoreApplication::applicationDirPath());
    // 获取选择的文件集合
    static QStringList getFileNames(const QString &filter,
                                    QString defaultDir =
                                        QCoreApplication::applicationDirPath());
    // 获取选择的目录
    static QString getFolderName();
    // 获取文件名,含拓展名
    static QString getFileNameWithExtension(const QString &strFilePath);
    // 获取选择文件夹中的文件
    static QStringList getFolderFileNames(const QStringList &filter);
    // 文件夹是否存在
    static bool folderIsExist(const QString &strFolder);
    // 文件是否存在
    static bool fileIsExist(const QString &strFile);
    // 复制文件
    static bool copyFile(const QString &sourceFile, const QString &targetFile);
    // 删除文件夹下所有文件
    static void deleteDirectory(const QString &path);

    //桌面宽度高度
    static int deskWidth();
    static int deskHeight();
    //程序本身文件名称
    static QString appName();
    //程序当前所在路径
    static QString appPath();
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

#endif // QUIHELPER_H
