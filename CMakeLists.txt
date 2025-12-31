cmake_minimum_required(VERSION 3.28)
project(WhatsApp)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -flto -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion")

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        WebEngineWidgets
)

find_package(fmt CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)
qt6_add_resources(RCC_SOURCES resources/resources.qrc)

add_executable(WhatsApp
        ${SOURCES}
        ${HEADERS}
        ${RCC_SOURCES}
)

target_link_libraries(WhatsApp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::WebEngineWidgets
        fmt::fmt
        glog::glog
)

target_include_directories(WhatsApp PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
)

install(TARGETS WhatsApp
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
