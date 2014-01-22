#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class IP;
class LifeBar;
class TextureLoader;
class Character;
class XPBar;
class LevelIndicator;
class DifficultyIndicator;
class Level;
class WaveIndicator;

class GUI {
    public:
    GUI(IP& ip, Character& character, Level& level);
    ~GUI();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);
    WaveIndicator& GetWaveIndicator();

    private:
    LifeBar *_lifeBar;
    XPBar *_xpBar;
    LevelIndicator *_levelIndicator;
    DifficultyIndicator *_difficultyIndicator;
    WaveIndicator *_waveIndicator;
};

#endif // GUI_H_INCLUDED
