TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    drone-test/src/LinuxInteractive.cpp \
    osdk-core/src/DJI_API.cpp \
    osdk-core/src/DJI_App.cpp \
    osdk-core/src/DJI_Camera.cpp \
    osdk-core/src/DJI_Codec.cpp \
    osdk-core/src/DJI_Flight.cpp \
    osdk-core/src/DJI_Follow.cpp \
    osdk-core/src/DJI_HardDriver.cpp \
    osdk-core/src/DJI_HotPoint.cpp \
    osdk-core/src/DJI_Link.cpp \
    osdk-core/src/DJI_Logging.cpp \
    osdk-core/src/DJI_Memory.cpp \
    osdk-core/src/DJI_Mission.cpp \
    osdk-core/src/DJI_VirtualRC.cpp \
    osdk-core/src/DJI_WayPoint.cpp \
    osdk-wrapper/src/LinuxCamera.cpp \
    osdk-wrapper/src/LinuxCleanup.cpp \
    osdk-wrapper/src/LinuxFlight.cpp \
    osdk-wrapper/src/LinuxMobile.cpp \
    osdk-wrapper/src/LinuxSetup.cpp \
    osdk-wrapper/src/LinuxWaypoint.cpp \
    osdk-wrapper/src/ReadUserConfig.cpp \
    platform/src/LinuxSerialDevice.cpp \
    platform/src/LinuxThread.cpp

HEADERS += \
    drone-test/inc/LinuxInteractive.h \
    osdk-core/inc/DJI_API.h \
    osdk-core/inc/DJI_App.h \
    osdk-core/inc/DJI_Camera.h \
    osdk-core/inc/DJI_Codec.h \
    osdk-core/inc/DJI_Config.h \
    osdk-core/inc/DJI_Flight.h \
    osdk-core/inc/DJI_Follow.h \
    osdk-core/inc/DJI_HardDriver.h \
    osdk-core/inc/DJI_HotPoint.h \
    osdk-core/inc/DJI_Link.h \
    osdk-core/inc/DJI_Logging.h \
    osdk-core/inc/DJI_Memory.h \
    osdk-core/inc/DJI_Mission.h \
    osdk-core/inc/DJI_Type.h \
    osdk-core/inc/DJI_Version.h \
    osdk-core/inc/DJI_VirtualRC.h \
    osdk-core/inc/DJI_WayPoint.h \
    osdk-core/inc/DJICommonType.h \
    osdk-wrapper/inc/LinuxCamera.h \
    osdk-wrapper/inc/LinuxCleanup.h \
    osdk-wrapper/inc/LinuxFlight.h \
    osdk-wrapper/inc/LinuxMobile.h \
    osdk-wrapper/inc/LinuxSetup.h \
    osdk-wrapper/inc/LinuxWaypoint.h \
    osdk-wrapper/inc/ReadUserConfig.h \
    platform/LinuxSerialDevice.h \
    platform/LinuxThread.h \
    platform/inc/LinuxSerialDevice.h \
    platform/inc/LinuxThread.h

 INCLUDEPATH += \
/home/wsn/Documents/QT/drone_test/drone-test/inc\
/home/wsn/Documents/QT/drone_test/osdk-core/inc\
/home/wsn/Documents/QT/drone_test/osdk-wrapper/inc\
/home/wsn/Documents/QT/drone_test/platform/inc

LIBS += -lpthread

DISTFILES += \
    video_run.py

INCLUDEPATH += -I /usr/include/python2.7
LIBS += -lpython2.7

INCLUDEPATH += -I /usr/local/include/opencv2/highgui\
/usr/local/include/opencv2/core\
/usr/local/include/opencv2/imgproc\
/usr/local/include/opencv2/videoio

LIBS += -lopencv_highgui\
-lopencv_core\
-lopencv_imgproc\
-lopencv_videoio



