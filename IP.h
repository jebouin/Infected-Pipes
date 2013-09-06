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

class IP {
    public:
    IP();
    ~IP();
    void Update();
    void Draw();

    Renderer *_renderer;
    TextureLoader *_textureLoader;

    private:
    sf::Clock _clock;
    sf::RenderWindow *_window;
    Level *_level;
    EntityManager *_entityManager;
    Player *_player;
    Background *_background;
    Grass *_grass;
};

#endif // IP_H_INCLUDED
