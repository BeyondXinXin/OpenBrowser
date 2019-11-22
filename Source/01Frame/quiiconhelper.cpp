#include "quiiconhelper.h"


QScopedPointer<QUIIconHelper> QUIIconHelper::self;
QUIIconHelper *QUIIconHelper::Instance() {
    if (self.isNull()) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new QUIIconHelper);
        }
    }
    return self.data();
}

QUIIconHelper::QUIIconHelper(QObject *parent) : QObject(parent) {
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

QFont QUIIconHelper::getIconFont() {
    return this->iconFont;
}

void QUIIconHelper::setIcon(QLabel *lab, const QChar &str, quint32 size) {
    iconFont.setPixelSize(static_cast<int>(size));
    lab->setFont(iconFont);
    lab->setText(str);
}

void QUIIconHelper::setIcon(QAbstractButton *btn, const QChar &str, quint32 size) {
    iconFont.setPixelSize(static_cast<int>(size));
    btn->setFont(iconFont);
    btn->setText(str);
}

QPixmap QUIIconHelper::getPixmap(const QColor &color, const QChar &str, quint32 size,
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

QPixmap QUIIconHelper::getPixmap(QToolButton *btn, bool normal) {
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

bool QUIIconHelper::eventFilter(QObject *watched, QEvent *event) {
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

