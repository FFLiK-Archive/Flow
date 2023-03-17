#include <SDL.h>
#include <iostream>
#include <Window.h>
#include <Scene.h>
#include <MainScene.h>
#include <Log.h>
using namespace std;

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Window* win = new Window({"Flow", 1280, 720, 60});
	win->Rendering();

	Scene* scene;
	scene = new MainScene(500);
	win->AddScene(scene, 0);

	bool run = true;
	while (run) {
		switch (win->PollEvent()) {
		case QUIT:
			run = false;
			break;
		}
	}
	delete win;
	SDL_Quit();
	return 0;
}