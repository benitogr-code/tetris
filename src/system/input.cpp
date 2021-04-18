#include "input.h"

#include <SDL.h>

Input::Input() {
  _scanCodes.insert(TScanCodes::value_type(SDL_SCANCODE_ESCAPE, KeyId_Escape));
  _scanCodes.insert(TScanCodes::value_type(SDL_SCANCODE_UP, KeyId_Up));
  _scanCodes.insert(TScanCodes::value_type(SDL_SCANCODE_DOWN, KeyId_Down));
  _scanCodes.insert(TScanCodes::value_type(SDL_SCANCODE_LEFT, KeyId_Left));
  _scanCodes.insert(TScanCodes::value_type(SDL_SCANCODE_RIGHT, KeyId_Right));
}

void Input::update() {
  const int maxEvents = 32;
  SDL_Event events[maxEvents];
  const int eventsRead = SDL_PeepEvents(events, maxEvents, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYUP);

  if (eventsRead == -1) {
    LOG_ERROR("Error reading keyboard events: {}", SDL_GetError());

    return;
  }

  std::vector<InputEvent> inputEvents;
  inputEvents.reserve(eventsRead);

  for (int i = 0; i < eventsRead; ++i) {
    const auto& keyEvent = events[i].key;

    const auto iter = _scanCodes.find(keyEvent.keysym.scancode);
    if (iter != _scanCodes.end()) {
      InputEvent input;
      input.keyId = iter->second;
      input.state = keyEvent.type == SDL_KEYDOWN ? InputState_Pressed : InputState_Released;
      input.state |= keyEvent.repeat > 0 ? InputState_Hold : 0;

      inputEvents.push_back(input);
    }
  }

  for (auto iter = inputEvents.begin(); iter != inputEvents.end(); ++iter) {
    _callback(*iter);
  }
}
