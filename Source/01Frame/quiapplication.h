/**
 * qt UIWidget 框架
 */

#ifndef APP_H
#define APP_H
#include "stable.h"

// 仅能启动一个实例
class QUIApplication : public QApplication {
    Q_OBJECT

  public:
    QUIApplication(int &argc, char **argv);
    ~QUIApplication();
    bool lock();
  private:
    QSharedMemory *_singular; // shared memory !! SINGLE ACCESS
};

#endif // APP_H
