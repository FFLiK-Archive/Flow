#pragma once
#include <SDL.h>
#include <Event.h>
#include <queue>
using namespace std;

class Scene {
public:
	Scene(int update_delay);
	virtual ~Scene();

	virtual int Rendering() abstract;
	int RegisterRenderer(SDL_Renderer* ren);
	int PushEvent(EventType type, SDL_Keycode key);
	bool IsRun();

	int __Process__();

protected:
	bool run = false;
	bool process_completed = false;

	SDL_Renderer* ren;

	queue<Event> event_queue;

	virtual int EventProcess(Event &evt) abstract;
	virtual int NormalProcess() abstract;

	int update_delay;
};

