# CMakeのバージョン指定
cmake_minimum_required(VERSION 3.5)

# CMakeのキャッシュ内にコンパイラのパスを設定
# C++の場合は LANGUAGES CXX を指定して同様に設定する。
set(CMAKE_C_COMPILER /usr/bin/gcc-11 CACHE FILEPATH "C Compiler")

#プロジェクトの指定と言語の指定
project(fdtd1d_main LANGUAGES C)

# buildの種類を"Debug"に指定する。
set(CMAKE_BUILD_TYPE "Debug")

# Debug情報を含む
set(CMAKE_C_FLAGS_DEBUG "-g")

# 変数 excitation_mode を設定
set(excitation_mode "sin" CACHE STRING "Excitation mode: gaussian or sin")
# set(excitation_mode "sin" CACHE STRING "Excitation mode: gaussian or sin")

# angular Frequency Number を設定
set(angular_frequency_num "566" CACHE INTERNAL "angular frequency number")

# excitation_mode に応じてサブディレクトリと実行ファイルを追加
# gaussianの場合
if(excitation_mode STREQUAL "gaussian")
    add_subdirectory(./fdtd2d_gaussian)
    add_executable(main main_2d_gaussian.c)
    target_link_libraries(main fdtd2d_lib_gaussian)

#sinの場合
elseif(excitation_mode STREQUAL "sin")
    add_executable(main main_2d_sinwave.c )
    add_subdirectory(./fdtd2d_sinwave)
    target_link_libraries(main fdtd2d_lib_sinwave)

# errorを出力
else()
    message("Invalid excitation_mode specified. Use 'gaussian' or 'sin'.")
endif()

# common sourceの付加
add_subdirectory(./common_files)
target_link_libraries(main fdtd1d_common_lib)

# # sub directoryの指定
# add_subdirectory(./fdtd1d_gaussian)
# # targer名をmainに指定する。
# add_executable(main main_1d_gaussian.c)

# sub directoryのprojectをtarget projectに付加

# コンパイルオプションの指定
target_compile_options(main PRIVATE -Wall -Wextra)
target_compile_options(main PRIVATE -O2)
target_compile_options(main PRIVATE -std=gnu99)

# ビルドの高速化
target_compile_options(main PRIVATE -pipe)

# 自動的にそのアーキテクチャにそったオプションをつける
target_compile_options(main PRIVATE -march=native)

# ループの展開を行う。
target_compile_options(main PRIVATE -funroll-loops)

# 計算をメモリ上ではなくCPUのレジスタにコピーして行うようにする
target_compile_options(main PRIVATE -fforce-addr)

# CPUの拡張命令セットを使うようにする
target_compile_options(main PRIVATE -msse -msse2 -msse3)
target_compile_options(main PRIVATE -m3dnow)
target_compile_options(main PRIVATE -mfpmath=sse)

# open mp用
target_compile_options(main PRIVATE -fopenmp)

# math.hを使用するためのライブラリのリンク
target_link_libraries(main m)

# カスタムターゲットの定義
add_custom_target(run_main
    COMMAND $<TARGET_FILE:main> ${angular_frequency_num}
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# エイリアスの定義,make runで実行できる
add_custom_target(run ALL DEPENDS run_main)
