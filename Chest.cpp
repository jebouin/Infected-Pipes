#include "Chest.h"
#include "IP.h"
#include "Level.h"
#include "ChestOpened.h"

Chest::Chest(IP& ip, sf::Vector2f pos) : MovingSprite(ip, "chest", sf::IntRect(0, 0, 30, 20), true) {
    setPosition(pos);
    _chestOpened = new ChestOpened(ip);
    _opened = false;
}

Chest::~Chest() {
    delete _chestOpened;
    _chestOpened = 0;
}

void Chest::Update(IP& ip, float eTime, Level& level) {
    Accelerate(sf::Vector2f(0, 0.003), eTime);
    MovingSprite::Update(ip, eTime, level);

    _chestOpened->Update(ip, eTime);
}

void Chest::Draw(IP& ip) {
    MovingSprite::Draw(ip);
    if(_opened) {
        _chestOpened->Draw(ip);
    }
}

void Chest::Open(IP& ip) {
    _opened = true;
    delete _chestOpened;
    _chestOpened = new ChestOpened(ip);
}
