#ifndef QUIICONHELPER_H
#define QUIICONHELPER_H
//图形字体处理类

#include "stable.h"

class QUIIconHelper : public QObject {
    Q_OBJECT

  public:
    static QUIIconHelper *Instance();
    explicit QUIIconHelper(QObject *parent = nullptr);

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
    static QScopedPointer<QUIIconHelper> self;

    QFont iconFont;             //图形字体
    QList<QToolButton *> btns;  //按钮队列
    QList<QPixmap> pixNormal;   //正常图片队列
    QList<QPixmap> pixDark;     //加深图片队列
};

#endif // QUIICONHELPER_H
