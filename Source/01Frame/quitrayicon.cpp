#include "quitrayicon.h"

QScopedPointer<QUITrayIcon> QUITrayIcon::self;
QUITrayIcon *QUITrayIcon::Instance() {
    if (self.isNull()) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new QUITrayIcon);
        }
    }
    return self.data();
}

QUITrayIcon::QUITrayIcon(QObject *parent) : QObject(parent) {
    mainWidget = nullptr;
    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    menu = new QMenu(QApplication::desktop());
    exitDirect = true;
}

void QUITrayIcon::iconIsActived(QSystemTrayIcon::ActivationReason reason) {
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

void QUITrayIcon::setExitDirect(bool exitDirect) {
    if (this->exitDirect != exitDirect) {
        this->exitDirect = exitDirect;
    }
}

void QUITrayIcon::setMainWidget(QWidget *mainWidget) {
    this->mainWidget = mainWidget;
    menu->addAction("主界面", mainWidget, SLOT(on_btnMenu_Min_clicked()));
    if (exitDirect) {
        menu->addAction("退出", this, SLOT(closeAll()));
    } else {
        menu->addAction("退出", this, SIGNAL(trayIconExit()));
    }
    trayIcon->setContextMenu(menu);
}

void QUITrayIcon::showMessage(
    const QString &title, const QString &msg,
    QSystemTrayIcon::MessageIcon icon, int msecs) {
    trayIcon->showMessage(title, msg, icon, msecs);
}

void QUITrayIcon::setIcon(const QString &strIcon) {
    trayIcon->setIcon(QIcon(strIcon));
}

void QUITrayIcon::setToolTip(const QString &tip) {
    trayIcon->setToolTip(tip);
}

void QUITrayIcon::setVisible(bool visible) {
    trayIcon->setVisible(visible);
}

void QUITrayIcon::closeAll() {
    trayIcon->hide();
    trayIcon->deleteLater();
    exit(0);
}


