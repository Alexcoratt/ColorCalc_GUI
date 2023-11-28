cmake_minimum_required(VERSION 3.5)

project(ColorCalc_GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES ColorCalc_GUI_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        itab.h
        itab.cpp

        common_methods.h
        common_methods.cpp

        paintcalculationtab.h
        paintcalculationtab.cpp

        lacquercalculationtab.h
        lacquercalculationtab.cpp

        foilcalculationtab.h
        foilcalculationtab.cpp

        foilrollstab.h
        foilrollstab.cpp

        presetcreationpopup.h
        presetcreationpopup.cpp

        presetupdatepopup.h
        presetupdatepopup.cpp

        presetremovalpopup.h
        presetremovalpopup.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ColorCalc_GUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ColorCalc_GUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ColorCalc_GUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ColorCalc_GUI
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ColorCalc_GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ColorCalc_GUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ColorCalc_GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ColorCalc_GUI)
endif()

add_subdirectory(/home/alexsm/LinuxFiles/Workshop/projects/ColorCalc bin)
target_link_libraries(${PROJECT_NAME} PRIVATE ColorCalc_lib)

add_subdirectory(/home/alexsm/LinuxFiles/Workshop/projects/ColorCalc_GUI/NamedField NamedField/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE NamedField_lib)

add_subdirectory(/home/alexsm/LinuxFiles/Workshop/projects/ColorCalc_GUI/PopUp PopUp/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE PopUp_lib)
