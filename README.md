# QT_openBrowser


## 介绍
基于QT      一个开源的文件浏览器   
支持stl、off、mhd、dcm等文件的浏览和前处理  
程序均来自网络整理，便于自己和他人使用。 
所有模块均采用manager管理，从程序中分割非常方便。  
其他功能持续增加维护，比如opencv与QT结合使用、QT+Halcon使用等
我的使用的版本见下方安装教程，由于能力有限，我仅维护测试ubuntu下程序，windos下需要自己简单修改就可以。  

代码主要复制于以下  
https://blog.csdn.net/webzhuce  阿兵-AI医疗  VKT中文教程  
https://blog.csdn.net/u013165921 笔尖bj opencv+qt结合  
https://me.csdn.net/feiyangqingyun   feiyangqingyun   QT自定义控件教程  
https://me.csdn.net/u011012932  一去丶二三里   QT常用控件基础  
https://doc.cgal.org/latest/Manual/index.html  CGAL 官方教程  
https://lorensen.github.io/VTKExamples/site/Cxx/#surface-reconstruction  VTK  官方教程  
https://itk.org/Doxygen/html/index.html  ITK  官方教程  
https://doc.qt.io/ qt 官方教程  

## 图片


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

姚欣  118.25.63.144  

分支说明  
branch——01  GitKraken软件新建分支、合并分支测试  

branch——02  程序优化  
1.删除vtk 封闭功能  
2.合并cgal封闭类和预览类（处理中会产生假死  
3.UI left按钮布局重新调整  
4.UI formshow 底部按钮状态调整  

branch——03  增加Opencv模块
1.界面框架重新调整
2.增加image模块(利用opencv处理)
3.增加两个测试控件  中心线提取  和 线拖动(仿ps)
4.优化若干bug


















