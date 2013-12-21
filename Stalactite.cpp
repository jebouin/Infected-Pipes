#include "Stalactite.h"
#include "Level.h"
#include "IP.h"
#include "ResourceLoader.h"
#include "Character.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "Map.h"

Stalactite::Stalactite(sf::Vector2i tilePos) {
    _base.setTexture(ResourceLoader::GetTexture("stalactite"));
    _stalactite.setTexture(ResourceLoader::GetTexture("stalactite"));
    _base.setTextureRect(sf::IntRect(0, 0, 16, 22));
    _stalactite.setTextureRect(sf::IntRect(32, 0, 16, 22));
    _base.setPosition(sf::Vector2f(tilePos.x*16, tilePos.y*16-4));
    _separated = false;
    _dead = false;
}

Stalactite::~Stalactite() {

}

void Stalactite::Update(IP& ip, float eTime, Level& level, Character& character, ParticleManager& pManager, EntityManager& eManager) {
    sf::Vector2f charPos = character.getPosition();
    if(MathHelper::ABS(charPos.x - (_base.getPosition().x + 4)) <= 8 && !_separated) {
        _separated = true;
        _base.setTextureRect(sf::IntRect(16, 0, 16, 22));
        _regenTimer.restart();
        _yVel = 0;
        _stalactite.setPosition(_base.getPosition());
    }

    if(_separated) {
        if(character.GetGlobalHitbox().intersects(_stalactite.getGlobalBounds()) && _damageTimer.getElapsedTime().asMilliseconds() >= 800) {
            _damageTimer.restart();
            character.Damage(16, ip, pManager, sf::Color(255, 0, 0), sf::Vector2f(0, 0), MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-110, -70)))*.7f, eManager, level);
            character.Accelerate(MathHelper::Ang2Vec(MathHelper::Deg2Rad(character.getPosition().x > _stalactite.getPosition().x+4 ? 0 : 180))*.03f, eTime);
        }

        sf::FloatRect rect = _stalactite.getGlobalBounds();
        if(level.GetMap().IsCollided(sf::FloatRect(rect.left, rect.top-8, rect.width, rect.height), Map::WALL) && !_dead && _stalactite.getPosition().y - 16 > _base.getPosition().y) {
            _dead = true;
        } else if(!_dead) {
            _yVel += .001f*eTime;
            _stalactite.setPosition(_stalactite.getPosition() + sf::Vector2f(0, _yVel*eTime));
        }

        if(_regenTimer.getElapsedTime().asMilliseconds() >= 1000) {
            _separated = false;
            _dead = false;
            _base.setTextureRect(sf::IntRect(0, 0, 16, 22));
        }
    }
}

void Stalactite::Draw(IP& ip) {
    ip._renderer->Draw(_base);
    if(_separated/* && !_dead*/) {
        ip._renderer->Draw(_stalactite);
    }
}
