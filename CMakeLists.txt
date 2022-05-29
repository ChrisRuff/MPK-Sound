cmake_minimum_required(VERSION 3.20)
project(MPK-Sound)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(MPK-Sound
        MPK_Sound/main.cpp

        MPK_Sound/include/MainWindow.hpp
        MPK_Sound/include/Bean.hpp
        MPK_Sound/include/devices/DeviceManager.hpp
        MPK_Sound/include/devices/Keyboard.hpp
        MPK_Sound/include/components/Piano.hpp
        MPK_Sound/include/sound/Player.hpp

        MPK_Sound/src/MainWindow.cpp
        MPK_Sound/src/devices/DeviceManager.cpp
        MPK_Sound/src/components/Piano.cpp
        MPK_Sound/src/sound/Player.cpp)

target_include_directories(MPK-Sound
        ${component}
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${PROJECT_BINARY_DIR} # for generated header files, like config header
)
target_link_libraries(MPK-Sound
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

