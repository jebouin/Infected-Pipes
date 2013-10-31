#ifndef IP_H_INCLUDED
#define IP_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Renderer;
class TextureLoader;
class SceneManager;

class IP {
    public:
    IP();
    ~IP();
    void Update();
    void Draw();

    Renderer *_renderer;
    TextureLoader *_textureLoader;
    sf::RenderWindow *_window;
    SceneManager *_sceneManager;
    sf::Font _font;

    private:
    sf::Clock _clock;
    bool _focused;
};

#endif // IP_H_INCLUDED
