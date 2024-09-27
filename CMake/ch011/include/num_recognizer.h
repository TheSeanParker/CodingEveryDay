#ifndef NUM_RECOGNIZER_H
#define NUM_RECOGNIZER_H

#include "num_recognizer_export.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef num_recognizer_EXPORTS
struct Recognizer;
#else
typedef struct _Recognizer Recognizer;
#endif

//! @brief 初始化手写数字识别库
//! @return void
NUM_RECOGNIZER_EXPORT void num_recognizer_init();

//! @brief 创建识别器
//! @param model_path 模型文件路径
//! @param[out] out_recognizer 接受初始化的识别器指针的指针
NUM_RECOGNIZER_EXPORT void num_recognizer_create(const char *model_path,
                                                 Recognizer **out_recognizer);

//! @brief 析构识别器
//! @param recognizer 识别器的指针
NUM_RECOGNIZER_EXPORT void num_recognizer_delete(Recognizer *recognizer);

//! @brief 识别图片数据中的手写数字
//! @param recognizer 识别器的指针
//! @param input_image
//! 模型接受的输入图片数据（28x28的float数值数组，0代表白色，1代表黑色）
//! @param result 接受识别结果的数值的指针
//! @return 错误值，成功返回0
NUM_RECOGNIZER_EXPORT int num_recognizer_recognize(Recognizer *recognizer,
                                                   float *input_image,
                                                   int *result);

//! @brief 识别PNG图片中的手写数字
//! @param recognizer 识别器的指针
//! @param png_path PNG图片文件路径
//! @param result 接受识别结果的数值的指针
//! @return 错误值，成功返回0
NUM_RECOGNIZER_EXPORT int num_recognizer_recognize_png(Recognizer *recognizer,
                                                       const char *png_path,
                                                       int *result);
#ifdef __cplusplus
} // extern "C"
#endif

#endif // NUM_RECOGNIZER_H