#include "Scene.h"
#include "IP.h"

Scene::Scene(IP& ip) {
    _active = true;
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

void Scene::End() {
    _active = false;
}
