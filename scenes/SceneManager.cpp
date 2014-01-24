#include "SceneManager.h"
#include "Scene.h"
#include "IP.h"

SceneManager::SceneManager(IP& ip) {
    _scenesToRemove = 0;
}

SceneManager::~SceneManager(){
    for(int i=0 ; i<_scenes.size() ; i++) {
        delete _scenes[i];
        _scenes[i] = 0;
    }
    _scenes.clear();
    for(int i=0 ; i<_addStack.size() ; i++) {
        delete _addStack[i];
        _addStack[i] = 0;
    }
    _addStack.clear();
}

void SceneManager::Update(float eTime, IP& ip){
    for(int i=0 ; i<_scenesToRemove ; i++) {
        RemoveScene();
    }
    _scenesToRemove = 0;
    for(int i=0 ; i<_addStack.size() ; i++) {
        AddScene(_addStack[i]);
    }
    _addStack.clear();


    if(GetNbScenes() > 0) {
        _scenes[_scenes.size()-1]->Update(eTime, ip);
    }
}

void SceneManager::Draw(IP& ip){
    int i;
    for(i=_scenes.size()-1 ; i>0 ; i--) {
        if(!_scenes[i]->IsTransparent()) {
            break;
        }
    }
    for(;i<_scenes.size() ; i++) {
        _scenes[i]->Draw(ip);
    }
}

void SceneManager::AddScene(Scene* scene){
    _scenes.push_back(scene);
}

int SceneManager::GetNbScenes() {
    return _scenes.size();
}

void SceneManager::AddSceneToRemoveStack() {
    _scenesToRemove++;
}

void SceneManager::RemoveScene() {
    delete _scenes[_scenes.size()-1];
    _scenes[_scenes.size()-1] = 0;
    _scenes.pop_back();
}

void SceneManager::AddSceneToAddStack(Scene* scene) {
    _addStack.push_back(scene);
}
