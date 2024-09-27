#include <onnxruntime_cxx_api.h>

int main() {
    Ort::Env env;
    Ort::Session session(env, ORT_TSTR(""), Ort::SessionOptions(nullptr));
    return 0;
}