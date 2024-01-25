# cmakeのversion 指定
cmake_minimum_required(VERSION 3.5)

# projectと言語の設定
project(fdtd1d_lib_gaussian LANGUAGES C)

# source filesの検索
file(GLOB_RECURSE SOURCES "./src/*.c")

# target名を決定し、source filesをtargetに付加
add_library(fdtd1d_lib_gaussian STATIC ${SOURCES})

# include files(header files)をtargetに付加
target_include_directories(fdtd1d_lib_gaussian INTERFACE ./include)

# math.hをtargetに付加
target_link_libraries(fdtd1d_lib_gaussian m)

# opengl用
# target_link_libraries(ftdt1d_gaussian GL)
# target_link_libraries(ftdt1d_gaussian glut)
# target_link_libraries(ftdt1d_gaussian glfw)
# target_link_libraries(ftdt1d_gaussian glfw3)
# target_link_libraries(ftdt1d_gaussian GLEW)
# target_link_libraries(ftdt1d_gaussian Xrandr)
# target_link_libraries(ftdt1d_gaussian Xinerama)
# target_link_libraries(ftdt1d_gaussian Xi)
# target_link_libraries(ftdt1d_gaussian Xxf86vm)
# target_link_libraries(ftdt1d_gaussian X11)
# target_link_libraries(ftdt1d_gaussian rt)
# target_link_libraries(ftdt1d_gaussian dl)
# target_link_libraries(ftdt1d_gaussian Xmu)
