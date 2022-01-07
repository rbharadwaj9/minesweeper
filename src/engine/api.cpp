#include "api.h"

Napi::FunctionReference EngineApi::constructor;

Napi::Object EngineApi::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "EngineApi", {
            InstanceMethod("getFullBoard", &EngineApi::getFullBoard),
            InstanceMethod("getState", &EngineApi::getState),
            InstanceMethod("isGameOver", &EngineApi::isGameOver),
            });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set(
        Napi::String::New(env, "EngineApi"),
        func
    );
    return exports;
}

EngineApi::EngineApi(const Napi::CallbackInfo &info) : Napi::ObjectWrap<EngineApi>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    if (length != 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    int rows = (int) info[0].ToNumber();
    int cols = (int) info[1].ToNumber();
    int num_mines = (int) info[2].ToNumber();
    this->game_ = new Minesweeper(rows, cols, num_mines);
}

Napi::Value EngineApi::getFullBoard(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string result = "Hello";

    return Napi::String::New(env, result);
}

Napi::Value EngineApi::getState(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    std::string result = "Hello";

    return Napi::String::New(env, result);
}

Napi::Value EngineApi::isGameOver(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    bool result = this->game_->is_game_over();

    return Napi::Boolean::New(env, result);
}
