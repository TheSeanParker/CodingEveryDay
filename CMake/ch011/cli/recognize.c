#include <num_recognizer.h>
#include <stdio.h>

//! @brief 主函数
//!
//!   命令行参数应有3个：
//!   1. 命令行程序本身的文件名，即recognize；
//!   2. 模型文件路径；
//!   3. 将要识别的PNG图片文件路径。
//!
//!   例如：recognize models/mnist.onnx 2.png
//!
//! @param argc 命令行参数个数
//! @param argv 命令行参数值数组
//! @return 返回码，0表示正常退出
int main(int argc, const char **argv) {
    // 检查命令行参数个数是否为3个
    if (argc != 3) {
        printf("Usage: recognize mnist.onnx 3.png\n");
        return -1; // 返回错误码-1
    }

    int ret = 0;            // 返回码
    int result = -1;        // 识别结果
    Recognizer *recognizer; // 识别器指针

    num_recognizer_init(); // 初始化识别器

    // 使用模型文件创建识别器，argv[1]即模型文件路径
    num_recognizer_create(argv[1], &recognizer);

    // 识别图片文件中的手写数字，argv[2]即图片文件路径
    if (ret = num_recognizer_recognize_png(recognizer, argv[2], &result)) {
        // 返回值非0，识别过程发生错误
        printf("Failed to recognize\n");
        goto exit_main;
    }

    printf("%d\n", result); // 输出识别结果

exit_main:
    num_recognizer_delete(recognizer); // 析构识别器
    return ret;                        // 返回正常退出的返回码0
}