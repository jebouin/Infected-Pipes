#include "SpeechManager.h"
#include "SpeechBubble.h"
#include "IP.h"

SpeechManager::SpeechManager() {

}

SpeechManager::~SpeechManager() {
    Clear();
}

void SpeechManager::Update(IP& ip, float eTime) {
    for(int i=0 ; i<_bubbles.size() ; i++) {
        _bubbles[i]->Update(ip, eTime);
        /*if(!_bubbles[i]->IsAlive()) {
            delete _bubbles[i];
            _bubbles[i] = 0;
            _bubbles.erase(_bubbles.begin() + i);
            i--;
        }*/
    }
}

void SpeechManager::Draw(IP& ip) {
    for(int i=0 ; i<_bubbles.size() ; i++) {
        _bubbles[i]->Draw(ip);
    }
}

void SpeechManager::AddBubble(SpeechBubble* b) {
    _bubbles.push_back(b);
}

void SpeechManager::Clear() {
    for(int i=0 ; i<_bubbles.size() ; i++) {
        delete _bubbles[i];
        _bubbles[i] = 0;
    }
    _bubbles.clear();
}
