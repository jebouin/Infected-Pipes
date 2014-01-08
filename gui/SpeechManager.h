#ifndef SPEECHMANAGER_H_INCLUDED
#define SPEECHMANAGER_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class SpeechBubble;
class IP;

class SpeechManager {
public:
    SpeechManager();
    ~SpeechManager();
    void Update(IP& ip, float eTime);
    void Draw(IP& ip);
    void AddBubble(SpeechBubble* b);
    void Clear();
private:
    std::vector<SpeechBubble*> _bubbles;
};

#endif SPEECHMANAGER_H_INCLUDED
