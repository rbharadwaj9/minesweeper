#include <sstream>
#include "api.h"

Napi::FunctionReference EngineApi::constructor;

Napi::Object EngineApi::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "EngineApi", {
      InstanceMethod("getFullBoard", &EngineApi::getFullBoard),
      InstanceMethod("getState", &EngineApi::getState),
      InstanceMethod("isGameOver", &EngineApi::isGameOver),
      InstanceMethod("playMove", &EngineApi::playMove),
      InstanceMethod("getMines", &EngineApi::getMines),
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
  if (length < 3 || length > 4) {
    Napi::TypeError::New(env, "Num Args Incorrect").ThrowAsJavaScriptException();
  }
  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }
  if (length == 4 && !info[3].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  int rows = (int) info[0].ToNumber();
  int cols = (int) info[1].ToNumber();
  int num_mines = (int) info[2].ToNumber();
  int seed = (length == 4) ? (int) info[3].ToNumber() : 0;
  this->game_ = new Minesweeper(rows, cols, num_mines, seed);
}

Napi::Value EngineApi::getFullBoard(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string result = this->game_->get_board_debug();
  return Napi::String::New(env, result);
}

Napi::Value EngineApi::getState(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string result = this->game_->get_user_board();
  return Napi::String::New(env, result);
}

Napi::Value EngineApi::isGameOver(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  bool result = this->game_->is_game_over();
  return Napi::Boolean::New(env, result);
}

Napi::Value EngineApi::playMove(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  int row = (int) info[0].ToNumber();
  int col = (int) info[1].ToNumber();
  const Coordinate c(row, col);

  bool result = this->game_->play_move(c);
  return Napi::Boolean::New(env, result);
}

Napi::Value EngineApi::getMines(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string result = this->game_->get_mines();
  return Napi::String::New(env, result);
}
