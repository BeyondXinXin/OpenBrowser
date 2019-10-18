#ifndef FORMSHOW_H
#define FORMSHOW_H

//01frame
#include <app.h>

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
    Ui::FormShow *ui;

    bool videoMax;
    int videoCount;
    QString videoType;
    QMenu *videoMenu;
    QList<QLabel *> widgets;

  private slots:
    void Initial();

  private slots:
    void show_video_all();
    void show_video_4();
    void show_video_6();
    void show_video_8();
    void show_video_9();
    void show_video_16();

    void hide_video_all();
    void change_video(int index, int flag);

    void change_video_4(int index);
    void change_video_6(int index);
    void change_video_8(int index);
    void change_video_9(int index);
    void change_video_16(int index);
    void on_frmshowpushButton_8_clicked();
    void on_frmshowpushButton_9_clicked();
    void on_frmshowpushButton_10_clicked();
    void on_frmshowpushButton_11_clicked();
    void on_frmshowpushButton_12_clicked();
    void on_frmshowpushButton_clicked();
};

#endif // FORMSHOW_H
