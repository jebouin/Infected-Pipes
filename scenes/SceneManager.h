#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include <iostream>
#include <vector>

class IP;
class Scene;

using namespace std;

class SceneManager {
public:
    SceneManager(IP& ip);
    ~SceneManager();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);
    void AddScene(Scene* scene);
    int GetNbScenes();

private:
    vector<Scene*> _scenes;
};

#endif
