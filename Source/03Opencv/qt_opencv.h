/**
 * opencv 常用函数qt插件
 * 1:OpencvImgChange  图片转换类
 * 2:OpencvEnhance    图像改变类
 * 3:OpencvGeom       图像几何变换类
 * 4:OpencvGray       图像增强类
 * 5:OpencvMorp       图像腐蚀类
 */

#ifndef QT_OPENCV_H
#define QT_OPENCV_H

#include <app.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
using namespace cv;
using namespace std;

class OpencvImgChange;
// 图像转换
class OpencvImgChange {
  public:
    OpencvImgChange();
    ~OpencvImgChange();
    QImage cvMat2QImage(const Mat &mat);// Mat 改成 QImage
    Mat QImage2cvMat(QImage image);// QImage 改成 Mat
    QImage splitBGR(QImage src, int color);	// 提取RGB分量
    QImage splitColor(QImage src, String model, int color);// 提取分量
};

// 图像改变
class OpencvEnhance {
  public:
    OpencvEnhance();
    ~OpencvEnhance();
    QImage Normalized(QImage src, int kernel_length);// 简单滤波
    QImage Gaussian(QImage src, int kernel_length);	// 高斯滤波
    QImage Median(QImage src, int kernel_length);// 中值滤波
    QImage Sobel(QImage src, int kernel_length);// sobel边缘检测
    QImage Laplacian(QImage src, int kernel_length);// laplacian边缘检测
    QImage Canny(QImage src, int kernel_length, int lowThreshold);// canny边缘检测
    QImage HoughLine(
        QImage src, int threshold, double minLineLength, double maxLineGap);// 线检测
    QImage HoughCircle(QImage src, int minRadius, int maxRadius);// 圆检测

  private:
    OpencvImgChange *imgchangeClass;
};

// 图像几何变换
class OpencvGeom {
  public:
    OpencvGeom();
    ~OpencvGeom();
    QImage Resize(QImage src, int length, int width);
    QImage Enlarge_Reduce(QImage src, int times);
    QImage Rotate(QImage src, int angle);
    QImage Rotate_fixed(QImage src, int angle);
    QImage Flip(QImage src, int flipcode);
    QImage Lean(QImage src, int x, int y);
  private:
    OpencvImgChange *imgchangeClass;
};

// 图像增强
class OpencvGray {
  public:
    OpencvGray();
    ~OpencvGray();
    QImage Bin(QImage src, int threshold);
    QImage Graylevel(QImage src);
    QImage Reverse(QImage src);								// 图像反转
    QImage Linear(QImage src, int alpha, int beta);			// 线性变换
    QImage Gamma(QImage src, int gamma);					// 伽马变换(指数变换)
    QImage Log(QImage src, int c);							// 对数变换
    QImage Histeq(QImage src);								// 直方图均衡化
    void BinToGraylevel(Mat &image);
    bool IsBin(Mat &image);
  private:
    OpencvImgChange *imgchangeClass;
};

// 图像腐蚀
class OpencvMorp {
  public:
    OpencvMorp();
    ~OpencvMorp();
    QImage Erode(QImage src, int elem, int kernel, int times, int, int);// 腐蚀
    QImage Dilate(QImage src, int elem, int kernel, int times, int, int);// 膨胀
    QImage Open(QImage src, int elem, int kernel, int times, int, int);// 开运算
    QImage Close(QImage src, int elem, int kernel, int times, int, int);// 闭运算
    QImage Grad(QImage src, int elem, int kernel, int, int, int);// 形态学梯度
    QImage Tophat(QImage src, int elem, int kernel, int, int, int);// 顶帽操作
    QImage Blackhat(QImage src, int elem, int kernel, int, int, int);// 黑帽操作
  private:
    OpencvImgChange *imgchangeClass;
};

#endif // QT_OPENCV_H
