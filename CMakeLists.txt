cmake_minimum_required(VERSION 3.7)

project(QTaskbarControl VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME}
    qtaskbarcontrol.cpp
    qtaskbarcontrol_p.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

if(UNIX AND NOT APPLE AND NOT ANDROID)
    target_sources(${PROJECT_NAME} PRIVATE qtaskbarcontrol_x11.cpp)

    find_package(Qt5 COMPONENTS DBus REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::DBus)
elseif(WIN32)
    set(CMAKE_AUTORCC ON)

    target_sources(${PROJECT_NAME} PRIVATE
        qtaskbarcontrol_win.cpp
        qtaskbarcontrol.qrc
    )

    find_package(Qt5 COMPONENTS WinExtras REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::WinExtras)
elseif(APPLE AND NOT IOS)
    target_sources(${PROJECT_NAME} PRIVATE qtaskbarcontrol_mac.mm)

    find_package(Qt COMPONENTS MacExtras REQUIRED)
    find_library(APPKIT_LIBRARY AppKit)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::MacExtras ${APPKIT_LIBRARY})
else()
    target_sources(${PROJECT_NAME} PRIVATE qtaskbarcontrol_dummy.cpp)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC Q_TASKBAR_CONTROL_EXPORT=)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
