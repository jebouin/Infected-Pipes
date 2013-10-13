#include "SceneManager.h"
#include "Scene.h"
#include "IP.h"

SceneManager::SceneManager(IP& ip) {

}

SceneManager::~SceneManager(){

}

void SceneManager::Update(float eTime, IP& ip){
    if(GetNbScenes() > 0) {
        _scenes[_scenes.size()-1]->Update(eTime, ip);
    }
}

void SceneManager::Draw(IP& ip){
    if(GetNbScenes() > 0) {
        _scenes[_scenes.size()-1]->Draw(ip);
    }
}

void SceneManager::AddScene(Scene* scene){
    _scenes.push_back(scene);
}

int SceneManager::GetNbScenes() {
    return _scenes.size();
}
