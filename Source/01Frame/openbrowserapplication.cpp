#include "openbrowserapplication.h"
#include "quihelper.h"
#include "quitrayicon.h"
#include "maskwidget.h"
#include "quiconfig.h"
#include "readivus.h"

openBrowserApplication::openBrowserApplication(QObject *parent) :
    QObject(parent),
    appReadyState_(true),
    appRunState_(false) {
    this->DirInitial();
    this->LogInitial();
    this->openBrowserInitial();
}

openBrowserApplication::~openBrowserApplication() {
    qui_->deleteLater();
    log_manager_->deleteLater();
}

bool openBrowserApplication::Run() {
    qDebug();
    if (appReadyState_ && !appRunState_) {
        if( QUIConfig::cmd_option_.debug_mode == true) {
            return true;
        }
        if( QUIConfig::cmd_option_.test_mode == true) {
            ReadIVUS *tmp = new ReadIVUS();
            tmp->show();
            return true;
        }
        if( QUIConfig::cmd_option_.relese_mode == true) {
            return true;
        }
        QUITrayIcon::Instance()->setIcon(":/Image/logo.ico");
        QUITrayIcon::Instance()->setVisible(true);
        QUITrayIcon::Instance()->setMainWidget(qui_);
        qui_->show();
        return true;
    } else {
        return false;
    }
}

void openBrowserApplication::LogInitial() {
    log_manager_ = new QUILogManager();
}

void openBrowserApplication::openBrowserInitial() {
    qui_ = new FormTitle();
    MaskWidget::Instance()->setDialogNames(QStringList("MaskWidget"));
    MaskWidget::Instance()->setMainWidget(qui_);
    QUIHelper::setStyle(":/Style/style.qss");
}

void openBrowserApplication::DirInitial() {

#ifdef Q_OS_WIN
#endif
#ifdef Q_OS_MAC
#endif

#ifdef Q_OS_LINUX
    QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    if (!QUIHelper::DirMake(QString("%1/.openBrowser").arg(home_path))) {
        qCritical() << "dir initial fail";
        appReadyState_ = false;
    } else {
        QDir::setCurrent(QString("%1/.openBrowser").arg(home_path));
    }
#endif
    QUIHelper::DirMake("./stl");
    QUIHelper::DirMake("./manaual");
}

void openBrowserApplication::DbInitial() {

}

void openBrowserApplication::FileInitial() {

}

void openBrowserApplication::LicenseInitial() {

}
