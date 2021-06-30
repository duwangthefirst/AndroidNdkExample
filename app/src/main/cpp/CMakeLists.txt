cmake_minimum_required(VERSION 3.10.2)
project("androidndkexample")

# 设置编译标识位
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror")
# 下面的"-u ANativeActivity_onCreate"标识用于解决ANativeActivity_onCreate()无法导出的bug, 详见https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# 将native_app_glue编译为静态库（该库使得Application可以管理NativeActivity的生命周期事件和触摸输入）
add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# 编译app的共享库
add_library(native-lib SHARED native-lib.cpp )

# 查找NDK预编译的库
find_library(android-lib android)
find_library(log-lib log)
find_library(egl-lib EGL)
find_library(gles-lib GLESv1_CM)

target_include_directories(native-lib PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)

target_link_libraries(
        native-lib
        native_app_glue
        ${android-lib}
        ${log-lib}
        ${egl-lib}
        ${gles-lib}
)