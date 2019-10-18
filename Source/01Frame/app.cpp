#include "app.h"


// 02control includes
#include "maskwidget.h"
#include "formtitle.h"


// 仅能启动一个实例
Application::Application(int &argc, char **argv):
    QApplication(argc, argv, true) {
    _singular = new QSharedMemory("SharedMemory", this);
    this->setWindowIcon(QIcon(":/Image/logo.ico"));
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(15);
    qApp->setFont(font);
    QUIHelper::setCode();
    AppInit::Instance()->start();//支持界面拖拽
    TrayIcon::Instance()->setIcon(":/Image/logo.ico");
    TrayIcon::Instance()->setVisible(true);
    MaskWidget::Instance()->setDialogNames(QStringList("MaskWidget"));
}

Application::~Application() {
    if (_singular->isAttached()) {
        _singular->detach();
    }
}

bool Application::lock() {
    if (_singular->attach(QSharedMemory::ReadOnly)) {
        _singular->detach();
        return false;
    }
    if (_singular->create(1)) {
        return true;
    }
    return false;
}

/*-----------------------------------
 * 界面支持拖拽
 * -----------------------------------*/
AppInit *AppInit::self = nullptr;
AppInit *AppInit::Instance() {
    if (!self) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self) {
            self = new AppInit;
        }
    }
    return self;
}

AppInit::AppInit(QObject *parent) : QObject(parent) {
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt) {
    QWidget *w = static_cast<QWidget *>(obj);
    if (!w->property("my_canMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }
    if (!w->property("my_canMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }
    static QPoint mousePoint;
    static bool mousePressed = false;
    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() & Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }
    return QObject::eventFilter(obj, evt);
}

void AppInit::start() {
    qApp->installEventFilter(this);
}

QScopedPointer<QUIMessageBox> QUIMessageBox::self;
QUIMessageBox *QUIMessageBox::Instance() {
    if (self.isNull()) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new QUIMessageBox);
        }
    }
    return self.data();
}

QUIMessageBox::QUIMessageBox(QWidget *parent) : QDialog(parent) {
    this->initControl();
    this->initForm();
    QUIHelper::setFormInCenter(this);
}

QUIMessageBox::~QUIMessageBox() {
    delete widgetMain;
}

void QUIMessageBox::initControl() {
    this->setObjectName(QString::fromUtf8("QUIMessageBox"));
    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
    widgetTitle->setSizePolicy(sizePolicy);
    widgetTitle->setMinimumSize(QSize(0, TitleMinSize));
    horizontalLayout3 = new QHBoxLayout(widgetTitle);
    horizontalLayout3->setSpacing(0);
    horizontalLayout3->setObjectName(QString::fromUtf8("horizontalLayout3"));
    horizontalLayout3->setContentsMargins(0, 0, 0, 0);
    labIco = new QLabel(widgetTitle);
    labIco->setObjectName(QString::fromUtf8("labIco"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labIco->sizePolicy().hasHeightForWidth());
    labIco->setSizePolicy(sizePolicy1);
    labIco->setMinimumSize(QSize(TitleMinSize, 0));
    labIco->setAlignment(Qt::AlignCenter);
    horizontalLayout3->addWidget(labIco);
    labTitle = new QLabel(widgetTitle);
    labTitle->setObjectName(QString::fromUtf8("labTitle"));
    labTitle->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    horizontalLayout3->addWidget(labTitle);
    labTime = new QLabel(widgetTitle);
    labTime->setObjectName(QString::fromUtf8("labTime"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTime->sizePolicy().hasHeightForWidth());
    labTime->setSizePolicy(sizePolicy2);
    labTime->setAlignment(Qt::AlignCenter);
    horizontalLayout3->addWidget(labTime);
    widgetMenu = new QWidget(widgetTitle);
    widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
    sizePolicy1.setHeightForWidth(widgetMenu->sizePolicy().hasHeightForWidth());
    widgetMenu->setSizePolicy(sizePolicy1);
    horizontalLayout4 = new QHBoxLayout(widgetMenu);
    horizontalLayout4->setSpacing(0);
    horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
    horizontalLayout4->setContentsMargins(0, 0, 0, 0);
    btnMenu_Close = new QPushButton(widgetMenu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(TitleMinSize, 0));
    btnMenu_Close->setMaximumSize(QSize(TitleMinSize, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);
    btnMenu_Close->setFlat(true);
    horizontalLayout4->addWidget(btnMenu_Close);
    horizontalLayout3->addWidget(widgetMenu);
    verticalLayout1->addWidget(widgetTitle);
    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMainQUI"));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(5);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(5, 5, 5, 5);
    frame = new QFrame(widgetMain);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    verticalLayout4 = new QVBoxLayout(frame);
    verticalLayout4->setObjectName(QString::fromUtf8("verticalLayout4"));
    verticalLayout4->setContentsMargins(-1, 9, -1, -1);
    horizontalLayout1 = new QHBoxLayout();
    horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
    labIcoMain = new QLabel(frame);
    labIcoMain->setObjectName(QString::fromUtf8("labIcoMain"));
    labIcoMain->setAlignment(Qt::AlignCenter);
    horizontalLayout1->addWidget(labIcoMain);
    horizontalSpacer1 = new QSpacerItem(5, 0,
                                        QSizePolicy::Minimum, QSizePolicy::Minimum);
    horizontalLayout1->addItem(horizontalSpacer1);
    labInfo = new QLabel(frame);
    labInfo->setObjectName(QString::fromUtf8("labInfo"));
    QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
    labInfo->setSizePolicy(sizePolicy4);
    labInfo->setMinimumSize(QSize(0, TitleMinSize));
    labInfo->setScaledContents(false);
    labInfo->setWordWrap(true);
    horizontalLayout1->addWidget(labInfo);
    verticalLayout4->addLayout(horizontalLayout1);
    horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
    horizontalSpacer2 = new QSpacerItem(
        40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout2->addItem(horizontalSpacer2);
    btnOk = new QPushButton(frame);
    btnOk->setObjectName(QString::fromUtf8("btnOk"));
    btnOk->setMinimumSize(QSize(85, 0));
    btnOk->setFocusPolicy(Qt::StrongFocus);
    btnOk->setIcon(QIcon(":/Image/btn_ok.png"));
    horizontalLayout2->addWidget(btnOk);
    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setMinimumSize(QSize(85, 0));
    btnCancel->setFocusPolicy(Qt::StrongFocus);
    btnCancel->setIcon(QIcon(":/Image/btn_close.png"));
    horizontalLayout2->addWidget(btnCancel);
    verticalLayout4->addLayout(horizontalLayout2);
    verticalLayout2->addWidget(frame);
    verticalLayout1->addWidget(widgetMain);
    widgetTitle->raise();
    widgetMain->raise();
    frame->raise();
    btnOk->setText("确定");
    btnCancel->setText("取消");
    connect(btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(btnMenu_Close, SIGNAL(clicked()),
            this, SLOT(on_btnMenu_Close_clicked()));
    connect(btnCancel, SIGNAL(clicked()),
            this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIMessageBox::initForm() {
    IconHelper::Instance()->setIcon(
        labIco, QChar(0xf072), 14);
    IconHelper::Instance()->setIcon(
        btnMenu_Close, QChar(0xf00d), 12);
    this->setProperty("form", true);
    this->widgetTitle->setProperty("form", "title");
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setWindowTitle(this->labTitle->text());
    int width = 80;
    int iconWidth = 18;
    int iconHeight = 18;
    this->setFixedSize(280, 150);
    labIcoMain->setFixedSize(30, 30);
    QList<QPushButton *> btns = this->frame->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setMinimumWidth(width);
        btn->setIconSize(QSize(iconWidth, iconHeight));
    }
    closeSec = 0;
    currentSec = 0;
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    timer->start();
    this->installEventFilter(this);
}

void QUIMessageBox::checkSec() {
    if (closeSec == 0) {
        return;
    }
    if (currentSec < closeSec) {
        currentSec++;
    } else {
        this->close();
    }
    QString str = QString("关闭倒计时 %1 s").arg(closeSec - currentSec + 1);
    this->labTime->setText(str);
}

void QUIMessageBox::setMessage(const QString &msg, int type, int closeSec) {
    this->setMinimumWidth(0);
    this->closeSec = closeSec;
    this->currentSec = 0;
    this->labTime->clear();
    checkSec();
    //图片存在则取图片,不存在则取图形字体
    int size = this->labIcoMain->size().height();
    bool exist = !QImage(":/Image/msg_info.png").isNull();
    if (type == 0) {
        if (exist) {
            this->labIcoMain->
            setStyleSheet("border-image: url(:/Image/msg_info.png);");
        } else {
            IconHelper::Instance()->setIcon(
                this->labIcoMain, 0xf05a, static_cast<quint32>(size));
        }
        this->btnCancel->setVisible(false);
        this->labTitle->setText("提示");
    } else if (type == 1) {
        if (exist) {
            this->labIcoMain->
            setStyleSheet("border-image: url(:/Image/msg_question.png);");
        } else {
            IconHelper::Instance()->setIcon(
                this->labIcoMain, 0xf059, static_cast<quint32>(size));
        }
        this->setMinimumWidth(1200);
        this->labTitle->setText("询问");
    } else if (type == 2) {
        if (exist) {
            this->labIcoMain->
            setStyleSheet("border-image: url(:/Image/msg_error.png);");
        } else {
            IconHelper::Instance()->setIcon(
                this->labIcoMain, 0xf057, static_cast<quint32>(size));
        }
        this->btnCancel->setVisible(false);
        this->labTitle->setText("错误");
    }
    this->labInfo->setText(msg);
    this->setWindowTitle(this->labTitle->text());
}

void QUIMessageBox::closeEvent(QCloseEvent *) {
    closeSec = 0;
    currentSec = 0;
}

bool QUIMessageBox::eventFilter(QObject *obj, QEvent *evt) {
    static QPoint mousePoint;
    static bool mousePressed = false;
    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }
    return QWidget::eventFilter(obj, evt);
}

void QUIMessageBox::on_btnOk_clicked() {
    done(QMessageBox::Yes);
    close();
}

void QUIMessageBox::on_btnMenu_Close_clicked() {
    done(QMessageBox::No);
    close();
}

void QUIMessageBox::setIconMain(const QChar &str, quint32 size) {
    IconHelper::Instance()->setIcon(this->labIco, str, size);
}

QScopedPointer<IconHelper> IconHelper::self;
IconHelper *IconHelper::Instance() {
    if (self.isNull()) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new IconHelper);
        }
    }
    return self.data();
}

IconHelper::IconHelper(QObject *parent) : QObject(parent) {
    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome")) {
        int fontId = fontDb.addApplicationFont(":/Image/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "load fontawesome-webfont.ttf error";
        }
    }
    if (fontDb.families().contains("FontAwesome")) {
        iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }
}

QFont IconHelper::getIconFont() {
    return this->iconFont;
}

void IconHelper::setIcon(QLabel *lab, const QChar &str, quint32 size) {
    iconFont.setPixelSize(static_cast<int>(size));
    lab->setFont(iconFont);
    lab->setText(str);
}

void IconHelper::setIcon(QAbstractButton *btn, const QChar &str, quint32 size) {
    iconFont.setPixelSize(static_cast<int>(size));
    btn->setFont(iconFont);
    btn->setText(str);
}

QPixmap IconHelper::getPixmap(const QColor &color, const QChar &str, quint32 size,
                              quint32 pixWidth, quint32 pixHeight, int flags) {
    QPixmap pix(static_cast<int>(pixWidth), static_cast<int>(pixHeight));
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(color);
    iconFont.setPixelSize(static_cast<int>(size));
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), flags, str);
    painter.end();
    return pix;
}

QPixmap IconHelper::getPixmap(QToolButton *btn, bool normal) {
    QPixmap pix;
    int index = btns.indexOf(btn);
    if (index >= 0) {
        if (normal) {
            pix = pixNormal.at(index);
        } else {
            pix = pixDark.at(index);
        }
    }
    return pix;
}

bool IconHelper::eventFilter(QObject *watched, QEvent *event) {
    if (watched->inherits("QToolButton")) {
        QToolButton *btn = static_cast<QToolButton *>(watched);
        int index = btns.indexOf(btn);
        if (index >= 0) {
            if (event->type() == QEvent::Enter) {
                btn->setIcon(QIcon(pixDark.at(index)));
            } else if (event->type() == QEvent::Leave) {
                if (btn->isChecked()) {
                    btn->setIcon(QIcon(pixDark.at(index)));
                } else {
                    btn->setIcon(QIcon(pixNormal.at(index)));
                }
            }
        }
    }
    return QObject::eventFilter(watched, event);
}


QScopedPointer<TrayIcon> TrayIcon::self;
TrayIcon *TrayIcon::Instance() {
    if (self.isNull()) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new TrayIcon);
        }
    }
    return self.data();
}

TrayIcon::TrayIcon(QObject *parent) : QObject(parent) {
    mainWidget = nullptr;
    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    menu = new QMenu(QApplication::desktop());
    exitDirect = true;
}

void TrayIcon::iconIsActived(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick: {
                mainWidget->showNormal();
                break;
            }
        default:
            break;
    }
}

void TrayIcon::setExitDirect(bool exitDirect) {
    if (this->exitDirect != exitDirect) {
        this->exitDirect = exitDirect;
    }
}

void TrayIcon::setMainWidget(QWidget *mainWidget) {
    this->mainWidget = mainWidget;
    menu->addAction("主界面", mainWidget, SLOT(on_btnMenu_Min_clicked()));
    if (exitDirect) {
        menu->addAction("退出", this, SLOT(closeAll()));
    } else {
        menu->addAction("退出", this, SIGNAL(trayIconExit()));
    }
    trayIcon->setContextMenu(menu);
}

void TrayIcon::showMessage(
    const QString &title, const QString &msg,
    QSystemTrayIcon::MessageIcon icon, int msecs) {
    trayIcon->showMessage(title, msg, icon, msecs);
}

void TrayIcon::setIcon(const QString &strIcon) {
    trayIcon->setIcon(QIcon(strIcon));
}

void TrayIcon::setToolTip(const QString &tip) {
    trayIcon->setToolTip(tip);
}

void TrayIcon::setVisible(bool visible) {
    trayIcon->setVisible(visible);
}

void TrayIcon::closeAll() {
    trayIcon->hide();
    trayIcon->deleteLater();
    exit(0);
}

int QUIHelper::deskWidth() {
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static int width = 0;
    if (width == 0) {
        width = qApp->desktop()->availableGeometry().width();
    }
    return width;
}

int QUIHelper::deskHeight() {
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static int height = 0;
    if (height == 0) {
        height = qApp->desktop()->availableGeometry().height();
    }
    return height;
}

QString QUIHelper::appName() {
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static QString name;
    if (name.isEmpty()) {
        name = qApp->applicationFilePath();
        QStringList list = name.split("/");
        name = list.at(list.count() - 1).split(".").at(0);
    }
    return name;
}

QString QUIHelper::appPath() {
    return qApp->applicationDirPath();
}

void QUIHelper::newDir(const QString &dirName) {
    QString strDir = dirName;
    //如果路径中包含斜杠字符则说明是绝对路径
    //linux系统路径字符带有 /  windows系统 路径字符带有 :/
    if (!strDir.startsWith("/") && !strDir.contains(":/")) {
        strDir = QString("%1/%2").arg(QUIHelper::appPath()).arg(strDir);
    }
    QDir dir(strDir);
    if (!dir.exists()) {
        dir.mkpath(strDir);
    }
}

void QUIHelper::writeInfo(const QString &info, const QString &filePath) {
    QString fileName = QString("%1/%2/%3_runinfo_%4.txt")
                       .arg(QUIHelper::appPath())
                       .arg(filePath)
                       .arg(QUIHelper::appName())
                       .arg(QDate::currentDate().toString("yyyyMM"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream stream(&file);
    stream << DATETIME << "  " << info << NEWLINE;
    file.close();
}

void QUIHelper::writeError(const QString &info, const QString &filePath) {
    //正式运行屏蔽掉输出错误信息,调试阶段才需要
    QString fileName = QString("%1/%2/%3_runerror_%4.txt")
                       .arg(QUIHelper::appPath())
                       .arg(filePath)
                       .arg(QUIHelper::appName())
                       .arg(QDate::currentDate().toString("yyyyMM"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream stream(&file);
    stream << DATETIME << "  " << info << NEWLINE;
    file.close();
}

void QUIHelper::setStyle(const QString &qssFile) {
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setPalette(
            QPalette(QColor((qss.indexOf("paletteColor:") >= 0) ?
                            qss.mid(qss.indexOf("paletteColor:") +
                                    QString("paletteColor:").length(), 7) :
                            "#2E2F30")));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

QPixmap QUIHelper::ninePatch(const QString &picName,
                             int horzSplit, int vertSplit,
                             int dstWidth, int dstHeight) {
    QPixmap pix(picName);
    return ninePatch(pix, horzSplit, vertSplit, dstWidth, dstHeight);
}

QPixmap QUIHelper::ninePatch(const QPixmap &pix, int horzSplit,
                             int vertSplit, int dstWidth, int dstHeight) {
    int pixWidth = pix.width();
    int pixHeight = pix.height();
    QPixmap pix1 = pix.copy(0, 0, horzSplit, vertSplit);
    QPixmap pix2 = pix.copy(horzSplit, 0, pixWidth - horzSplit * 2, vertSplit);
    QPixmap pix3 = pix.copy(pixWidth - horzSplit, 0, horzSplit, vertSplit);
    QPixmap pix4 = pix.copy(0, vertSplit, horzSplit, pixHeight - vertSplit * 2);
    QPixmap pix5 = pix.copy(horzSplit, vertSplit, pixWidth - horzSplit * 2,
                            pixHeight - vertSplit * 2);
    QPixmap pix6 = pix.copy(pixWidth - horzSplit, vertSplit, horzSplit,
                            pixHeight - vertSplit * 2);
    QPixmap pix7 = pix.copy(0, pixHeight - vertSplit, horzSplit, vertSplit);
    QPixmap pix8 = pix.copy(horzSplit, pixHeight - vertSplit,
                            pixWidth - horzSplit * 2, pixWidth - horzSplit * 2);
    QPixmap pix9 = pix.copy(pixWidth - horzSplit,
                            pixHeight - vertSplit, horzSplit, vertSplit);
    //保持高度拉宽
    pix2 = pix2.scaled(dstWidth - horzSplit * 2, vertSplit,
                       Qt::IgnoreAspectRatio);
    //保持宽度拉高
    pix4 = pix4.scaled(horzSplit, dstHeight - vertSplit * 2,
                       Qt::IgnoreAspectRatio);
    //宽高都缩放
    pix5 = pix5.scaled(dstWidth - horzSplit * 2, dstHeight - vertSplit * 2,
                       Qt::IgnoreAspectRatio);
    //保持宽度拉高
    pix6 = pix6.scaled(horzSplit, dstHeight - vertSplit * 2,
                       Qt::IgnoreAspectRatio);
    //保持高度拉宽
    pix8 = pix8.scaled(dstWidth - horzSplit * 2, vertSplit);
    //生成宽高图片并填充透明背景颜色
    QPixmap resultImg(dstWidth, dstHeight);
    resultImg.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&resultImg);
    if (!resultImg.isNull()) {
        painter.drawPixmap(0, 0, pix1);
        painter.drawPixmap(horzSplit, 0, pix2);
        painter.drawPixmap(dstWidth - horzSplit, 0, pix3);
        painter.drawPixmap(0, vertSplit, pix4);
        painter.drawPixmap(horzSplit, vertSplit, pix5);
        painter.drawPixmap(dstWidth - horzSplit, vertSplit, pix6);
        painter.drawPixmap(0, dstHeight - vertSplit, pix7);
        painter.drawPixmap(horzSplit, dstHeight - vertSplit, pix8);
        painter.drawPixmap(dstWidth - horzSplit, dstHeight - vertSplit, pix9);
    }
    painter.end();
    return resultImg;
}

void QUIHelper::setFormInCenter(QWidget *frm) {
    int frmX = frm->width();
    int frmY = frm->height();
    QDesktopWidget w;
    int deskWidth = w.availableGeometry().width();
    int deskHeight = w.availableGeometry().height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    frm->move(movePoint);
}

void QUIHelper::setTranslator(const QString &qmFile) {
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

void QUIHelper::setCode() {
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
}

void QUIHelper::sleep(int sec) {
    QTime dieTime = QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void QUIHelper::runWithSystem(
    const QString &strName, const QString &strPath, bool autoRun) {
    QSettings
    reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
        , QSettings::NativeFormat);
    reg.setValue(strName, autoRun ? strPath : "");
}

bool QUIHelper::isIP(const QString &ip) {
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.)"
                   "{3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(ip);
}

bool QUIHelper::isMac(const QString &mac) {
    QRegExp RegExp("^[A-F0-9]{2}(-[A-F0-9]{2}){5}$");
    return RegExp.exactMatch(mac);
}

bool QUIHelper::isTel(const QString &tel) {
    if (tel.length() != 11) {
        return false;
    }
    if (!tel.startsWith("13") && !tel.startsWith("14")
            && !tel.startsWith("15") && !tel.startsWith("18")) {
        return false;
    }
    return true;
}

bool QUIHelper::isEmail(const QString &email) {
    if (!email.contains("@") || !email.contains(".com")) {
        return false;
    }
    return true;
}

int QUIHelper::strHexToDecimal(const QString &strHex) {
    bool ok;
    return strHex.toInt(&ok, 16);
}

int QUIHelper::strDecimalToDecimal(const QString &strDecimal) {
    bool ok;
    return strDecimal.toInt(&ok, 10);
}

int QUIHelper::strBinToDecimal(const QString &strBin) {
    bool ok;
    return strBin.toInt(&ok, 2);
}

QString QUIHelper::decimalToStrHex(int decimal) {
    QString temp = QString::number(decimal, 16);
    if (temp.length() == 1) {
        temp = "0" + temp;
    }
    return temp;
}

int QUIHelper::byteToUShort(const QByteArray &data) {
    int i = data.at(1) & 0x000000FF;
    i |= ((data.at(0) << 8) & 0x0000FF00);
    if (i >= 32768) {
        i = i - 65536;
    }
    return i;
}

int QUIHelper::byteToUShortRec(const QByteArray &data) {
    int i = data.at(0) & 0x000000FF;
    i |= ((data.at(1) << 8) & 0x0000FF00);
    if (i >= 32768) {
        i = i - 65536;
    }
    return i;
}

QString QUIHelper::getXorEncryptDecrypt(const QString &str, char key) {
    QByteArray data = str.toLatin1();
    int size = data.size();
    for (int i = 0; i < size; i++) {
        data[i] = data[i] ^ key;
    }
    return QLatin1String(data);
}

uchar QUIHelper::getOrCode(const QByteArray &data) {
    int len = data.length();
    uchar result = 0;
    for (int i = 0; i < len; i++) {
        result ^= data.at(i);
    }
    return result;
}

uchar QUIHelper::getCheckCode(const QByteArray &data) {
    int len = data.length();
    uchar temp = 0;
    for (uchar i = 0; i < len; i++) {
        temp += data.at(i);
    }
    return temp % 256;
}

QString QUIHelper::getValue(quint8 value) {
    QString result = QString::number(value);
    if (result.length() <= 1) {
        result = QString("0%1").arg(result);
    }
    return result;
}

QString QUIHelper::byteArrayToAsciiStr(const QByteArray &data) {
    QString temp;
    int len = data.size();
    for (int i = 0; i < len; i++) {
        //0x20为空格,空格以下都是不可见字符
        char b = data.at(i);
        if (0x00 == b) {
            temp += QString("\\NUL");
        } else if (0x01 == b) {
            temp += QString("\\SOH");
        } else if (0x02 == b) {
            temp += QString("\\STX");
        } else if (0x03 == b) {
            temp += QString("\\ETX");
        } else if (0x04 == b) {
            temp += QString("\\EOT");
        } else if (0x05 == b) {
            temp += QString("\\ENQ");
        } else if (0x06 == b) {
            temp += QString("\\ACK");
        } else if (0x07 == b) {
            temp += QString("\\BEL");
        } else if (0x08 == b) {
            temp += QString("\\BS");
        } else if (0x09 == b) {
            temp += QString("\\HT");
        } else if (0x0A == b) {
            temp += QString("\\LF");
        } else if (0x0B == b) {
            temp += QString("\\VT");
        } else if (0x0C == b) {
            temp += QString("\\FF");
        } else if (0x0D == b) {
            temp += QString("\\CR");
        } else if (0x0E == b) {
            temp += QString("\\SO");
        } else if (0x0F == b) {
            temp += QString("\\SI");
        } else if (0x10 == b) {
            temp += QString("\\DLE");
        } else if (0x11 == b) {
            temp += QString("\\DC1");
        } else if (0x12 == b) {
            temp += QString("\\DC2");
        } else if (0x13 == b) {
            temp += QString("\\DC3");
        } else if (0x14 == b) {
            temp += QString("\\DC4");
        } else if (0x15 == b) {
            temp += QString("\\NAK");
        } else if (0x16 == b) {
            temp += QString("\\SYN");
        } else if (0x17 == b) {
            temp += QString("\\ETB");
        } else if (0x18 == b) {
            temp += QString("\\CAN");
        } else if (0x19 == b) {
            temp += QString("\\EM");
        } else if (0x1A == b) {
            temp += QString("\\SUB");
        } else if (0x1B == b) {
            temp += QString("\\ESC");
        } else if (0x1C == b) {
            temp += QString("\\FS");
        } else if (0x1D == b) {
            temp += QString("\\GS");
        } else if (0x1E == b) {
            temp += QString("\\RS");
        } else if (0x1F == b) {
            temp += QString("\\US");
        } else if (0x7F == b) {
            temp += QString("\\x7F");
        } else if (0x5C == b) {
            temp += QString("\\x5C");
        } else if (0x20 >= b) {
            temp += QString("\\x%1").arg(decimalToStrHex(static_cast<quint8>(b)));
        } else {
            temp += QString("%1").arg(b);
        }
    }
    return temp.trimmed();
}

QByteArray QUIHelper::hexStrToByteArray(const QString &str) {
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len / 2);
    char lstr, hstr;
    for (int i = 0; i < len;) {
        hstr = str.at(i).toLatin1();
        if (hstr == ' ') {
            i++;
            continue;
        }
        i++;
        if (i >= len) {
            break;
        }
        lstr = str.at(i).toLatin1();
        hexdata = convertHexChar(hstr);
        lowhexdata = convertHexChar(lstr);
        if ((hexdata == 16) || (lowhexdata == 16)) {
            break;
        } else {
            hexdata = hexdata * 16 + lowhexdata;
        }
        i++;
        senddata[hexdatalen] = static_cast<char>(hexdata);
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

char QUIHelper::convertHexChar(char ch) {
    if ((ch >= '0') && (ch <= '9')) {
        return ch - 0x30;
    } else if ((ch >= 'A') && (ch <= 'F')) {
        return ch - 'A' + 10;
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return ch - 'a' + 10;
    } else {
        return (-1);
    }
}

QByteArray QUIHelper::asciiStrToByteArray(const QString &str) {
    QByteArray buffer;
    int len = str.length();
    QString letter;
    QString hex;
    for (int i = 0; i < len; i++) {
        letter = str.at(i);
        if (letter == "\\") {
            i++;
            letter = str.mid(i, 1);
            if (letter == "x") {
                i++;
                hex = str.mid(i, 2);
                buffer.append(static_cast<char>(strHexToDecimal(hex)));
                i++;
                continue;
            } else if (letter == "N") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "L") {           //NUL=0x00
                        buffer.append(static_cast<char>(0x00));
                        continue;
                    }
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "K") {           //NAK=0x15
                        buffer.append(0x15);
                        continue;
                    }
                }
            } else if (letter == "S") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "H") {           //SOH=0x01
                        buffer.append(0x01);
                        continue;
                    } else {                    //SO=0x0E
                        buffer.append(0x0E);
                        i--;
                        continue;
                    }
                } else if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "X") {           //STX=0x02
                        buffer.append(0x02);
                        continue;
                    }
                } else if (hex == "I") {        //SI=0x0F
                    buffer.append(0x0F);
                    continue;
                } else if (hex == "Y") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "N") {           //SYN=0x16
                        buffer.append(0x16);
                        continue;
                    }
                } else if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "B") {           //SUB=0x1A
                        buffer.append(0x1A);
                        continue;
                    }
                }
            } else if (letter == "E") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "X") {           //ETX=0x03
                        buffer.append(0x03);
                        continue;
                    } else if (hex == "B") {    //ETB=0x17
                        buffer.append(0x17);
                        continue;
                    }
                } else if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "T") {           //EOT=0x04
                        buffer.append(0x04);
                        continue;
                    }
                } else if (hex == "N") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "Q") {           //ENQ=0x05
                        buffer.append(0x05);
                        continue;
                    }
                } else if (hex == "M") {        //EM=0x19
                    buffer.append(0x19);
                    continue;
                } else if (hex == "S") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "C") {           //ESC=0x1B
                        buffer.append(0x1B);
                        continue;
                    }
                }
            } else if (letter == "A") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "K") {           //ACK=0x06
                        buffer.append(0x06);
                        continue;
                    }
                }
            } else if (letter == "B") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "E") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "L") {           //BEL=0x07
                        buffer.append(0x07);
                        continue;
                    }
                } else if (hex == "S") {        //BS=0x08
                    buffer.append(0x08);
                    continue;
                }
            } else if (letter == "C") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "R") {               //CR=0x0D
                    buffer.append(0x0D);
                    continue;
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "N") {           //CAN=0x18
                        buffer.append(0x18);
                        continue;
                    }
                }
            } else if (letter == "D") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "L") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "E") {           //DLE=0x10
                        buffer.append(0x10);
                        continue;
                    }
                } else if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "1") {           //DC1=0x11
                        buffer.append(0x11);
                        continue;
                    } else if (hex == "2") {    //DC2=0x12
                        buffer.append(0x12);
                        continue;
                    } else if (hex == "3") {    //DC3=0x13
                        buffer.append(0x13);
                        continue;
                    } else if (hex == "4") {    //DC2=0x14
                        buffer.append(0x14);
                        continue;
                    }
                }
            } else if (letter == "F") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "F") {               //FF=0x0C
                    buffer.append(0x0C);
                    continue;
                } else if (hex == "S") {        //FS=0x1C
                    buffer.append(0x1C);
                    continue;
                }
            } else if (letter == "H") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "T") {               //HT=0x09
                    buffer.append(0x09);
                    continue;
                }
            } else if (letter == "L") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "F") {               //LF=0x0A
                    buffer.append(0x0A);
                    continue;
                }
            } else if (letter == "G") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "S") {               //GS=0x1D
                    buffer.append(0x1D);
                    continue;
                }
            } else if (letter == "R") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "S") {               //RS=0x1E
                    buffer.append(0x1E);
                    continue;
                }
            } else if (letter == "U") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "S") {               //US=0x1F
                    buffer.append(0x1F);
                    continue;
                }
            } else if (letter == "V") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "T") {               //VT=0x0B
                    buffer.append(0x0B);
                    continue;
                }
            } else if (letter == "\\") {
                //如果连着的是多个\\则对应添加\对应的16进制0x5C
                buffer.append(0x5C);
                continue;
            } else {
                //将对应的\[前面的\\也要加入
                buffer.append(0x5C);
                buffer.append(letter.toLatin1());
                continue;
            }
        }
        buffer.append(str.mid(i, 1).toLatin1());
    }
    return buffer;
}

QString QUIHelper::byteArrayToHexStr(const QByteArray &data) {
    QString temp = "";
    QString hex = data.toHex();
    for (int i = 0; i < hex.length(); i = i + 2) {
        temp += hex.mid(i, 2) + " ";
    }
    return temp.trimmed().toUpper();
}

QString QUIHelper::getSaveName(const QString &filter, QString defaultDir) {
    return QFileDialog::getSaveFileName(nullptr, "选择文件", defaultDir, filter);
}

QString QUIHelper::getFileName(const QString &filter, QString defaultDir) {
    return QFileDialog::getOpenFileName(nullptr, "选择文件", defaultDir, filter);
}

QStringList QUIHelper::getFileNames(const QString &filter, QString defaultDir) {
    return QFileDialog::getOpenFileNames(nullptr, "选择文件", defaultDir, filter);
}

QString QUIHelper::getFolderName() {
    return QFileDialog::getExistingDirectory();
}

QString QUIHelper::getFileNameWithExtension(const QString &strFilePath) {
    QFileInfo fileInfo(strFilePath);
    return fileInfo.fileName();
}

QStringList QUIHelper::getFolderFileNames(const QStringList &filter) {
    QStringList fileList;
    QString strFolder = QFileDialog::getExistingDirectory();
    if (0 != strFolder.length()) {
        QDir myFolder(strFolder);
        if (myFolder.exists()) {
            fileList = myFolder.entryList(filter);
        }
    }
    return fileList;
}

bool QUIHelper::folderIsExist(const QString &strFolder) {
    QDir tempFolder(strFolder);
    return tempFolder.exists();
}

bool QUIHelper::fileIsExist(const QString &strFile) {
    QFile tempFile(strFile);
    return tempFile.exists();
}

bool QUIHelper::copyFile(const QString &sourceFile, const QString &targetFile) {
    bool ok;
    ok = QFile::copy(sourceFile, targetFile);
    //将复制过去的文件只读属性取消
    ok = QFile::setPermissions(targetFile, QFile::WriteOwner);
    return ok;
}

void QUIHelper::deleteDirectory(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) {
        return;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList) {
        if (fi.isFile()) {
            fi.dir().remove(fi.fileName());
        } else {
            deleteDirectory(fi.absoluteFilePath());
            dir.rmdir(fi.absoluteFilePath());
        }
    }
}

bool QUIHelper::ipLive(const QString &ip, int port, int timeout) {
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, static_cast<quint16>(port));
    //超时没有连接上则判断不在线
    return tcpClient.waitForConnected(timeout);
}

QString QUIHelper::getHtml(const QString &url) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),
                     &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    return QString(responseData);
}

QString QUIHelper::getNetIP(const QString &webCode) {
    QString web = webCode;
    web = web.replace(' ', "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    QStringList list = web.split("<br/>");
    QString tar = list.at(3);
    QStringList ip = tar.split("=");
    return ip.at(1);
}

QString QUIHelper::getLocalIP() {
    QStringList ips;
    QList<QHostAddress> addrs = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrs) {
        QString ip = addr.toString();
        if (QUIHelper::isIP(ip)) {
            ips << ip;
        }
    }
    //优先取192开头的IP,如果获取不到IP则取127.0.0.1
    QString ip = "127.0.0.1";
    foreach (QString str, ips) {
        if (str.startsWith("192.168.1") || str.startsWith("192")) {
            ip = str;
            break;
        }
    }
    return ip;
}

QString QUIHelper::urlToIP(const QString &url) {
    QHostInfo host = QHostInfo::fromName(url);
    return host.addresses().at(0).toString();
}

bool QUIHelper::isWebOk() {
    //能接通百度IP说明可以通外网
    return ipLive("115.239.211.112", 80);
}

void QUIHelper::showMessageBoxInfo(const QString &info, int closeSec, bool exec) {
    if (exec) {
        QUIMessageBox msg;
        msg.setMessage(info, 0, closeSec);
        msg.exec();
    } else {
        QUIMessageBox::Instance()->setMessage(info, 0, closeSec);
        QUIMessageBox::Instance()->show();
    }
}

void QUIHelper::showMessageBoxError(const QString &info, int closeSec, bool exec) {
    if (exec) {
        QUIMessageBox msg;
        msg.setMessage(info, 2, closeSec);
        msg.exec();
    } else {
        QUIMessageBox::Instance()->setMessage(info, 2, closeSec);
        QUIMessageBox::Instance()->show();
    }
}

int QUIHelper::showMessageBoxQuestion(const QString &info) {
    QUIMessageBox msg;
    msg.setMessage(info, 1);
    return msg.exec();
}

