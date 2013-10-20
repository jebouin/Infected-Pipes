#ifndef SPEECHMANAGER_H_INCLUDED
#define SPEECHMANAGER_H_INCLUDED

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

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
    vector<SpeechBubble*> _bubbles;
};

#endif SPEECHMANAGER_H_INCLUDED
