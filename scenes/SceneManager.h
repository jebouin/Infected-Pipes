#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include <vector>

class IP;
class Scene;



class SceneManager {
public:
    SceneManager(IP& ip);
    ~SceneManager();
    void Update(float eTime, IP& ip);
    void Draw(IP& ip);
    void AddScene(Scene* scene);
    int GetNbScenes();
    void RemoveScene();

private:
    std::vector<Scene*> _scenes;
};

#endif
