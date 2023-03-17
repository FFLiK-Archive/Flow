#include <SDL.h>

enum EventType { NONE, QUIT, KEY_DOWN, KEY_UP };

class Event {
public:
	EventType type;
	SDL_Keycode key;
};