#ifndef FORMMAIN_H
#define FORMMAIN_H

// 01frame includes
#include "app.h"
#include "myMenu.h"

// 04 uimanager includes
#include "stlmanager.h"
#include "dcmmanager.h"

// 05vtkthread includes
#include "vtkthreadpolydataread.h"
#include "vtkthreadimagedataread.h"
#include "vtkthreadmarchingcubes.h"
#include "vtkthreadpolydatawrite.h"

// VTK includes
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkOutlineFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkImageShrink3D.h>
#include <vtkImageResample.h>
#include <vtkPolyDataMapper.h>
#include <vtkDistanceWidget.h>
#include <vtkImagePlaneWidget.h>
#include <vtkResliceImageViewer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkResliceImageViewerMeasurements.h>

namespace Ui {
    class FormMain;
}

class myMenu;

class FormMain : public QWidget {
    Q_OBJECT
  public:
    explicit FormMain(QWidget *parent = nullptr);
    ~FormMain();

  Q_SIGNALS:
    void SignalMaskWidgetDisappearOut();

  private :
    void initFrom();

  private Q_SLOTS:
    //响应打开图像文件的槽函数
    void SlotOpenFileIn(QString tmp_file = "");
    void SlotLaftIn(const int int_tmp, const QString qstr_tmp);

  private:
    Ui::FormMain *ui;
    myMenu *I_menubar;
    // imagedata manager
    QPointer<DcmManager> dcm_manager_;// dcm show
    // polydata manager
    QPointer<STLManager> stl_manager_;// stl show
};

#endif // FORMMAIN_H
