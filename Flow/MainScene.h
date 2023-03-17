#pragma once
#include <Scene.h>

#define MAINSCENE(x) ((MainScene*)x)

class MainScene : public Scene {
public:
	MainScene(int update_delay = 0);
	~MainScene();
	int Rendering();

private:
	int EventProcess(Event& evt);
	int NormalProcess();
};

