cmake_minimum_required(VERSION 3.16)

project(creator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(creator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        widget/viewwidget.h widget/viewwidget.cpp widget/viewwidget.ui
        widget/fileswidget.h widget/fileswidget.cpp widget/fileswidget.ui
        widget/nodeswidget.h widget/nodeswidget.cpp widget/nodeswidget.ui
        widget/attributewidget.h widget/attributewidget.cpp widget/attributewidget.ui
        core/data/image.h
        core/render.h core/render.cpp
        converter/imageconverter.h converter/imageconverter.cpp
        simulator/simulator.h simulator/simulator.cpp
        core/game.h core/game.cpp
        core/sprite/container.h core/sprite/container.cpp
        core/sprite/imagesprite.h core/sprite/imagesprite.cpp
        core/stage.h core/stage.cpp
        core/sprite/listsprite.h core/sprite/listsprite.cpp
        core/script.h core/script.cpp
        core/sprite/textsprite.h core/sprite/textsprite.cpp
        core/line.h core/line.cpp
        core/actuator.h core/actuator.cpp
        core/paintevent.h core/paintevent.cpp
        core/sprite/trigger.h core/sprite/trigger.cpp
        core/archive.h core/archive.cpp
        core/sprite/animationsprite.h core/sprite/animationsprite.cpp
        core/object/characterobject.h core/object/characterobject.cpp
        core/sprite/charactersprite.h core/sprite/charactersprite.cpp
        core/variable.h core/variable.cpp
        core/data/image.cpp
        core/data/equip.h core/data/equip.cpp
        core/sprite/rectsprite.h core/sprite/rectsprite.cpp
        core/utils/textutils.h core/utils/textutils.cpp
        core/font.h core/font.cpp
        converter/fontconverter.h converter/fontconverter.cpp
        core/scriptfunction.h core/scriptfunction.cpp
        core/action/action.h core/action/action.cpp
        core/action/moveaction.h core/action/moveaction.cpp
        core/action/walkaction.h core/action/walkaction.cpp
        core/action/floataction.h core/action/floataction.cpp
        core/action/popaction.h core/action/popaction.cpp
        simulator/simulatortoolswindow.h simulator/simulatortoolswindow.cpp simulator/simulatortoolswindow.ui
        core/sprite/charactershadowsprite.h core/sprite/charactershadowsprite.cpp
        core/action/sheetaction.h core/action/sheetaction.cpp
        core/object/variableobject.h core/object/variableobject.cpp
        inf/audio.h inf/audio.cpp
        inf/file.h inf/file.cpp
        inf/log.h inf/log.cpp
        core/assets/imageassets.h core/assets/imageassets.cpp

        core/assets/sheetassets.h core/assets/sheetassets.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET creator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(creator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(creator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(creator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.creator)
endif()
set_target_properties(creator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(MYLIB_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/")

include_directories(${MYLIB_HEADER})

include(GNUInstallDirs)
install(TARGETS creator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(creator)
endif()
