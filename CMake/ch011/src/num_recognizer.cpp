#include "num_recognizer.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <onnxruntime_cxx_api.h>
#include <png.h>

#ifdef _WIN32
// 在Windows操作系统中，我们需要使用Windows API来帮助我们完成const char*到const
// wchar_t*的编码转换。因此需要引用Windows.h。
#include <Windows.h>
#endif

static const char *INPUT_NAMES[] = {"Input3"}; // 模型输入参数名
static const char *OUTPUT_NAMES[] = {"Plus214_Output_0"}; // 模型输出参数名
static constexpr int64_t INPUT_WIDTH = 28;  // 模型输入图片宽度
static constexpr int64_t INPUT_HEIGHT = 28; // 模型输入图片高度
static const std::array<int64_t, 4> input_shape{
    1, 1, INPUT_WIDTH, INPUT_HEIGHT}; // 输入数据的形状（各维度大小）
static const std::array<int64_t, 2> output_shape{
    1, 10}; // 输出数据的形状（各维度大小）

static Ort::Env env{nullptr};                // onnxruntime环境
static Ort::MemoryInfo memory_info{nullptr}; // onnxruntime内存信息

//! @brief 手写数字识别类
struct Recognizer {
    //! @brief onnxruntime会话
    Ort::Session session;
};

//! @brief 将byte类型的颜色值转换为模型接受的二值化后的float类型数值
//! @param b byte类型的颜色值
//! @return 模型接受的二值化后的float类型值，0代表白色，1代表黑色。
static float byte2float(png_byte b) { return b < 128 ? 1 : 0; }

//! @brief 获取png图片指定像素的二值化后的float类型颜色值
//! @param x 像素横坐标
//! @param y 像素纵坐标
//! @param png_width 图片宽度
//! @param png_height 图片高度
//! @param color_type 图片颜色类型
//! @param png_data 图片数据
//! @return 对应像素的二值化后的float类型颜色值
static float get_float_color_in_png(unsigned int x, unsigned int y,
                                    png_uint_32 png_width,
                                    png_uint_32 png_height, png_byte color_type,
                                    png_bytepp png_data) {
    if (x >= png_width || x < 0)
        return 0;
    if (y >= png_height || y < 0)
        return 0;

    switch (color_type) {
    case PNG_COLOR_TYPE_RGB: {
        auto p = png_data[y] + x * 3;
        return byte2float((p[0] + p[1] + p[2]) / 3);
    } break;
    case PNG_COLOR_TYPE_RGBA: {
        auto p = png_data[y] + x * 4;
        return byte2float((p[0] + p[1] + p[2]) * p[3] / 3);
    } break;
    default:
        return 0;
    }
};

extern "C" {
void num_recognizer_init() {
    env = Ort::Env{static_cast<const OrtThreadingOptions *>(nullptr)};
    memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
}

void num_recognizer_create(const char *model_path,
                           Recognizer **out_recognizer) {
    Ort::Session session{nullptr};
#if _WIN32
    // Windows中，onnxruntime的Session接受模型文件路径时需使用const
    // wchar_t*，即宽字符串。因此在这里做一下转换。
    wchar_t wpath[256];
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, model_path, -1, wpath, 256);
    session = Ort::Session(env, wpath, Ort::SessionOptions(nullptr));
#else
    session = Ort::Session(env, model_path, Ort::SessionOptions(nullptr));
#endif
    *out_recognizer = new Recognizer{std::move(session)};
}

void num_recognizer_delete(Recognizer *recognizer) { delete recognizer; }

int num_recognizer_recognize(Recognizer *recognizer, float *input_image,
                             int *result) {

    std::array<float, 10> results{};

    auto input_tensor = Ort::Value::CreateTensor<float>(
        memory_info, input_image, INPUT_WIDTH * INPUT_HEIGHT,
        input_shape.data(), input_shape.size());

    auto output_tensor = Ort::Value::CreateTensor<float>(
        memory_info, results.data(), results.size(), output_shape.data(),
        output_shape.size());

    recognizer->session.Run(Ort::RunOptions{nullptr}, INPUT_NAMES,
                            &input_tensor, 1, OUTPUT_NAMES, &output_tensor, 1);

    *result = static_cast<int>(std::distance(
        results.begin(), std::max_element(results.begin(), results.end())));

    return 0;
}

int num_recognizer_recognize_png(Recognizer *recognizer, const char *png_path,
                                 int *result) {
    int ret = 0;
    std::array<float, INPUT_WIDTH * INPUT_HEIGHT> input_image;
    FILE *fp;
    unsigned char header[8];
    png_structp png_ptr;
    png_infop info_ptr;
    png_uint_32 png_width, png_height;
    png_byte color_type;
    png_bytep *png_data;

    // 打开PNG图片文件
    fp = fopen(png_path, "rb");
    if (!fp) {
        ret = -2;
        goto exit3;
    }

    // 读取PNG图片文件头
    fread(header, 1, 8, fp);
    // 验证文件头确实是PNG格式的文件头
    if (png_sig_cmp(reinterpret_cast<unsigned char *>(header), 0, 8)) {
        ret = -3;
        goto exit2;
    }

    // 创建PNG指针数据结构
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
                                     nullptr);
    if (!png_ptr) {
        ret = -4;
        goto exit2;
    }

    // 创建PNG信息指针数据结构
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        ret = -5;
        goto exit2;
    }

    // 设置跳转以处理异常
    if (setjmp(png_jmpbuf(png_ptr))) {
        ret = -6;
        goto exit2;
    }

    // 初始化PNG文件
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    // 读取PNG信息
    png_read_info(png_ptr, info_ptr);
    png_width = png_get_image_width(png_ptr, info_ptr);   // PNG图片宽度
    png_height = png_get_image_height(png_ptr, info_ptr); // PNG图片高度
    color_type = png_get_color_type(png_ptr, info_ptr); // PNG图片颜色类型

    // 设置跳转以处理异常
    if (setjmp(png_jmpbuf(png_ptr))) {
        ret = -7;
        goto exit2;
    }

    // 读取PNG的数据
    png_data = (png_bytep *)malloc(sizeof(png_bytep) * png_height);
    for (unsigned int y = 0; y < png_height; ++y) {
        png_data[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, png_data);

    // 将PNG图片重新采样，缩放到模型接受的输入图片大小
    for (unsigned int y = 0; y < INPUT_HEIGHT; ++y) {
        for (unsigned int x = 0; x < INPUT_WIDTH; ++x) {
            float res = 0;
            int n = 0;
            for (unsigned int png_y = y * png_height / INPUT_HEIGHT;
                 png_y < (y + 1) * png_height / INPUT_HEIGHT; ++png_y) {
                for (unsigned int png_x = x * png_width / INPUT_WIDTH;
                     png_x < (x + 1) * png_width / INPUT_WIDTH; ++png_x) {
                    res += get_float_color_in_png(png_x, png_y, png_width,
                                                  png_height, color_type,
                                                  png_data);
                    ++n;
                }
            }
            input_image[y * INPUT_HEIGHT + x] = res / n;
        }
    }

    // 识别图片数据中的手写数字
    ret = num_recognizer_recognize(recognizer, input_image.data(), result);

exit1:
    // 释放存放PNG图片数据的内存空间
    for (unsigned int y = 0; y < png_height; ++y) {
        free(png_data[y]);
    }
    free(png_data);

exit2:
    // 关闭文件
    fclose(fp);

exit3:
    return ret;
}
}