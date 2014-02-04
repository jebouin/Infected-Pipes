#ifndef JELLYFISH_H_INCLUDED
#define JELLYFISH_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Ennemy.h"

class IP;
class Level;
class Character;
class EntityManager;
class ParticleManager;
class BulletManager;

struct TentaclePoint {
    sf::Vector2f pos;
    sf::Vector2f vel;
};

class Jellyfish : public Ennemy {
    public:
    Jellyfish(IP& ip, Level& level);
    ~Jellyfish();
    void Update(IP& ip, float eTime, Level& level, Character& character, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void Die(IP& ip, ParticleManager& pManager, EntityManager& eManager, Level& level);

    private:
    bool _initTentacles;
    sf::Clock _attackTimer;
    sf::Clock _moveTimer;
    sf::Clock _deathTimer;
    sf::Clock _explosionTimer;
    float _moveTime;
    vector<vector<TentaclePoint> > _tentacles;
    vector<float> _tentaclesMovement;
    sf::VertexArray _tentaclesLines;
    bool _dying;
};

#endif // JELLYFISH_H_INCLUDED
