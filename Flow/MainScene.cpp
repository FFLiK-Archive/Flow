#include "MainScene.h"
#include <iostream>
#include <Log.h>
using namespace std;

MainScene::MainScene(int update_delay) : Scene(update_delay) {
    Log::PrintLog("MainScene", "Constructor", "생성자 호출");
}

MainScene::~MainScene() {
    Log::PrintLog("MainScene", "Destructor", "소멸자 호출");
    this->run = false;
    while (!this->process_completed);
    //TODO : Delete Something
}

int MainScene::Rendering() {
    return 0;
}

int MainScene::EventProcess(Event& evt) {

    return 0;
}

int MainScene::NormalProcess() {

    return 0;
}
