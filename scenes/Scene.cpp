#include "Scene.h"
#include "IP.h"

Scene::Scene(IP& ip, bool transparent) {
    _active = true;
    _transparent = transparent;
}

Scene::~Scene() {

}

void Scene::Update(float eTime, IP& ip){

}

void Scene::Draw(IP& ip){

}

bool Scene::IsActive() {
    return _active;
}

bool Scene::IsTransparent() {
    return _transparent;
}

void Scene::End() {
    _active = false;
}

void Scene::SetTransparent(bool t) {
    _transparent = t;
}
