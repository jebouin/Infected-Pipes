#ifndef IP_H_INCLUDED
#define IP_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Renderer;
class TextureLoader;
class Level;
class EntityManager;
class Player;
class Background;
class Grass;
class ParticleManager;
class GUI;
class BulletManager;

class IP {
    public:
    IP();
    ~IP();
    void Update();
    void Draw();

    Renderer *_renderer;
    TextureLoader *_textureLoader;
    sf::RenderWindow *_window;
    sf::Font _font;

    private:
    sf::Clock _clock;
    Level *_level;
    EntityManager *_entityManager;
    BulletManager *_bulletManager;
    Player *_player;
    ParticleManager *_particleManager;
    GUI *_gui;
};

#endif // IP_H_INCLUDED
