#include <napi.h>
#include "engine/api.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return EngineApi::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
