#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class Character;
class EntityManager;
class Level;
class ParticleManager;
class BulletManager;
class GUI;
class Camera;
class SkillTree;

class Player {
    public:
    Player(IP& ip, EntityManager& eManager);
    ~Player();
    void Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager);
    void Draw(IP& ip);
    void DrawFront(IP& ip);
    sf::View& GetView();
    Character& GetCharacter();
    SkillTree& GetSkillTree();

    private:
    Camera *_camera;
    Character *_character;
    SkillTree *_skillTree;
};

#endif // PLAYER_H_INCLUDED
