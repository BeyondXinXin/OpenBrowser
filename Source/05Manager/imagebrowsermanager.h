/*
 * image browser 模块 manager
*/

#ifndef IMAGEBROWSERMANAGER_H
#define IMAGEBROWSERMANAGER_H

#include <app.h>
#include "qopencvprocessing.h"
#include "qopencvwidget.h"

class ImageBrowserManager: public QObject {
    Q_OBJECT
  public:

    explicit ImageBrowserManager(QOpencvWidget &widget,
                                 QObject *parent = nullptr);
    virtual ~ImageBrowserManager() override;
    void OpenStlFile(const QString &file_path);

  public Q_SLOTS:
    void SlotImgProcess(const int);

  private:
    void Initial();
    void UnDo();
    void ReDo();

  private:
    QOpencvWidget &widget_;
    QVector<QImage> img_vector;	                // 存储图像的Vector容器
    QVector<QImage>::iterator imt_iter_;		// Vector迭代器



};

#endif // IMAGEBROWSERMANAGER_H
