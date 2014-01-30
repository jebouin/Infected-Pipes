#include "HealingParticle.h"
#include "ParticleManager.h"
#include "MathHelper.h"
#include "IP.h"
#include "Renderer.h"

HealingParticle::HealingParticle(IP& ip, int amount, sf::Vector2f pos)
    : Particle(ip, "blood", pos, sf::Vector2f(0, -.07), 0, 700, sf::Vector2f(1, 1), sf::Vector2f(1, 1), 255, 0, false, false, false, sf::IntRect(0, 0, 1, 1), true) {
    std::string healingText = MathHelper::NbToStringWithUnit(amount);
    int fontSize = (amount >= 1000 ? 24 : 16);
    _text.setFont(ip._font);
    _text.setCharacterSize(fontSize);
    _text.setString(healingText);
    setColor(sf::Color(0, 255, 0));
    _text.setOrigin(sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height)/2.f);
    SetHitbox(sf::IntRect(8, 2, _text.getLocalBounds().width-3, _text.getLocalBounds().height-2));
}

HealingParticle::~HealingParticle() {

}

void HealingParticle::Update(IP& ip, float eTime, Level& level, ParticleManager& pManager) {
    Particle::Update(ip, eTime, level, pManager);
    _text.setPosition(getPosition());
    _text.setColor(getColor());
}

void HealingParticle::Draw(IP& ip) {
    ip._renderer->Draw(_text);
}
