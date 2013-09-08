#include "DamageParticle.h"
#include "IP.h"
#include "Animation.h"
#include "AnimationTable.h"

DamageParticle::DamageParticle(IP& ip, int damage, sf::Vector2f pos, sf::Vector2f velocity, float lifeTime, sf::Vector2f startScale, sf::Vector2f endScale, bool gravity, bool collision)
    : Particle(ip, "blood0", pos, velocity, 0, lifeTime, startScale, endScale, 255, 0, gravity, collision, false, sf::IntRect(0, 0, 1, 1)) {
    int l = 0;
    int fontSize = 12;
    for(l=0 ; pow(10, l) <= damage ; l++);
    sf::Sprite sprites[l];
    sf::Vector2i totalSize(0, 0);
    const_cast<sf::Texture&>(ip._font.getTexture(fontSize)).setSmooth(false);
    for(int i=l-1 ; i>=0 ; i--) {
        const sf::Glyph& g(ip._font.getGlyph('0'+((int)(damage/pow(10, i)) % 10), fontSize, false));
        sprites[i].setTexture(ip._font.getTexture(fontSize));
        sprites[i].setTextureRect(g.textureRect);
        sprites[i].setPosition(sf::Vector2f(totalSize.x, 0));
        totalSize.x += g.textureRect.width;
        g.textureRect.height > totalSize.y ? totalSize.y = g.bounds.height:0;
    }
    _texture.create(totalSize.x, totalSize.y);
    _texture.setSmooth(false);
    _texture.clear(sf::Color(0, 0, 0, 0));
    for(int i=0 ; i<l ; i++) {
        _texture.draw(sprites[i]);
    }
    _texture.display();
    setColor(sf::Color(255, 128, 0));
    setTexture(_texture.getTexture());
    setTextureRect(sf::IntRect(0, 0, _texture.getSize().x, _texture.getSize().y));
    SetHitbox(sf::IntRect(0, 0, getTextureRect().width, getTextureRect().height-2));
}

DamageParticle::~DamageParticle() {

}
