#include "Pipe.h"
#include "IP.h"
#include "EntityManager.h"
#include "Ennemy.h"
#include "TextureLoader.h"
#include "MathHelper.h"

Pipe::Pipe(IP& ip, sf::Vector2f pos) {
    setTexture(ip._textureLoader->GetTexture("pipe"));
    setPosition(pos);
}

Pipe::~Pipe() {

}

void Pipe::Update(IP& ip, EntityManager& eManager) {
    if(c.getElapsedTime().asMilliseconds() > 20 && eManager.GetNbEnnemies() < 4) {
        Spawn(ip, eManager);
        c.restart();
    }
}

void Pipe::Spawn(IP& ip, EntityManager& eManager) {
    Ennemy *e = new Ennemy(ip);
    e->setPosition(sf::Vector2f(getPosition().x+e->getGlobalBounds().width/2.f, getPosition().y+getGlobalBounds().height/2.f));
    e->SetVel(sf::Vector2f(-MathHelper::RandFloat(0.5f, 1.2f), 0));
    eManager.Add(e);
}
