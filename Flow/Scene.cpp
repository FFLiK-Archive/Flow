#include "Scene.h"
#include <thread>
#include <iostream>
#include <Log.h>
using namespace std;

Scene::Scene(int update_delay){
    Log::PrintLog("Scene", "Constructor", "생성자 호출");
    this->run = true;
    this->process_completed = false;
    this->update_delay = update_delay;
    thread th([&]() {this->__Process__();});
    th.detach();
}

Scene::~Scene() {
    Log::PrintLog("Scene", "Destructor", "소멸자 호출");
    this->run = false;
    while (!this->process_completed);
    //TODO : Destroy Data
}

int Scene::RegisterRenderer(SDL_Renderer* ren) {
    this->ren = ren;
    return 0;
}

int Scene::PushEvent(EventType type, SDL_Keycode key) {
    this->event_queue.push({ type, key });
    return 0;
}

int Scene::__Process__() {
    while (this->run) {
        while (!this->event_queue.empty()) {
            this->EventProcess(this->event_queue.front());
            this->event_queue.pop();
        }
        this->NormalProcess();
        SDL_Delay(update_delay);
    }
    this->process_completed = true;
    return 0;
}

bool Scene::IsRun() {
    return this->run;
}
