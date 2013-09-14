#include "Pipe.h"
#include "IP.h"
#include "EntityManager.h"
#include "Ennemy.h"
#include "Spiderock.h"
#include "TextureLoader.h"
#include "MathHelper.h"

Pipe::Pipe(IP& ip, sf::Vector2f pos, float angle) : sf::Sprite() {
    setTexture(ip._textureLoader->GetTexture("pipe"));
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height/2.f));
    setPosition(pos);
    setRotation(angle);
}

Pipe::~Pipe() {

}

void Pipe::Update(IP& ip, EntityManager& eManager) {

}

void Pipe::Spawn(IP& ip, EntityManager& eManager) {
    Spiderock *e = new Spiderock(ip);
    e->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
    e->SetVel(MathHelper::Ang2Vec(MathHelper::Deg2Rad(getRotation())) * MathHelper::RandFloat(0.4f, 0.6f));
    eManager.Add(e);
}
