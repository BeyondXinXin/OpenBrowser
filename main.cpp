// 01frame includes
#include <app.h>

// 02control includes
#include "maskwidget.h"

// 04ui includes
#include "formmain.h"
#include "formtitle.h"


// VTK includes
#include <vtkOutputWindow.h>

int main(int argc, char *argv[]) {
    vtkOutputWindow::SetGlobalWarningDisplay(0);
    Application a(argc, argv);
    if (!a.lock()) {
        QUIHelper::showMessageBoxError("正在运行，请不要重复启动", 5, true);
        return 0;
    }
    FormTitle qui;
    TrayIcon::Instance()->setMainWidget(&qui);
    MaskWidget::Instance()->setMainWidget(&qui);
    QUIHelper::setStyle(":/Style/style.qss");
    //------开始------//
    qui.show();

    return a.exec();
}




























