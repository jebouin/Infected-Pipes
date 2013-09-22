#ifndef BULLETMANAGER_H_INCLUDED
#define BULLETMANAGER_H_INCLUDED

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Bullet;
class Level;

class BulletManager {
    public:
    BulletManager();
    ~BulletManager();
    void Update(IP& ip, float eTime, Level& level);
    void Draw(IP& ip);
    void AddBullet(Bullet* bullet);
    void Clear();
    int GetCount();
    Bullet* GetBullet(int id);

    private:
    vector<Bullet*> _bullets;
};

#endif // BULLETMANAGER_H_INCLUDED
