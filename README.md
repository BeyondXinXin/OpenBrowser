# QT_openBrowser

## 介绍
基于QT      一个开源的文件浏览器   

## 软件架构
分层架构  

1.文件结构  
/bin      程序exe生成目录，程序运行根目录（代码没有修改根目录，浏览过程中临时文件都存在这里，有需要可以放到专门的tmp目录下）  
/bulid    cmake构建目录，每个人都不一样，无需下载    
/Source   程序源码  
/Source/01Frame  程序框架，初始化相关  
/Source/02CustomControl  自定义小控件  
/Source/02CustomControl/NetCom  串口网口插件  
/Source/03Opencv  opencv相关  
/Source/03CGAL  CGAL相关  
/Source/03CGAL/CGALThread CGAL线程相关  
/Source/03VTK  VTK相关  
/Source/03VTK/VTKThread  VTK线程相关  
/Source/04Ui  UI相关  
/Source/05Manager  结构管理  
/Source/05Manager/UiManager  界面结构管理  

## 安装教程

开源库使用  
armadillo-9.600.6  
CGAL-4.13.1  
gmp-6.1.2  
ITK__4.13  
opencv-3.3.0  
pytorch  
VTK-8.1.2  

## 使用说明

自己工作中积累的知识汇总，一来方便自己查找，而来方便有需要的人下载使用

## 参与贡献

姚欣  779354187  118.25.63.144

分支说明
branch——01  GitKraken软件新建分支、合并分支测试


