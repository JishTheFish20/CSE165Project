cmake_minimum_required(VERSION 3.5)

project(165 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Finding necessary Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL)  # Added OpenGL
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL)  # Added OpenGL

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(165
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(165 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(165
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Linking with Qt Widgets and OpenGL modules
target_link_libraries(165 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL)

# Optional: For iOS and macOS, set bundle identifier manually
if(${QT_VERSION} VERSION_LESS "6.1.0")
  set_target_properties(165 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.165
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
  )
endif()

include(GNUInstallDirs)
install(TARGETS 165
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(165)
endif()
