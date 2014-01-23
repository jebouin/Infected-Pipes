#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include <vector>
#include <iostream>

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
    void AddSceneToRemoveStack();
    void AddSceneToAddStack(Scene* scene);

private:
    void RemoveScene(); //private, cause using it outside of the class can result in mem leaks

    std::vector<Scene*> _addStack;
    std::vector<Scene*> _scenes;
    int _scenesToRemove;
};

#endif
