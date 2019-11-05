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
include_directories(  ${OpenCV_INCLUDE_DIRS} )

find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

find_package(Eigen3 REQUIRED)
include( ${EIGEN3_USE_FILE} )





option(BUILD_SHARED_LIBS "" OFF)
option(USE_SYSTEM_VTK "" ON)
option(USE_SYSTEM_ITK "" ON)

include_directories(Source/01Frame)
set(01Frame
    Source/01Frame/Resources/style.qrc
    Source/01Frame/Resources/Image.qrc
    Source/01Frame/app.h
    Source/01Frame/app.cpp
    Source/01Frame/stable.h
    Source/01Frame/myMenu.cpp
    Source/01Frame/myMenu.h
    )

include_directories(Source/02CustomControl)
include_directories(Source/02CustomControl/NetCom)
set(02CustomControl
    Source/02CustomControl/setupini.cpp
    Source/02CustomControl/setupini.h
    Source/02CustomControl/cpumemorylabel.cpp
    Source/02CustomControl/cpumemorylabel.h
    Source/02CustomControl/maskwidget.cpp
    Source/02CustomControl/maskwidget.h
    Source/02CustomControl/progressbarwait.cpp
    Source/02CustomControl/progressbarwait.h
    Source/02CustomControl/progressbarcolor.cpp
    Source/02CustomControl/progressbarcolor.h
    Source/02CustomControl/sliderbar.cpp
    Source/02CustomControl/sliderbar.h
    Source/02CustomControl/screenwidget.cpp
    Source/02CustomControl/screenwidget.h
    Source/02CustomControl/sliderrange.cpp
    Source/02CustomControl/sliderrange.h

    Source/02CustomControl/NetCom/settingsdialog.h
    Source/02CustomControl/NetCom/settingsdialog.cpp
    Source/02CustomControl/NetCom/settingsdialog.ui
    Source/02CustomControl/NetCom/frmtcpclient.h
    Source/02CustomControl/NetCom/frmtcpclient.cpp
    Source/02CustomControl/NetCom/frmtcpclient.ui
    Source/02CustomControl/NetCom/frmtcpserver.h
    Source/02CustomControl/NetCom/frmtcpserver.cpp
    Source/02CustomControl/NetCom/frmtcpserver.ui
    Source/02CustomControl/NetCom/frmudpserver.h
    Source/02CustomControl/NetCom/frmudpserver.cpp
    Source/02CustomControl/NetCom/frmudpserver.ui
    )

include_directories(Source/03Opencv)
set(03Opencv
    Source/03Opencv/qopencvprocessing.cpp
    Source/03Opencv/qopencvprocessing.h
    Source/03Opencv/qopencvwidget.h
    Source/03Opencv/qopencvwidget.cpp
    )

include_directories(Source/03CGAL)
include_directories(Source/03CGAL/CGALThread)
set(03CGAL
    Source/03CGAL/CGALThread/cgalthread.h
    Source/03CGAL/CGALThread/cgalthread.cpp
    Source/03CGAL/CGALThread/cgalthreadsubdivision.h
    Source/03CGAL/CGALThread/cgalthreadsubdivision.cpp
    Source/03CGAL/CGALThread/cgalthreadfill.h
    Source/03CGAL/CGALThread/cgalthreadfill.cpp
    )

include_directories(Source/03VTK)
include_directories(Source/03VTK/VTKThread)
set(03VTK
    Source/03VTK/customsurfaceviewer.h
    Source/03VTK/customsurfaceviewer.cpp
    Source/03VTK/customvtkrenderer.h
    Source/03VTK/customvtkrenderer.cpp
    Source/03VTK/linesurfaceclipper.h
    Source/03VTK/linesurfaceclipper.cpp
    Source/03VTK/automaticdivision.h
    Source/03VTK/automaticdivision.cpp
    Source/03VTK/smoothsurfaceselector.h
    Source/03VTK/smoothsurfaceselector.cpp
    Source/03VTK/refinesurface.cpp
    Source/03VTK/refinesurface.h

    Source/03VTK/VTKThread/vtkthread.h
    Source/03VTK/VTKThread/vtkthread.cpp
    Source/03VTK/VTKThread/vtkthreadimagedataread.h
    Source/03VTK/VTKThread/vtkthreadimagedataread.cpp
    Source/03VTK/VTKThread/vtkthreadpolydataread.h
    Source/03VTK/VTKThread/vtkthreadpolydataread.cpp
    Source/03VTK/VTKThread/vtkthreadmarchingcubes.h
    Source/03VTK/VTKThread/vtkthreadmarchingcubes.cpp
    Source/03VTK/VTKThread/vtkthreadpolydatawrite.h
    Source/03VTK/VTKThread/vtkthreadpolydatawrite.cpp
    Source/03VTK/VTKThread/vtkthreadsubdivision.h
    Source/03VTK/VTKThread/vtkthreadsubdivision.cpp
    )

include_directories(Source/04Ui)
set(04Ui
    Source/04Ui/formmain.h
    Source/04Ui/formmain.cpp
    Source/04Ui/formmain.ui
    Source/04Ui/formtitle.h
    Source/04Ui/formtitle.cpp
    Source/04Ui/formtitle.ui
    Source/04Ui/formleft.h
    Source/04Ui/formleft.cpp
    Source/04Ui/formleft.ui
    Source/04Ui/formshow.h
    Source/04Ui/formshow.ui
    Source/04Ui/formshow.cpp
    Source/04Ui/aboutinfo.h
    Source/04Ui/aboutinfo.cpp
    Source/04Ui/aboutinfo.ui
    Source/04Ui/formmaskwidget.h
    Source/04Ui/formmaskwidget.cpp
    Source/04Ui/formmaskwidget.ui
    Source/04Ui/formimagehandle.h
    Source/04Ui/formimagehandle.cpp
    Source/04Ui/formimagehandle.ui
    )

include_directories(Source/05Manager)
set(05Manager
    Source/05Manager/stlmanager.h
    Source/05Manager/stlmanager.cpp
    Source/05Manager/dcmmanager.h
    Source/05Manager/dcmmanager.cpp
    Source/05Manager/imagebrowsermanager.h
    Source/05Manager/imagebrowsermanager.cpp
    )

include_directories(Source/06Test)
include_directories(Source/06Test/MinPath)
include_directories(Source/06Test/EdgeAdjustment)
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
    )

set(Source
    main.cpp)

add_executable(${PROJECT_NAME}
    ${Source}
    ${01Frame}
    ${02CustomControl}
    ${03Opencv}
    ${03CGAL}
    ${03VTK}
    ${04Ui}
    ${05Manager}
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


