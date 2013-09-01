#ifndef IP_H_INCLUDED
#define IP_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Renderer;
class TextureLoader;
class Map;
class EntityManager;
class Player;

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
    Map *_map;
    EntityManager *_entityManager;
    Player *_player;
};

#endif // IP_H_INCLUDED
