#ifdef __APPLE__
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#endif

#include "SDL.h"
#include "sdl.h"
#include <v8.h>
#include <string>

using namespace v8;

static uv_loop_t *video_loop;

extern "C" void
init(Handle<Object> target)
{
// #ifdef __APPLE__
//   // on the mac it is necessary to create to call [NSApplication sharedApplication]
//   // before we can create a rendering window
//   objc_msgSend(objc_getClass("NSApplication"), sel_getUid("sharedApplication"));
// #endif
  sdl::ColorWrapper::Init(target);
    
  NODE_SET_METHOD(target, "init", sdl::Init);
  NODE_SET_METHOD(target, "initSubSystem", sdl::InitSubSystem);
  NODE_SET_METHOD(target, "wasInit", sdl::WasInit);

  NODE_SET_METHOD(target, "quit", sdl::Quit);
  NODE_SET_METHOD(target, "quitSubSystem", sdl::QuitSubSystem);

  NODE_SET_METHOD(target, "clearError", sdl::ClearError);
  NODE_SET_METHOD(target, "getError", sdl::GetError);
  NODE_SET_METHOD(target, "setError", sdl::SetError);

  NODE_SET_METHOD(target, "waitEvent", sdl::WaitEvent);
  NODE_SET_METHOD(target, "pollEvent", sdl::PollEvent);

  NODE_SET_METHOD(target, "numJoysticks", sdl::NumJoysticks);
  NODE_SET_METHOD(target, "joystickOpen", sdl::JoystickOpen);
  NODE_SET_METHOD(target, "joystickName", sdl::JoystickName);
  NODE_SET_METHOD(target, "joystickNumAxes", sdl::JoystickNumAxes);
  NODE_SET_METHOD(target, "joystickNumButtons", sdl::JoystickNumButtons);
  NODE_SET_METHOD(target, "joystickNumBalls", sdl::JoystickNumBalls);
  NODE_SET_METHOD(target, "joystickNumHats", sdl::JoystickNumHats);
  NODE_SET_METHOD(target, "joystickClose", sdl::JoystickClose);
  NODE_SET_METHOD(target, "joystickUpdate", sdl::JoystickUpdate);
  NODE_SET_METHOD(target, "joystickEventState", sdl::JoystickEventState);

  NODE_SET_METHOD(target, "fillRect", sdl::FillRect);
  NODE_SET_METHOD(target, "createRGBSurface", sdl::CreateRGBSurface);
  NODE_SET_METHOD(target, "blitSurface", sdl::BlitSurface);
  NODE_SET_METHOD(target, "freeSurface", sdl::FreeSurface);
  NODE_SET_METHOD(target, "setColorKey", sdl::SetColorKey);

  NODE_SET_METHOD(target, "mapRGB", sdl::MapRGB);
  NODE_SET_METHOD(target, "mapRGBA", sdl::MapRGBA);
  NODE_SET_METHOD(target, "getRGB", sdl::GetRGB);
  NODE_SET_METHOD(target, "getRGBA", sdl::GetRGBA);
  NODE_SET_METHOD(target, "setClipRect",sdl::SetClipRect);

  Local<Object> INIT = Object::New();
  target->Set(String::New("INIT"), INIT);
  INIT->Set(String::New("TIMER"), Number::New(SDL_INIT_TIMER));
  INIT->Set(String::New("AUDIO"), Number::New(SDL_INIT_AUDIO));
  INIT->Set(String::New("VIDEO"), Number::New(SDL_INIT_VIDEO));
  INIT->Set(String::New("JOYSTICK"), Number::New(SDL_INIT_JOYSTICK));
  INIT->Set(String::New("EVERYTHING"), Number::New(SDL_INIT_EVERYTHING));
  INIT->Set(String::New("NOPARACHUTE"), Number::New(SDL_INIT_NOPARACHUTE));

  Local<Object> SURFACE = Object::New();
  target->Set(String::New("SURFACE"), SURFACE);
  // SURFACE->Set(String::New("ANYFORMAT"), Number::New(SDL_ANYFORMAT));
  // SURFACE->Set(String::New("ASYNCBLIT"), Number::New(SDL_ASYNCBLIT));
  // SURFACE->Set(String::New("DOUBLEBUF"), Number::New(SDL_DOUBLEBUF));
  // SURFACE->Set(String::New("HWACCEL"), Number::New(SDL_HWACCEL));
  // SURFACE->Set(String::New("HWPALETTE"), Number::New(SDL_HWPALETTE));
  // SURFACE->Set(String::New("HWSURFACE"), Number::New(SDL_HWSURFACE));
  // SURFACE->Set(String::New("FULLSCREEN"), Number::New(SDL_FULLSCREEN));
  // SURFACE->Set(String::New("OPENGL"), Number::New(SDL_OPENGL));
  // SURFACE->Set(String::New("RESIZABLE"), Number::New(SDL_RESIZABLE));
  SURFACE->Set(String::New("RLEACCEL"), Number::New(SDL_RLEACCEL));
  // SURFACE->Set(String::New("SRCALPHA"), Number::New(SDL_SRCALPHA));
  // SURFACE->Set(String::New("SRCCOLORKEY"), Number::New(SDL_SRCCOLORKEY));
  SURFACE->Set(String::New("SWSURFACE"), Number::New(SDL_SWSURFACE));
  SURFACE->Set(String::New("PREALLOC"), Number::New(SDL_PREALLOC));

  // SDL Enumerations start:

  Local<Object> AUDIOFORMAT = Object::New();
  target->Set(String::New("AUDIOFORMAT"), AUDIOFORMAT);
  AUDIOFORMAT->Set(String::New("MASK_BITSIZE"), Number::New(SDL_AUDIO_MASK_BITSIZE));
  AUDIOFORMAT->Set(String::New("MASK_DATATYPE"), Number::New(SDL_AUDIO_MASK_DATATYPE));
  AUDIOFORMAT->Set(String::New("MASK_ENDIAN"), Number::New(SDL_AUDIO_MASK_ENDIAN));
  AUDIOFORMAT->Set(String::New("MASK_SIGNED"), Number::New(SDL_AUDIO_MASK_SIGNED));

  Local<Object> TEXTUREACCESS = Object::New();
  target->Set(String::New("TEXTUREACCESS"), TEXTUREACCESS);
  TEXTUREACCESS->Set(String::New("STATIC"), Number::New(SDL_TEXTUREACCESS_STATIC));
  TEXTUREACCESS->Set(String::New("STREAMING"), Number::New(SDL_TEXTUREACCESS_STREAMING));

  Local<Object> TTF = Object::New();
  target->Set(String::New("TTF"), TTF);
  NODE_SET_METHOD(TTF, "init", sdl::TTF::Init);
  NODE_SET_METHOD(TTF, "openFont", sdl::TTF::OpenFont);
  // NODE_SET_METHOD(TTF, "renderTextBlended", sdl::TTF::RenderTextBlended);

  Local<Object> IMG = Object::New();
  target->Set(String::New("IMG"), IMG);

  NODE_SET_METHOD(IMG, "load", sdl::IMG::Load);

  Local<Object> WM = Object::New();
  target->Set(String::New("WM"), WM);

  Local<Object> GL = Object::New();
  target->Set(String::New("GL"), GL);


  NODE_SET_METHOD(GL, "setAttribute", sdl::GL::SetAttribute);
  NODE_SET_METHOD(GL, "getAttribute", sdl::GL::GetAttribute);

  GL->Set(String::New("RED_SIZE"), Number::New(SDL_GL_RED_SIZE));
  GL->Set(String::New("GREEN_SIZE"), Number::New(SDL_GL_GREEN_SIZE));
  GL->Set(String::New("BLUE_SIZE"), Number::New(SDL_GL_BLUE_SIZE));
  GL->Set(String::New("ALPHA_SIZE"), Number::New(SDL_GL_ALPHA_SIZE));
  GL->Set(String::New("DOUBLEBUFFER"), Number::New(SDL_GL_DOUBLEBUFFER));
  GL->Set(String::New("BUFFER_SIZE"), Number::New(SDL_GL_BUFFER_SIZE));
  GL->Set(String::New("DEPTH_SIZE"), Number::New(SDL_GL_DEPTH_SIZE));
  GL->Set(String::New("STENCIL_SIZE"), Number::New(SDL_GL_STENCIL_SIZE));
  GL->Set(String::New("ACCUM_RED_SIZE"), Number::New(SDL_GL_ACCUM_RED_SIZE));
  GL->Set(String::New("ACCUM_GREEN_SIZE"), Number::New(SDL_GL_ACCUM_GREEN_SIZE));
  GL->Set(String::New("ACCUM_BLUE_SIZE"), Number::New(SDL_GL_ACCUM_BLUE_SIZE));
  GL->Set(String::New("ACCUM_ALPHA_SIZE"), Number::New(SDL_GL_ACCUM_ALPHA_SIZE));

  Local<Object> HINT = Object::New();
  target->Set(String::New("HINT"), HINT);

  HINT->Set(String::New("FRAMEBUFFER_ACCELERATION"), String::New(SDL_HINT_FRAMEBUFFER_ACCELERATION));
  HINT->Set(String::New("IDLE_TIMER_DISABLED"), String::New(SDL_HINT_IDLE_TIMER_DISABLED));
  HINT->Set(String::New("ORIENTATIONS"), String::New(SDL_HINT_ORIENTATIONS));
  HINT->Set(String::New("RENDER_DRIVER"), String::New(SDL_HINT_RENDER_DRIVER));
  HINT->Set(String::New("RENDER_OPENGL_SHADERS"), String::New(SDL_HINT_RENDER_OPENGL_SHADERS));
  HINT->Set(String::New("SCALE_QUALITY"), String::New(SDL_HINT_RENDER_SCALE_QUALITY));
  HINT->Set(String::New("RENDER_VSYNC"), String::New(SDL_HINT_RENDER_VSYNC));
}

////////////////////////////////////////////////////////////////////////////////

sdl::ColorWrapper::ColorWrapper() {
}

sdl::ColorWrapper::~ColorWrapper() {
}

void sdl::ColorWrapper::Init(Handle<Object> exports) {
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

  color_wrap_template_ = Persistent<FunctionTemplate>::New(tpl);

  color_wrap_template_->InstanceTemplate()->SetInternalFieldCount(1);
  color_wrap_template_->SetClassName(String::NewSymbol("ColorWrapper"));

  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "red", GetRed);
  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "r", GetRed);

  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "green", GetGreen);
  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "g", GetGreen);

  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "blue", GetBlue);
  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "b", GetBlue);

  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "alpha", GetAlpha);
  NODE_SET_PROTOTYPE_METHOD(color_wrap_template_, "a", GetAlpha);

  exports->Set(String::NewSymbol("Color"), color_wrap_template_->GetFunction());
}

Handle<Value> sdl::ColorWrapper::New(const Arguments& args) {
  HandleScope scope;

  ColorWrapper* wrap = new ColorWrapper();
  int red = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();
  int green = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();
  int blue = args[2]->IsUndefined() ? 0 : args[2]->Int32Value();
  int alpha = args[3]->IsUndefined() ? 0 : args[3]->Int32Value();

  if(red > 255) {
    red = 255;
  }
  else if(red < 0) {
    red = 0;
  }

  if(green > 255) {
    green = 255;
  }
  else if(green < 0) {
    green = 0;
  }

  if(blue > 255) {
    blue = 255;
  }
  else if(blue < 0) {
    blue = 0;
  }

  if(alpha > 255) {
    alpha = 255;
  }
  else if(alpha < 0) {
    alpha = 0;
  }

  wrap->color_.r = static_cast<Uint8>(red);
  wrap->color_.g = static_cast<Uint8>(green);
  wrap->color_.b = static_cast<Uint8>(blue);
  wrap->color_.a = static_cast<Uint8>(alpha);

  wrap->Wrap(args.This());
  return args.This();
}

Handle<Value> sdl::ColorWrapper::GetRed(const Arguments& args) {
  HandleScope scope;

  ColorWrapper* wrap = ObjectWrap::Unwrap<ColorWrapper>(args.This());
  return scope.Close(Number::New(wrap->color_.r));
}

Handle<Value> sdl::ColorWrapper::GetGreen(const Arguments& args) {
  HandleScope scope;

  ColorWrapper* wrap = ObjectWrap::Unwrap<ColorWrapper>(args.This());
  return scope.Close(Number::New(wrap->color_.g));
}

Handle<Value> sdl::ColorWrapper::GetBlue(const Arguments& args) {
  HandleScope scope;

  ColorWrapper* wrap = ObjectWrap::Unwrap<ColorWrapper>(args.This());
  return scope.Close(Number::New(wrap->color_.b));
}

Handle<Value> sdl::ColorWrapper::GetAlpha(const Arguments& args) {
  HandleScope scope;

  ColorWrapper* wrap = ObjectWrap::Unwrap<ColorWrapper>(args.This());
  return scope.Close(Number::New(wrap->color_.a));
}

////////////////////////////////////////////////////////////////////////////////

sdl::EventWrapper::EventWrapper() {
}

sdl::EventWrapper::~EventWrapper() {
}

void sdl::EventWrapper::Init(Handle<Object> exports) {
  event_type_to_string_[SDL_DOLLARGESTURE] = "dollarGesture";
  event_type_to_string_[SDL_DROPFILE] = "dropFile";
  event_type_to_string_[SDL_FINGERMOTION] = "fingerMotion";
  event_type_to_string_[SDL_FINGERDOWN] = "fingerDown";
  event_type_to_string_[SDL_FINGERUP] = "fingerUp";
  event_type_to_string_[SDL_KEYDOWN] = "keyDown";
  event_type_to_string_[SDL_KEYUP] = "keyUp";
  event_type_to_string_[SDL_JOYAXISMOTION] = "joyAxisMotion";
  event_type_to_string_[SDL_JOYBALLMOTION] = "joyBallMotion";
  event_type_to_string_[SDL_JOYHATMOTION] = "joyHatMotion";
  event_type_to_string_[SDL_JOYBUTTONDOWN] = "joyButtonDown";
  event_type_to_string_[SDL_JOYBUTTONUP] = "joyButtonUp";
  event_type_to_string_[SDL_MOUSEMOTION] = "mouseMotion";
  event_type_to_string_[SDL_MOUSEBUTTONDOWN] = "mouseButtonDown";
  event_type_to_string_[SDL_MOUSEBUTTONUP] = "mouseButtonUp";
  event_type_to_string_[SDL_MOUSEWHEEL] = "mouseWheel";
  event_type_to_string_[SDL_MULTIGESTURE] = "multiGesture";
  event_type_to_string_[SDL_QUIT] = "quit";
  event_type_to_string_[SDL_SYSWMEVENT] = "sysWMEvent";
  event_type_to_string_[SDL_TEXTEDITING] = "textEditing";
  event_type_to_string_[SDL_TEXTINPUT] = "textInput";
  event_type_to_string_[SDL_USEREVENT] = "userEvent";
  event_type_to_string_[SDL_WINDOWEVENT] = "windowEvent";

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

  event_wrap_template_ = Persistent<FunctionTemplate>::New(tpl);

  event_wrap_template_->InstanceTemplate()->SetInternalFieldCount(1);
  event_wrap_template_->SetClassName(String::NewSymbol("EventWrapper"));

  NODE_SET_PROTOTYPE_METHOD(event_wrap_template_, "type", GetType);
  NODE_SET_PROTOTYPE_METHOD(event_wrap_template_, "specificType", GetSpecificType);

  exports->Set(String::NewSymbol("Event"), event_wrap_template_->GetFunction());
}

Handle<Value> sdl::EventWrapper::New(const Arguments& args) {
  HandleScope scope;

  return Undefined();
}

Handle<Value> sdl::EventWrapper::GetType(const Arguments& args) {
  HandleScope scope;

  EventWrapper* wrap = ObjectWrap::Unwrap<EventWrapper>(args.This());
  std::string type_string = event_type_to_string_[wrap->event_.type];
  return scope.Close(String::New(type_string.c_str()));
}

Handle<Value> sdl::EventWrapper::GetSpecificType(const Arguments& args) {
  HandleScope scope;

  EventWrapper* wrap = ObjectWrap::Unwrap<EventWrapper>(args.This());
  return Undefined();
  // return scope.Close(String::New(window_event_to_string_[wrap->event_.type]));
}

////////////////////////////////////////////////////////////////////////////////

Handle<Value> sdl::GL::SetAttribute(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetAttribute(Number, Number)")));
  }

  int attr = args[0]->Int32Value();
  int value = args[1]->Int32Value();

  if (SDL_GL_SetAttribute((SDL_GLattr)attr, value)) return ThrowSDLException(__func__);
  return Undefined();
}

Handle<Value> sdl::GL::GetAttribute(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetAttribute(Number)")));
  }

  int attr = args[0]->Int32Value();
  int value;

  if (SDL_GL_GetAttribute((SDL_GLattr)attr, &value)) return ThrowSDLException(__func__);

  return Number::New(value);
}

Handle<Value> sdl::Init(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Init(Number)")));
  }

  if (SDL_Init(args[0]->Int32Value()) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

Handle<Value> sdl::InitSubSystem(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected InitSubSystem(Number)")));
  }

  if (SDL_InitSubSystem(args[0]->Int32Value()) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

Handle<Value> sdl::Quit(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Quit()")));
  }

  SDL_Quit();

  return Undefined();
}

Handle<Value> sdl::QuitSubSystem(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected QuitSubSystem(Number)")));
  }

  SDL_QuitSubSystem(args[0]->Int32Value());

  return Undefined();
}

Handle<Value> sdl::WasInit(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WasInit(Number)")));
  }

  return Number::New(SDL_WasInit(args[0]->Int32Value()));
}

Handle<Value> sdl::ClearError(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ClearError()")));
  }

  SDL_ClearError();

  return Undefined();
}

Handle<Value> sdl::GetError(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetError()")));
  }

  return String::New(SDL_GetError());
}

Handle<Value> sdl::SetError(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsString())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetError(String)")));
  }

  String::Utf8Value message(args[1]);

  SDL_SetError(*message);

  return Undefined();
}

static Handle<Value> sdl::WaitEvent(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsFunction())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WaitEvent(Function)")));
  }

  SDL_Event e;
  int err = SDL_WaitEvent(&e);
  if(0 == err) {
    std::string err = "WaitEvent failed: ";
    err += SDL_GetError();
    return ThrowException(MakeSDLException(err.c_str()));
  }
  Handle<Value> argv[1];
  argv[0] = sdl::SDLEventToJavascriptObject(e);
  Handle<Function>::Cast(args[0])->Call(Context::GetCurrent()->Global(), 1, argv);
  return Undefined();
}

static Handle<Value> sdl::WaitEventTimeout(const Arguments& args) {
  HandleScope scope;

  if(!(args.Length() == 2 && args[0]->IsFunction() && args[1]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WaitEventTimeout(Function, Number)")));
  }

  SDL_Event e;
  int timeout = args[1]->Int32Value();
  int err = SDL_WaitEventTimeout(&e, timeout);
  if(0 == err) {
    std::string err = "WaitEventTimeout failed: ";
    err += SDL_GetError();
    return ThrowException(MakeSDLException(err.c_str()));
  }
  Handle<Value> argv[1];
  argv[0] = sdl::SDLEventToJavascriptObject(e);
  Handle<Function>::Cast(args[0])->Call(Context::GetCurrent()->Global(), 1, argv);
  return Undefined();
}

Handle<Value> sdl::PollEvent(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected PollEvent()")));
  }

  SDL_Event event;
  if (!SDL_PollEvent(&event)) {
    return Undefined();
  }

  Local<Object> evt = SDLEventToJavascriptObject(event);
  return scope.Close(evt);
}

static Handle<Value> sdl::NumJoysticks(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected NumJoysticks()")));
  }

  return Number::New(SDL_NumJoysticks());
}

static Handle<Value> sdl::JoystickOpen(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickOpen(Number)")));
  }

  SDL_Joystick* joystick = SDL_JoystickOpen(args[0]->Int32Value());
  if (!joystick) return ThrowSDLException(__func__);
  return scope.Close(WrapJoystick(joystick));
}

static Handle<Value> sdl::JoystickName(const Arguments& args) {
  return Undefined();
  // HandleScope scope;

  // if (!(args.Length() == 1 && args[0]->IsNumber())) {
  //   return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickName(Number)")));
  // }

  // return String::New(SDL_JoystickName(UnwrapJoystick(args[0])));
}

static Handle<Value> sdl::JoystickNumAxes(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumAxes(Joystick)")));
  }

  return Number::New(SDL_JoystickNumAxes(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickNumButtons(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumButtons(Joystick)")));
  }

  return Number::New(SDL_JoystickNumButtons(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickNumBalls(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumBalls(Joystick)")));
  }

  return Number::New(SDL_JoystickNumBalls(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickNumHats(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickNumHats(Joystick)")));
  }

  return Number::New(SDL_JoystickNumHats(UnwrapJoystick(args[0]->ToObject())));
}

static Handle<Value> sdl::JoystickClose(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickClose(Joystick)")));
  }

  SDL_JoystickClose(UnwrapJoystick(args[0]->ToObject()));

  return Undefined();
}

static Handle<Value> sdl::JoystickUpdate(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickUpdate()")));
  }

  SDL_JoystickUpdate();
  return Undefined();
}

static Handle<Value> sdl::JoystickEventState(const Arguments& args) {
  HandleScope scope;

  int state;
  if (args.Length() == 0) {
    state = SDL_QUERY;
  } else {
    if (!(args.Length() == 1 && args[0]->IsBoolean())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickEventState([Boolean])")));
    }
    state = args[0]->BooleanValue() ? SDL_ENABLE : SDL_IGNORE;
  }
  return Boolean::New(SDL_JoystickEventState(state));
}

static Handle<Value> sdl::FillRect(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 3
      && args[0]->IsObject()
      && (args[1]->IsObject() || args[1]->IsNull())
      && args[2]->IsNumber()
  )) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected FillRect(Surface, Rect, Number)")));
  }

  SDL_Surface* surface = UnwrapSurface(args[0]->ToObject());
  SDL_Rect* rect;
  if (args[1]->IsNull()) {
    rect = NULL;
  } else if (args[1]->IsArray()) {
    SDL_Rect r;
    Handle<Object> arr = args[1]->ToObject();
    r.x = arr->Get(String::New("0"))->Int32Value();
    r.y = arr->Get(String::New("1"))->Int32Value();
    r.w = arr->Get(String::New("2"))->Int32Value();
    r.h = arr->Get(String::New("3"))->Int32Value();
    rect = &r;
  } else {
    rect = UnwrapRect(args[1]->ToObject());
  }
  int color = args[2]->Int32Value();

  if (SDL_FillRect (surface, rect, color) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

static Handle<Value> sdl::CreateRGBSurface(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected CreateRGBSurface(Number, Number, Number)")));
  }

  int flags = args[0]->Int32Value();
  int width = args[1]->Int32Value();
  int height = args[2]->Int32Value();

  SDL_Surface *surface;
  int rmask, gmask, bmask, amask;

  /* SDL interprets each pixel as a 32-bit number, so our masks must depend
     on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  surface = SDL_CreateRGBSurface(flags, width, height, 32, rmask, gmask, bmask, amask);
  if (surface == NULL) return ThrowSDLException(__func__);
  return scope.Close(WrapSurface(surface));
}

static Handle<Value> sdl::BlitSurface(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 4
        && args[0]->IsObject()
        && (args[1]->IsObject() || args[1]->IsNull())
        && args[2]->IsObject()
        && (args[3]->IsObject() || args[3]->IsNull())
  )) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BlitSurface(Surface, Rect, Surface, Rect)")));
  }

  SDL_Surface* src = UnwrapSurface(args[0]->ToObject());
  SDL_Surface* dst = UnwrapSurface(args[2]->ToObject());

  SDL_Rect* srcrect;
  if (args[1]->IsNull()) {
    srcrect = NULL;
  } else if (args[1]->IsArray()) {
    Handle<Object> arr1 = args[1]->ToObject();
    srcrect = new SDL_Rect();
    srcrect->x = arr1->Get(String::New("0"))->Int32Value();
    srcrect->y = arr1->Get(String::New("1"))->Int32Value();
    srcrect->w = arr1->Get(String::New("2"))->Int32Value();
    srcrect->h = arr1->Get(String::New("3"))->Int32Value();
  } else {
    srcrect = UnwrapRect(args[1]->ToObject());
  }

  SDL_Rect* dstrect;
  if (args[3]->IsNull()) {
    dstrect = NULL;
  } else if (args[3]->IsArray()) {
    Handle<Object> arr2 = args[3]->ToObject();
    dstrect = new SDL_Rect();
    dstrect->x = arr2->Get(String::New("0"))->Int32Value();
    dstrect->y = arr2->Get(String::New("1"))->Int32Value();
    dstrect->w = arr2->Get(String::New("2"))->Int32Value();
    dstrect->h = arr2->Get(String::New("3"))->Int32Value();
  } else {
    dstrect = UnwrapRect(args[3]->ToObject());
  }

//  if (srcrect) printf("srcrect = {x: %d, y: %d, w: %d, h: %d}\n", srcrect->x, srcrect->y, srcrect->w, srcrect->h);
//  else printf("srcrect = null\n");
//  if (dstrect) printf("dstrect = {x: %d, y: %d, w: %d, h: %d}\n", dstrect->x, dstrect->y, dstrect->w, dstrect->h);
//  else printf("dstrect = null\n");


  if (SDL_BlitSurface(src, srcrect, dst, dstrect) < 0) return ThrowSDLException(__func__);
  return Undefined();
}

static Handle<Value> sdl::FreeSurface(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected FreeSurface(Surface)")));
  }

  // TODO: find a way to do this automatically by using GC hooks.  This is dangerous in JS land
  SDL_FreeSurface(UnwrapSurface(args[0]->ToObject()));
  args[0]->ToObject()->Set(String::New("DEAD"), Boolean::New(true));

  return Undefined();
}

static Handle<Value> sdl::SetColorKey(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 3 && args[0]->IsObject() && args[1]->IsNumber() && args[2]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetColorKey(Surface, Number, Number)")));
  }

  SDL_Surface* surface = UnwrapSurface(args[0]->ToObject());
  int flag = args[1]->Int32Value();
  int key = args[2]->Int32Value();

  if (SDL_SetColorKey(surface, flag, key) < 0) return ThrowSDLException(__func__);

  return Undefined();

}

static Handle<Value> sdl::MapRGB(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 4 && args[0]->IsObject() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected MapRGB(PixelFormat, Number, Number, Number)")));
  }

  SDL_PixelFormat* fmt = UnwrapPixelFormat(args[0]->ToObject());
  int r = args[1]->Int32Value();
  int g = args[2]->Int32Value();
  int b = args[3]->Int32Value();

  return Number::New(SDL_MapRGB(fmt, r, g, b));
}

static Handle<Value> sdl::MapRGBA(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 5 && args[0]->IsObject() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber() && args[4]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected MapRGBA(PixelFormat, Number, Number, Number, Number)")));
  }

  SDL_PixelFormat* fmt = UnwrapPixelFormat(args[0]->ToObject());
  int r = args[1]->Int32Value();
  int g = args[2]->Int32Value();
  int b = args[3]->Int32Value();
  int a = args[4]->Int32Value();

  return Number::New(SDL_MapRGBA(fmt, r, g, b, a));
}

static Handle<Value> sdl::GetRGB(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetRGB(Number, PixelFormat)")));
  }

  int pixel = args[0]->Int32Value();
  SDL_PixelFormat* fmt = UnwrapPixelFormat(args[1]->ToObject());
  ::Uint8 r, g, b;

  SDL_GetRGB(pixel, fmt, &r, &g, &b);

  Local<Object> rgb = Object::New();
  rgb->Set(String::New("r"), Number::New(r));
  rgb->Set(String::New("g"), Number::New(g));
  rgb->Set(String::New("b"), Number::New(b));

  return scope.Close(rgb);
}

static Handle<Value> sdl::GetRGBA(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetRGBA(Number, PixelFormat)")));
  }

  int pixel = args[0]->Int32Value();
  SDL_PixelFormat* fmt = UnwrapPixelFormat(args[1]->ToObject());
  ::Uint8 r, g, b, a;

  SDL_GetRGBA(pixel, fmt, &r, &g, &b, &a);

  Local<Object> rgba = Object::New();
  rgba->Set(String::New("r"), Number::New(r));
  rgba->Set(String::New("g"), Number::New(g));
  rgba->Set(String::New("b"), Number::New(b));
  rgba->Set(String::New("a"), Number::New(a));

  return scope.Close(rgba);
}


static Handle<Value> sdl::SetClipRect(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetClipRect(SDL_Surface, SDL_Rect)")));
  }    
  
  SDL_Surface* surface = UnwrapSurface(args[0]->ToObject());
  SDL_Rect* rect;
  if (args[1]->IsNull()) {
    rect = NULL;
  } else if (args[1]->IsArray()) {
    SDL_Rect r;
    Handle<Object> arr = args[1]->ToObject();
    r.x = arr->Get(String::New("0"))->Int32Value();
    r.y = arr->Get(String::New("1"))->Int32Value();
    r.w = arr->Get(String::New("2"))->Int32Value();
    r.h = arr->Get(String::New("3"))->Int32Value();
    rect = &r;
  } else {
    rect = UnwrapRect(args[1]->ToObject());
  }
  if (SDL_SetClipRect (surface, rect ) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

static Handle<Value> sdl::TTF::Init(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::Init()")));
  }

  if (TTF_Init() < 0) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("TTF::Init: "),
      String::New(TTF_GetError())
    )));
  }

  return Undefined();
}

static Handle<Value> sdl::TTF::OpenFont(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 2 && args[0]->IsString() && args[1]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::OpenFont(String, Number)")));
  }

  String::Utf8Value file(args[0]);
  int ptsize = (args[1]->Int32Value());

  TTF_Font* font = TTF_OpenFont(*file, ptsize);
  if (font == NULL) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("TTF::OpenFont: "),
      String::New(TTF_GetError())
    )));
  }
  return scope.Close(WrapFont(font));
}

// TODO: Rewrite for SDL2.
// static Handle<Value> sdl::TTF::RenderTextBlended(const Arguments& args) {
//   HandleScope scope;

//   if (!(args.Length() == 3 && args[0]->IsObject() && args[1]->IsString() && args[2]->IsNumber())) {
//     return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::RenderTextBlended(Font, String, Number)")));
//   }

//   SDL_PixelFormat* vfmt = SDL_GetVideoInfo()->vfmt;
//   TTF_Font* font = UnwrapFont(args[0]->ToObject());
//   String::Utf8Value text(args[1]);
//   int colorCode = args[2]->Int32Value();

//   Uint8 r, g, b;
//   SDL_GetRGB(colorCode, vfmt, &r, &g, &b);

//   SDL_Color color;
//   color.r = r;
//   color.g = g;
//   color.b = b;

//   SDL_Surface *resulting_text;
//   resulting_text = TTF_RenderText_Blended(font, *text, color);
//   if (!resulting_text) {
//     return ThrowException(Exception::Error(String::Concat(
//       String::New("TTF::RenderTextBlended: "),
//       String::New(TTF_GetError())
//     )));
//   }
//   return scope.Close(WrapSurface(resulting_text));
// }

// TODO: make an async version so this can be used in loops or parallel load images
static Handle<Value> sdl::IMG::Load(const Arguments& args) {
  HandleScope scope;

  if (!(args.Length() == 1 && args[0]->IsString())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected IMG::Load(String)")));
  }

  String::Utf8Value file(args[0]);

  SDL_Surface *image;
  image=IMG_Load(*file);
  if(!image) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("IMG::Load: "),
      String::New(IMG_GetError())
    )));
  }

  return scope.Close(WrapSurface(image));
}
