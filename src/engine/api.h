#ifndef API_H
#define API_H

#include <string>

#include <napi.h>
#include "engine.h"

class EngineApi : public Napi::ObjectWrap<EngineApi> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports); //Init function for setting the export key to JS

    EngineApi(const Napi::CallbackInfo& info); //Constructor to initialise

    Napi::Value getFullBoard(const Napi::CallbackInfo &info);

    Napi::Value getState(const Napi::CallbackInfo &info);

    Napi::Value isGameOver(const Napi::CallbackInfo &info);

    Napi::Value playMove(const Napi::CallbackInfo &info);

    Napi::Value getMines(const Napi::CallbackInfo &info);

  private:
    static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
    Minesweeper *game_; // Internal instance of game

};

#endif
