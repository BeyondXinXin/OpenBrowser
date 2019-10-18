#ifndef ABOUTINFO_H
#define ABOUTINFO_H

// 01frame includes
#include <app.h>


namespace Ui {
class AboutInfo;
}

class AboutInfo : public QWidget {
    Q_OBJECT

  public:
    explicit AboutInfo(QWidget *parent = nullptr);
    virtual ~AboutInfo() override;
  private:
    void Initial();
  private:
    Ui::AboutInfo *ui;
};

#endif // ABOUTINFO_H
