#ifndef FORMSHOW_H
#define FORMSHOW_H

/*
 * ImagesBrowser 组件
 */

// 01 Frame includes
#include "stable.h"

namespace Ui {
    class FormShow;
}

class FormShow : public QWidget {
    Q_OBJECT
  public:
    explicit FormShow(QWidget *parent = nullptr);
    ~FormShow();

  protected:
    bool eventFilter(QObject *watched, QEvent *event);
  private:
    void Initial();
  private slots:
    void ShowVideoAll();
    void ShowVideo4();
    void ShowVideo6();
    void ShowVideo8();
    void ShowVideo9();
    void ShowVideo16();
    void HideVideoAll();
    void ChangeVideo(const qint32 index, const qint32 flag);
    void ChangeVideo4(const qint32 index);
    void ChangeVideo6(const qint32 index);
    void ChangeVideo8(const qint32 index);
    void ChangeVideo9(const qint32 index);
    void ChangeVideo16(const qint32 index);
    void on_frmshowpushButton_8_clicked();
    void on_frmshowpushButton_9_clicked();
    void on_frmshowpushButton_10_clicked();
    void on_frmshowpushButton_11_clicked();
    void on_frmshowpushButton_12_clicked();
    void on_frmshowpushButton_clicked();
  private:
    Ui::FormShow *ui;
    bool video_max_;
    qint32 video_count_;
    QString video_type_;
    QMenu *video_menu_;
    QList<QLabel *> widgets_;


};

#endif // FORMSHOW_H
