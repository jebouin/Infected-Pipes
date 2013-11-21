#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class Player;
class Character;
class Level;

class Camera : public sf::View {
public:
    Camera(sf::FloatRect size);
    ~Camera();
    void Update(IP& ip, float eTime, Level& level, Character& character);

private:

};

#endif // CAMERA_H_INCLUDED
