//01frame
#include "maskwidget.h"

//qt
#include <qapplication.h>

MaskWidget *MaskWidget::self = nullptr;
MaskWidget::MaskWidget(QWidget *parent) : QWidget(parent) {
    mainWidget = nullptr;
    setOpacity(0.7);
    setBgColor(QColor(0, 0, 0));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    qApp->installEventFilter(this);
}

void MaskWidget::setMainWidget(QWidget *mainWidget) {
    if (this->mainWidget != mainWidget) {
        this->mainWidget = mainWidget;
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    }
}

void MaskWidget::setDialogNames(const QStringList &dialogNames) {
    if (this->dialogNames != dialogNames) {
        this->dialogNames = dialogNames;
    }
}

void MaskWidget::setOpacity(double opacity) {
    this->setWindowOpacity(opacity);
}

void MaskWidget::setBgColor(const QColor &bgColor) {
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, bgColor);
    this->setPalette(palette);
}

void MaskWidget::showEvent(QShowEvent *) {
    if (mainWidget != nullptr) {
        if (mainWidget->isFullScreen()) {
            this->showFullScreen();
        } else {
            this->setGeometry(mainWidget->geometry());
        }
    }
}

bool MaskWidget::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Show) {
        if (dialogNames.contains(obj->objectName())) {
            this->show();
        }
    } else if (event->type() == QEvent::Hide) {
        if (dialogNames.contains(obj->objectName())) {
            this->hide();
        }
    }
    return QObject::eventFilter(obj, event);
}
