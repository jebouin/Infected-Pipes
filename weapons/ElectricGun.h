#ifndef ELECTRICGUN_H_INCLUDED
#define ELECTRICGUN_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Weapon.h"

using namespace std;

class IP;
class TextureLoader;
class GameEntity;
class BulletManager;
class EntityManager;
class Ennemy;

class ElectricGun : public Weapon {
    public:
    ElectricGun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos);
    ~ElectricGun();
    void Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager);
    void Draw(IP& ip);
    bool Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager);
    int GetNbPoints(sf::Vector2f p0, sf::Vector2f p1, float dist);

    private:
    sf::Clock _hitTimer;
    float _radius;
    bool _shooting;
    float _timeSinceShot;
    sf::VertexArray _electricity;
    sf::VertexArray _subElec;
    vector<Ennemy*> _targets;
    vector<vector<float> > _midPoints;
};

#endif // ELECTRICGUN_H_INCLUDED
