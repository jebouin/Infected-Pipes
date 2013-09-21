#include "DamageParticle.h"
#include "IP.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "MathHelper.h"

DamageParticle::DamageParticle(IP& ip, int damage, sf::Vector2f pos, sf::Vector2f velocity, sf::Vector2f startScale, sf::Vector2f endScale, bool gravity, bool collision)
    : Particle(ip, "blood0", pos, velocity, 0, (damage >= 1000 ? MathHelper::RandFloat(1500, 1800) : MathHelper::RandFloat(600, 800)), startScale, endScale, 255, 0, gravity, collision, false, sf::IntRect(0, 0, 1, 1)) {
    string damageText = MathHelper::NbToStringWithUnit(damage);
    int fontSize = (damage >= 1000 ? 20 : 16);
    sf::Sprite sprites[damageText.size()];
    sf::Vector2i totalSize(0, 0);
    const_cast<sf::Texture&>(ip._font.getTexture(fontSize)).setSmooth(false);
    for(int i=0 ; i<damageText.size() ; i++) {
        const sf::Glyph& g(ip._font.getGlyph(damageText[i], fontSize, false));
        sprites[i].setTexture(ip._font.getTexture(fontSize));
        sprites[i].setTextureRect(g.textureRect);
        sprites[i].setPosition(sf::Vector2f(totalSize.x, 0));
        totalSize.x += g.textureRect.width;
        g.textureRect.height > totalSize.y ? totalSize.y = g.bounds.height:0;
    }
    _texture.create(totalSize.x, totalSize.y);
    _texture.setSmooth(false);
    _texture.clear(sf::Color(0, 0, 0, 0));
    for(int i=0 ; i<damageText.size() ; i++) {
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
