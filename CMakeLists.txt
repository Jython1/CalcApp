cmake_minimum_required(VERSION 3.16)

project(CalcApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_add_executable(appCalcApp
    main.cpp
    calclogic.cpp
    calclogic.h
)

qt_add_qml_module(appCalcApp
    URI CalcApp
    VERSION 1.0
    QML_FILES
        Main.qml
        CalcButton.qml
        Calc.qml
        QML_FILES SecretWindow.qml
)

target_link_libraries(appCalcApp
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

# Установки для macOS и Windows можно оставить, если нужны
set_target_properties(appCalcApp PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS appCalcApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
