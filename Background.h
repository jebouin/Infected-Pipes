#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Map;

class Background {
    public:
    Background(IP& ip, std::string name, float zoom, Map& map);
    ~Background();
    void Update(IP& ip, float elapsedTime);
    void Draw(sf::RenderTexture& rt, const sf::View& prevView);

    private:
    std::string _name;
    std::vector<sf::Sprite> _backSprites;
    std::vector<sf::Sprite> _backSprites2;
    sf::Sprite _back;
    sf::Sprite _back2;
    sf::Sprite _forest;
    sf::Sprite _mountains;
    sf::Sprite _clouds;
    float _cloudsX;
    sf::View _view;
    float _zoom;

    //const Level& _level;
};

#endif // BACKGROUND_H_INCLUDED
