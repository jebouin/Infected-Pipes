#include "Spawner.h"
#include "IP.h"
#include "EntityManager.h"
#include "MovingSprite.h"
#include "Pipe.h"
#include "Renderer.h"

Spawner::Spawner(IP& ip) {

}

Spawner::~Spawner() {
    for(int i=0 ; i<_pipes.size() ; i++) {
        delete _pipes[0];
        _pipes.erase(_pipes.begin());
    }
}

void Spawner::Update(IP& ip, EntityManager& eManager) {
    for(int i=0 ; i<_pipes.size() ; i++) {
        _pipes[i]->Update(ip, eManager);
    }
}

void Spawner::Draw(IP& ip) {
    for(int i=0 ; i<_pipes.size() ; i++) {
        ip._renderer->Draw(*_pipes[i]);
    }
}

void Spawner::AddPipe(Pipe *p) {
    _pipes.push_back(p);
}

bool Spawner::IsCollided(sf::FloatRect rect) {
    for(int i=0 ; i<_pipes.size() ; i++) {
        if(rect.intersects(_pipes[i]->getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

bool Spawner::IsCollided(MovingSprite& sprite, sf::Vector2f pos) {
    return IsCollided(sf::FloatRect(sf::Vector2f(sprite.GetHitbox().left, sprite.GetHitbox().top)+pos, sf::Vector2f(sprite.GetHitbox().width, sprite.GetHitbox().height)));
}

bool Spawner::IsCollided(MovingSprite& sprite) {
    return IsCollided(sprite.GetGlobalHitbox());
}

bool Spawner::IsOnGround(MovingSprite& sprite) {
    sf::FloatRect rect(sprite.GetGlobalHitbox().left, sprite.GetGlobalHitbox().top+sprite.GetGlobalHitbox().height+1, sprite.GetGlobalHitbox().width, 1);
    if(IsCollided(rect)) {
        return true;
    }
    return false;
}
