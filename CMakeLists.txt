cmake_minimum_required(VERSION 3.1.0)
project(openBrowser)
list(APPEND SOURCES ${SOURCES_DIR}/logo.rc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

find_package(Qt5
    REQUIRED
    COMPONENTS
    Core
    Gui
    Widgets
    Sql
    Test
    Xml
    )

find_package(Qt5LinguistTools)
find_package(Qt5Network)
find_package(Qt5SerialPort)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} )

find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

find_package(Eigen3 REQUIRED)
include( ${EIGEN3_USE_FILE} )





option(BUILD_SHARED_LIBS "" OFF)
option(USE_SYSTEM_VTK "" ON)
option(USE_SYSTEM_ITK "" ON)

include_directories(Source/01Frame)
set(01Frame
    Source/01Frame/openbrowserapplication.h
    Source/01Frame/openbrowserapplication.cpp
    Source/01Frame/commandlinemanager.h
    Source/01Frame/commandlinemanager.cpp

    Source/01Frame/quiapplication.h
    Source/01Frame/quiapplication.cpp
    Source/01Frame/quimenu.cpp
    Source/01Frame/quimenu.h
    Source/01Frame/quihelper.h
    Source/01Frame/quihelper.cpp
    Source/01Frame/quiconfig.h
    Source/01Frame/quiconfig.cpp
    Source/01Frame/quitrayicon.h
    Source/01Frame/quitrayicon.cpp
    Source/01Frame/quiiconhelper.h
    Source/01Frame/quiiconhelper.cpp
    Source/01Frame/quimessagebox.h
    Source/01Frame/quimessagebox.cpp
    Source/01Frame/quiwidgetmove.h
    Source/01Frame/quiwidgetmove.cpp
    Source/01Frame/quilogmanager.h
    Source/01Frame/quilogmanager.cpp
    Source/01Frame/stable.h
    )

include_directories(Source/02Resources)
set(02Resources
    Source/02Resources/style.qrc
    Source/02Resources/Image.qrc
    )

# image modular
include_directories(Source/03ImageModular)
include_directories(Source/03ImageModular/PreProcessing)
set(03ImageMode
    Source/03ImageModular/imagebrowsermanager.h
    Source/03ImageModular/imagebrowsermanager.cpp
    Source/03ImageModular/PreProcessing/qopencvprocessing.cpp
    Source/03ImageModular/PreProcessing/qopencvprocessing.h
    Source/03ImageModular/PreProcessing/qopencvwidget.h
    Source/03ImageModular/PreProcessing/qopencvwidget.cpp
    Source/03ImageModular/PreProcessing/formimagehandle.h
    Source/03ImageModular/PreProcessing/formimagehandle.cpp
    Source/03ImageModular/PreProcessing/formimagehandle.ui
    )

# model modular
include_directories(Source/03ModelModular)
include_directories(Source/03ModelModular/PreProcessing)
include_directories(Source/03ModelModular/PreProcessing/VTKThread)
include_directories(Source/03ModelModular/PreProcessing/CGALThread)
set(03ModelModular
    Source/03ModelModular/stlmanager.h
    Source/03ModelModular/stlmanager.cpp

    Source/03ModelModular/PreProcessing/customsurfaceviewer.h
    Source/03ModelModular/PreProcessing/customsurfaceviewer.cpp
    Source/03ModelModular/PreProcessing/customvtkrenderer.h
    Source/03ModelModular/PreProcessing/customvtkrenderer.cpp
    Source/03ModelModular/PreProcessing/linesurfaceclipper.h
    Source/03ModelModular/PreProcessing/linesurfaceclipper.cpp
    Source/03ModelModular/PreProcessing/automaticdivision.h
    Source/03ModelModular/PreProcessing/automaticdivision.cpp
    Source/03ModelModular/PreProcessing/smoothsurfaceselector.h
    Source/03ModelModular/PreProcessing/smoothsurfaceselector.cpp
    Source/03ModelModular/PreProcessing/refinesurface.cpp
    Source/03ModelModular/PreProcessing/refinesurface.h
    Source/03ModelModular/PreProcessing/form3dreconstruction.cpp
    Source/03ModelModular/PreProcessing/form3dreconstruction.h
    Source/03ModelModular/PreProcessing/form3dreconstruction.ui

    Source/03ModelModular/PreProcessing/VTKThread/vtkthread.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthread.cpp
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadimagedataread.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadimagedataread.cpp
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadpolydataread.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadpolydataread.cpp
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadmarchingcubes.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadmarchingcubes.cpp
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadpolydatawrite.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadpolydatawrite.cpp
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadsubdivision.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadsubdivision.cpp
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadform3dreconstruction.h
    Source/03ModelModular/PreProcessing/VTKThread/vtkthreadform3dreconstruction.cpp

    Source/03ModelModular/PreProcessing/CGALThread/cgalthread.h
    Source/03ModelModular/PreProcessing/CGALThread/cgalthread.cpp
    Source/03ModelModular/PreProcessing/CGALThread/cgalthreadsubdivision.h
    Source/03ModelModular/PreProcessing/CGALThread/cgalthreadsubdivision.cpp
    Source/03ModelModular/PreProcessing/CGALThread/cgalthreadfill.h
    Source/03ModelModular/PreProcessing/CGALThread/cgalthreadfill.cpp

    )

# Dcm Modular
include_directories(Source/03DcmModular)
include_directories(Source/03DcmModular/PreProcessing)
set(03DcmModular
    Source/03DcmModular/dcmmanager.h
    Source/03DcmModular/dcmmanager.cpp
    )

# Images Modular
include_directories(Source/03ImagesModular)
include_directories(Source/03ImagesModular/PreProcessing)
set(03ImagesModular
    Source/03ImagesModular/imagesbrowermanager.cpp
    Source/03ImagesModular/imagesbrowermanager.h
    Source/03ImagesModular/PreProcessing/formshow.h
    Source/03ImagesModular/PreProcessing/formshow.ui
    Source/03ImagesModular/PreProcessing/formshow.cpp
    )


include_directories(Source/04Ui)
set(04Ui
    Source/04Ui/formmain.h
    Source/04Ui/formmain.cpp
    Source/04Ui/formmain.ui
    Source/04Ui/formtitle.h
    Source/04Ui/formtitle.cpp
    Source/04Ui/formtitle.ui
    )

include_directories(Source/04Widget)
include_directories(Source/04Widget/CustomControl)
include_directories(Source/04Widget/CustomControl/NetCom)
set(04Widget
    Source/04Widget/formleft.h
    Source/04Widget/formleft.cpp
    Source/04Widget/formleft.ui
    Source/04Widget/aboutinfo.h
    Source/04Widget/aboutinfo.cpp
    Source/04Widget/aboutinfo.ui
    Source/04Widget/formmaskwidget.h
    Source/04Widget/formmaskwidget.cpp
    Source/04Widget/formmaskwidget.ui

    Source/04Widget/CustomControl/setupini.cpp
    Source/04Widget/CustomControl/setupini.h
    Source/04Widget/CustomControl/cpumemorylabel.cpp
    Source/04Widget/CustomControl/cpumemorylabel.h
    Source/04Widget/CustomControl/maskwidget.cpp
    Source/04Widget/CustomControl/maskwidget.h
    Source/04Widget/CustomControl/progressbarwait.cpp
    Source/04Widget/CustomControl/progressbarwait.h
    Source/04Widget/CustomControl/progressbarcolor.cpp
    Source/04Widget/CustomControl/progressbarcolor.h
    Source/04Widget/CustomControl/sliderbar.cpp
    Source/04Widget/CustomControl/sliderbar.h
    Source/04Widget/CustomControl/screenwidget.cpp
    Source/04Widget/CustomControl/screenwidget.h
    Source/04Widget/CustomControl/sliderrange.cpp
    Source/04Widget/CustomControl/sliderrange.h
    Source/04Widget/CustomControl/NetCom/settingsdialog.h
    Source/04Widget/CustomControl/NetCom/settingsdialog.cpp
    Source/04Widget/CustomControl/NetCom/settingsdialog.ui
    Source/04Widget/CustomControl/NetCom/frmtcpclient.h
    Source/04Widget/CustomControl/NetCom/frmtcpclient.cpp
    Source/04Widget/CustomControl/NetCom/frmtcpclient.ui
    Source/04Widget/CustomControl/NetCom/frmtcpserver.h
    Source/04Widget/CustomControl/NetCom/frmtcpserver.cpp
    Source/04Widget/CustomControl/NetCom/frmtcpserver.ui
    Source/04Widget/CustomControl/NetCom/frmudpserver.h
    Source/04Widget/CustomControl/NetCom/frmudpserver.cpp
    Source/04Widget/CustomControl/NetCom/frmudpserver.ui
    )

include_directories(Source/06Test)
include_directories(Source/06Test/MinPath)
include_directories(Source/06Test/EdgeAdjustment)
include_directories(Source/06Test/IVUSread)
include_directories(Source/06Test/Anisotropicfiltering)
set(06Test
    Source/06Test/MinPath/minimalpathextraction.h
    Source/06Test/MinPath/custom_item.h
    Source/06Test/MinPath/custom_item.cpp
    Source/06Test/MinPath/mainwindow.h
    Source/06Test/MinPath/mainwindow.cpp
    Source/06Test/MinPath/mainwindow.ui
    Source/06Test/EdgeAdjustment/formedgeadjustment.h
    Source/06Test/EdgeAdjustment/formedgeadjustment.cpp
    Source/06Test/EdgeAdjustment/formedgeadjustment.ui
    Source/06Test/IVUSread/readivus.cpp
    Source/06Test/IVUSread/readivus.h
    Source/06Test/IVUSread/readivus.ui
    Source/06Test/Anisotropicfiltering/anisotropicfiltering.h
    Source/06Test/Anisotropicfiltering/anisotropicfiltering.cpp
    )

set(Source
    main.cpp)

add_executable(${PROJECT_NAME}
    ${Source}
    ${01Frame}
    ${02Resources}
    ${03ImageMode}
    ${03ModelModular}
    ${03DcmModular}
    ${03ImagesModular}
    ${04Ui}    
    ${04Widget}
    ${06Test}
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${ITK_LIBRARIES}
    )
target_link_libraries(
    ${PROJECT_NAME}
    ${VTK_LIBRARIES}
    )
target_link_libraries(
    ${PROJECT_NAME}
    "${CGAL_LIBS}"
    )
target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::SerialPort
    Qt5::Sql
    Qt5::Xml
    Qt5::Network
    Qt5::SerialPort
    )
target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
    "opencv_core"
    "opencv_highgui"
    "opencv_imgcodecs"
    "opencv_imgproc"
    "dl")


