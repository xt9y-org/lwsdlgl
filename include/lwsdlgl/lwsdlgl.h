#ifndef LWSDLGL_LWSDLGL_H
#define LWSDLGL_LWSDLGL_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    LWSDLGL_VERSION_MAJOR = 0,
    LWSDLGL_VERSION_MINOR = 1,
    LWSDLGL_VERSION_PATCH = 0,
    LWSDLGL_ABI_VERSION = 1
};

#define LWSDLGL_VERSION_STRING "0.1.0"

typedef struct LwsdlglSystemAPI {
    bool (*init)(SDL_InitFlags flags);
    bool (*initSubSystem)(SDL_InitFlags flags);
    void (*quitSubSystem)(SDL_InitFlags flags);
    SDL_InitFlags (*wasInit)(SDL_InitFlags flags);
    void (*quit)(void);
    const char *(*getError)(void);
    bool (*clearError)(void);
    int (*getVersion)(void);
    const char *(*getRevision)(void);
    const char *(*getPlatform)(void);
    Uint64 (*getTicks)(void);
    Uint64 (*getTicksNS)(void);
    Uint64 (*getPerformanceCounter)(void);
    Uint64 (*getPerformanceFrequency)(void);
    void (*delay)(Uint32 ms);
    void (*delayNS)(Uint64 ns);
    void (*free)(void *memory);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglSystemAPI;

typedef struct LwsdlglDisplayAPI {
    SDL_DisplayID *(*getDisplays)(int *count);
    SDL_DisplayID (*getPrimaryDisplay)(void);
    const char *(*getName)(SDL_DisplayID display);
    bool (*getBounds)(SDL_DisplayID display, SDL_Rect *rect);
    bool (*getUsableBounds)(SDL_DisplayID display, SDL_Rect *rect);
    float (*getContentScale)(SDL_DisplayID display);
    const SDL_DisplayMode *(*getDesktopMode)(SDL_DisplayID display);
    const SDL_DisplayMode *(*getCurrentMode)(SDL_DisplayID display);
    SDL_DisplayMode **(*getFullscreenModes)(SDL_DisplayID display, int *count);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglDisplayAPI;

typedef struct LwsdlglWindowAPI {
    SDL_Window *(*create)(const char *title, int width, int height, SDL_WindowFlags flags);
    SDL_Window *(*createWithProperties)(SDL_PropertiesID props);
    void (*destroy)(SDL_Window *window);
    SDL_WindowID (*getID)(SDL_Window *window);
    SDL_Window *(*getFromID)(SDL_WindowID id);
    SDL_WindowFlags (*getFlags)(SDL_Window *window);
    SDL_PropertiesID (*getProperties)(SDL_Window *window);
    bool (*setTitle)(SDL_Window *window, const char *title);
    const char *(*getTitle)(SDL_Window *window);
    bool (*setSize)(SDL_Window *window, int width, int height);
    bool (*getSize)(SDL_Window *window, int *width, int *height);
    bool (*getSizeInPixels)(SDL_Window *window, int *width, int *height);
    bool (*setPosition)(SDL_Window *window, int x, int y);
    bool (*getPosition)(SDL_Window *window, int *x, int *y);
    bool (*setMinimumSize)(SDL_Window *window, int width, int height);
    bool (*getMinimumSize)(SDL_Window *window, int *width, int *height);
    bool (*setMaximumSize)(SDL_Window *window, int width, int height);
    bool (*getMaximumSize)(SDL_Window *window, int *width, int *height);
    bool (*setResizable)(SDL_Window *window, bool value);
    bool (*setBordered)(SDL_Window *window, bool value);
    bool (*setAlwaysOnTop)(SDL_Window *window, bool value);
    bool (*setFocusable)(SDL_Window *window, bool value);
    bool (*show)(SDL_Window *window);
    bool (*hide)(SDL_Window *window);
    bool (*raise)(SDL_Window *window);
    bool (*maximize)(SDL_Window *window);
    bool (*minimize)(SDL_Window *window);
    bool (*restore)(SDL_Window *window);
    bool (*setFullscreen)(SDL_Window *window, bool value);
    bool (*setFullscreenMode)(SDL_Window *window, const SDL_DisplayMode *mode);
    const SDL_DisplayMode *(*getFullscreenMode)(SDL_Window *window);
    bool (*sync)(SDL_Window *window);
    float (*getPixelDensity)(SDL_Window *window);
    float (*getDisplayScale)(SDL_Window *window);
    SDL_DisplayID (*getDisplay)(SDL_Window *window);
    bool (*setOpacity)(SDL_Window *window, float opacity);
    float (*getOpacity)(SDL_Window *window);
    SDL_PixelFormat (*getPixelFormat)(SDL_Window *window);
    bool (*setMouseGrab)(SDL_Window *window, bool value);
    bool (*getMouseGrab)(SDL_Window *window);
    bool (*setKeyboardGrab)(SDL_Window *window, bool value);
    bool (*getKeyboardGrab)(SDL_Window *window);
    bool (*setRelativeMouseMode)(SDL_Window *window, bool value);
    bool (*getRelativeMouseMode)(SDL_Window *window);
    bool (*setMouseRect)(SDL_Window *window, const SDL_Rect *rect);
    const SDL_Rect *(*getMouseRect)(SDL_Window *window);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglWindowAPI;

typedef struct LwsdlglEventsAPI {
    void (*pump)(void);
    int (*peep)(SDL_Event *events, int count, SDL_EventAction action, Uint32 minType, Uint32 maxType);
    bool (*has)(Uint32 type);
    bool (*hasRange)(Uint32 minType, Uint32 maxType);
    void (*flush)(Uint32 type);
    void (*flushRange)(Uint32 minType, Uint32 maxType);
    bool (*poll)(SDL_Event *event);
    bool (*wait)(SDL_Event *event);
    bool (*waitTimeout)(SDL_Event *event, Sint32 timeoutMS);
    bool (*push)(SDL_Event *event);
    void (*setFilter)(SDL_EventFilter filter, void *userdata);
    bool (*getFilter)(SDL_EventFilter *filter, void **userdata);
    bool (*addWatch)(SDL_EventFilter filter, void *userdata);
    void (*removeWatch)(SDL_EventFilter filter, void *userdata);
    void (*filter)(SDL_EventFilter filter, void *userdata);
    bool (*enabled)(Uint32 type);
    void (*setEnabled)(Uint32 type, bool enabled);
    Uint32 (*registerTypes)(int count);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglEventsAPI;

typedef struct LwsdlglKeyboardAPI {
    const bool *(*getState)(int *count);
    void (*reset)(void);
    SDL_Window *(*getFocus)(void);
    SDL_Keymod (*getModState)(void);
    void (*setModState)(SDL_Keymod modstate);
    SDL_Keycode (*getKeyFromScancode)(SDL_Scancode scancode, SDL_Keymod modstate, bool keyEvent);
    SDL_Scancode (*getScancodeFromKey)(SDL_Keycode key, SDL_Keymod *modstate);
    SDL_Keycode (*getKeyFromName)(const char *name);
    const char *(*getKeyName)(SDL_Keycode key);
    SDL_Scancode (*getScancodeFromName)(const char *name);
    const char *(*getScancodeName)(SDL_Scancode scancode);
    bool (*startTextInput)(SDL_Window *window);
    bool (*startTextInputWithProperties)(SDL_Window *window, SDL_PropertiesID props);
    bool (*textInputActive)(SDL_Window *window);
    bool (*stopTextInput)(SDL_Window *window);
    bool (*setTextInputArea)(SDL_Window *window, const SDL_Rect *rect, int cursor);
    bool (*getTextInputArea)(SDL_Window *window, SDL_Rect *rect, int *cursor);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglKeyboardAPI;

typedef struct LwsdlglMouseAPI {
    SDL_Window *(*getFocus)(void);
    SDL_MouseButtonFlags (*getState)(float *x, float *y);
    SDL_MouseButtonFlags (*getGlobalState)(float *x, float *y);
    SDL_MouseButtonFlags (*getRelativeState)(float *x, float *y);
    void (*warpInWindow)(SDL_Window *window, float x, float y);
    bool (*warpGlobal)(float x, float y);
    bool (*capture)(bool enabled);
    SDL_Cursor *(*createCursor)(const Uint8 *data, const Uint8 *mask, int width, int height, int hotX, int hotY);
    SDL_Cursor *(*createColorCursor)(SDL_Surface *surface, int hotX, int hotY);
    SDL_Cursor *(*createSystemCursor)(SDL_SystemCursor id);
    bool (*setCursor)(SDL_Cursor *cursor);
    SDL_Cursor *(*getCursor)(void);
    SDL_Cursor *(*getDefaultCursor)(void);
    void (*destroyCursor)(SDL_Cursor *cursor);
    bool (*showCursor)(void);
    bool (*hideCursor)(void);
    bool (*cursorVisible)(void);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglMouseAPI;

typedef struct LwsdlglGamepadAPI {
    SDL_JoystickID *(*getGamepads)(int *count);
    SDL_Gamepad *(*open)(SDL_JoystickID instanceID);
    void (*close)(SDL_Gamepad *gamepad);
    bool (*connected)(SDL_Gamepad *gamepad);
    const char *(*getName)(SDL_Gamepad *gamepad);
    SDL_GamepadType (*getType)(SDL_Gamepad *gamepad);
    Sint16 (*getAxis)(SDL_Gamepad *gamepad, SDL_GamepadAxis axis);
    bool (*getButton)(SDL_Gamepad *gamepad, SDL_GamepadButton button);
    bool (*hasAxis)(SDL_Gamepad *gamepad, SDL_GamepadAxis axis);
    bool (*hasButton)(SDL_Gamepad *gamepad, SDL_GamepadButton button);
    bool (*hasSensor)(SDL_Gamepad *gamepad, SDL_SensorType type);
    bool (*setSensorEnabled)(SDL_Gamepad *gamepad, SDL_SensorType type, bool enabled);
    bool (*sensorEnabled)(SDL_Gamepad *gamepad, SDL_SensorType type);
    bool (*getSensorData)(SDL_Gamepad *gamepad, SDL_SensorType type, float *data, int count);
    float (*getSensorDataRate)(SDL_Gamepad *gamepad, SDL_SensorType type);
    bool (*rumble)(SDL_Gamepad *gamepad, Uint16 low, Uint16 high, Uint32 durationMS);
    bool (*rumbleTriggers)(SDL_Gamepad *gamepad, Uint16 left, Uint16 right, Uint32 durationMS);
    bool (*setLED)(SDL_Gamepad *gamepad, Uint8 red, Uint8 green, Uint8 blue);
    bool (*sendEffect)(SDL_Gamepad *gamepad, const void *data, int size);
    void (*update)(void);
    void (*setEventsEnabled)(bool enabled);
    bool (*eventsEnabled)(void);
    int (*addMapping)(const char *mapping);
    int (*addMappingsFromFile)(const char *file);
    char *(*getMapping)(SDL_Gamepad *gamepad);
    char *(*getMappingForID)(SDL_JoystickID instanceID);
    bool (*reloadMappings)(void);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglGamepadAPI;

typedef struct LwsdlglAudioAPI {
    int (*getDriverCount)(void);
    const char *(*getDriver)(int index);
    const char *(*getCurrentDriver)(void);
    SDL_AudioDeviceID *(*getPlaybackDevices)(int *count);
    SDL_AudioDeviceID *(*getRecordingDevices)(int *count);
    const char *(*getDeviceName)(SDL_AudioDeviceID device);
    bool (*getDeviceFormat)(SDL_AudioDeviceID device, SDL_AudioSpec *spec, int *sampleFrames);
    SDL_AudioDeviceID (*openDevice)(SDL_AudioDeviceID device, const SDL_AudioSpec *spec);
    void (*closeDevice)(SDL_AudioDeviceID device);
    bool (*pauseDevice)(SDL_AudioDeviceID device);
    bool (*resumeDevice)(SDL_AudioDeviceID device);
    bool (*devicePaused)(SDL_AudioDeviceID device);
    SDL_AudioStream *(*createStream)(const SDL_AudioSpec *srcSpec, const SDL_AudioSpec *dstSpec);
    void (*destroyStream)(SDL_AudioStream *stream);
    SDL_AudioStream *(*openDeviceStream)(SDL_AudioDeviceID device, const SDL_AudioSpec *spec, SDL_AudioStreamCallback callback, void *userdata);
    bool (*bindStream)(SDL_AudioDeviceID device, SDL_AudioStream *stream);
    void (*unbindStream)(SDL_AudioStream *stream);
    bool (*putStreamData)(SDL_AudioStream *stream, const void *data, int len);
    int (*getStreamData)(SDL_AudioStream *stream, void *buffer, int len);
    int (*getStreamAvailable)(SDL_AudioStream *stream);
    int (*getStreamQueued)(SDL_AudioStream *stream);
    bool (*flushStream)(SDL_AudioStream *stream);
    bool (*clearStream)(SDL_AudioStream *stream);
    bool (*lockStream)(SDL_AudioStream *stream);
    bool (*unlockStream)(SDL_AudioStream *stream);
    bool (*setStreamGain)(SDL_AudioStream *stream, float gain);
    float (*getStreamGain)(SDL_AudioStream *stream);
    bool (*setStreamFrequencyRatio)(SDL_AudioStream *stream, float ratio);
    float (*getStreamFrequencyRatio)(SDL_AudioStream *stream);
    size_t abiSize;
    unsigned abiVersion;
} LwsdlglAudioAPI;

extern const LwsdlglSystemAPI System;
extern const LwsdlglDisplayAPI Display;
extern const LwsdlglWindowAPI Window;
extern const LwsdlglEventsAPI Events;
extern const LwsdlglKeyboardAPI Keyboard;
extern const LwsdlglMouseAPI Mouse;
extern const LwsdlglGamepadAPI Gamepad;
extern const LwsdlglAudioAPI Audio;

#include <lwsdlgl/gpu.h>
#include <lwsdlgl/shadercross.h>

#ifdef __cplusplus
}
#endif

#endif
