#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class IP;

class Scene {
public:
    Scene(IP& ip);
    virtual ~Scene();
    virtual void Update(float eTime, IP& ip);
    virtual void Draw(IP& ip);
    bool IsActive();
    void End();

private:
    bool _active;
};

#endif
