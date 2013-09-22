#ifndef DIFFICULTYINDICATOR_H_INCLUDED
#define DIFFICULTYINDICATOR_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class IP;
class TextureLoader;
class Level;

struct Comment {
    string _text;
    int _dif;
};

class DifficultyIndicator : public sf::Sprite {
    public:
    DifficultyIndicator(IP& ip, Level& level, TextureLoader& tLoader);
    ~DifficultyIndicator();
    void Update(IP& ip);
    void Draw(IP& ip);

    private:
    const Level& _level;
    sf::Text _difficultyText;
    sf::Text _commentText;
    sf::Text _nbText;
    Comment _comments[15];
    int _curCommentID;
};

#endif // DIFFICULTYINDICATOR_H_INCLUDED
