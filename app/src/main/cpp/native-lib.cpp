#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_dfanr_androidndkexample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    #if defined(__arm__)
        #if defined(__ARM_ARCH_7A__)
            #if defined(__ARM_NEON__)
                #if defined(__ARM_PCS_VFP)
                    #define ABI "armeabi-v7a/NEON (hard-float)"
                #else
                    #define ABI "armeabi-v7a/NEON"
                #endif
            #else
                #if defined(__ARM_PCS_VFP)
                    #define ABI "armeabi-v7a (hard-float)"
                #else
                    #define ABI "armeabi-v7a"
                #endif
            #endif
        #else
            #define ABI "armeabi"
        #endif
    #elif defined(__i386__)
        #define ABI "x86"
    #elif defined(__x86_64__)
        #define ABI "x86_64"
    #elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
        #define ABI "mips64"
    #elif defined(__mips__)
        #define ABI "mips"
    #elif defined(__aarch64__)
        #define ABI "arm64-v8a"
    #else
        #define ABI "unknown"
    #endif

    // c++支持类似`std::string hello = "str1" "str2" "str3";`的写法，等价于`std::string hello = "str1str2str3";`
    // 宏定义ABI会被替换为"arm64-v8a"（包含双引号）
    std::string hello = "Hello from C++, current ABI is " ABI ". ";
    return env->NewStringUTF(hello.c_str());
}