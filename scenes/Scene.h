#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class IP;

class Scene {
public:
    Scene(IP& ip, bool transparent);
    virtual ~Scene();
    virtual void Update(float eTime, IP& ip);
    virtual void Draw(IP& ip);
    bool IsActive();
    bool IsTransparent();
    void End();
    void SetTransparent(bool t);

private:
    bool _active;
    bool _transparent;
};

#endif
