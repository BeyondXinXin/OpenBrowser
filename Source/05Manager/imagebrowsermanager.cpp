#include "imagebrowsermanager.h"
#include "mainwindow.h"
#include "formedgeadjustment.h"



ImageBrowserManager::ImageBrowserManager(QOpencvWidget &widget,
        QObject *parent) :
    QObject(parent), widget_(widget) {
    this->Initial();
}

ImageBrowserManager::~ImageBrowserManager() {

}

void ImageBrowserManager::Initial() {

}

void ImageBrowserManager::UnDo() {// 撤销
    if (imt_iter_ != img_vector.begin()) {// 前面还有对象
        imt_iter_--;
        this->widget_.SetSurface(*imt_iter_);
        if (imt_iter_ == img_vector.begin()) {// 自减后是否为初始图像
        }
    }
}

void ImageBrowserManager::ReDo() {// 重做
    if (imt_iter_ != (img_vector.end() - 1)) {// 后面还有对象
        imt_iter_++;
        this->widget_.SetSurface(*imt_iter_);
        if (imt_iter_ == (img_vector.end() - 1)) {// 自加后是否为最后一个
        }
    }
}

void ImageBrowserManager::OpenStlFile(const QString &file_path) {
    QImage *img = new QImage();
    if (!(img->load(file_path))) {
        QUIHelper::showMessageBoxError("打开图像失败！", 3, true);
        delete img;
        return;
    }
    this->widget_.SetSurface(*img);
    if (imt_iter_ != (img_vector.end() - 1)) {
        img_vector.erase(++imt_iter_, img_vector.end());
    }
    img_vector.append(*img);
    imt_iter_ = img_vector.end() - 1;

}

void ImageBrowserManager::SlotImgProcess(const int &operation) {
    if (this->img_vector.size() == 0) {
        emit SignalPromptInformationOut(tr("Image 数据错误"));
        return;
    }

    switch (operation) {
        case 601: {
                MainWindow *tmp = new MainWindow;
                tmp->OpenMinPathWidgetIn(widget_.GetSurface());
                break;
            }
        case 602: {
                FormEdgeAdjustment *tmp = new FormEdgeAdjustment();
                tmp->showMaximized();
                break;
            }
        default: {
                break;
            }
    }
}

