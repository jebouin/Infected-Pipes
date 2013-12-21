#ifndef IP_H_INCLUDED
#define IP_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Renderer;
class SceneManager;
class ShaderManager;

class IP {
    public:
    IP();
    ~IP();
    void Update();
    void Draw();

    Renderer *_renderer;
    sf::RenderWindow *_window;
    SceneManager *_sceneManager;
    sf::Font _font;

    private:
    void LoadResources();

    sf::Clock _clock;
    bool _focused;
};

#endif // IP_H_INCLUDED
