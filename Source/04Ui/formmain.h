#ifndef FORMMAIN_H
#define FORMMAIN_H

/*
 * 主界面
 */

// 01 Frame includes
#include "stable.h"
#include "quimenu.h"

// 05 UiManager includes
#include "stlmanager.h"
#include "dcmmanager.h"
#include "imagebrowsermanager.h"

namespace Ui {
    class FormMain;
}

class QUIMenu;

class FormMain : public QWidget {
    Q_OBJECT
  public:
    explicit FormMain(QWidget *parent = nullptr);
    ~FormMain();

  Q_SIGNALS:
    void SignalMainWindosChangeOut(const int);
  private :
    void initFrom();
  private Q_SLOTS:
    void SlotOpenFileIn(QString tmp_file = "");// 打开文件
    void SlotSetMainWindos(const int mainwindow);
  private:
    Ui::FormMain *ui;
    QUIMenu *I_menubar;
    // image manager
    QPointer<ImageBrowserManager> image_manager_;
    // mode manager
    QPointer<STLManager> mode_manager_;
    // dcm manager
    QPointer<DcmManager> dcm_manager_;
};

#endif // FORMMAIN_H
