#include "WaterFall.h"
#include "IP.h"
#include "Renderer.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "MathHelper.h"
#include "Animation.h"
#include "AnimationTable.h"
#include "Level.h"
#include "WaterField.h"
#include "Map.h"

WaterFall::WaterFall(IP& ip, sf::Vector2i tilePos, bool big)
    : MovingSprite(ip, big ? "bigWaterFall" : "waterFall", big ? sf::IntRect(0, 0, 16, 16) : sf::IntRect(0, 0, 6, 16), true) {
    _big = big;
    AnimationTable& t(GetAnims());
    if(big) {
        t.AddAnimation("fall", new Animation(8, 30, sf::Vector2i(0, 0), sf::Vector2i(16, 16), true));
    } else {
        t.AddAnimation("fall", new Animation(8, 30, sf::Vector2i(0, 0), sf::Vector2i(6, 16), true));
    }
    t.SetAnimation("fall");
    setPosition(sf::Vector2f(tilePos*16) + sf::Vector2f(8, 4));
    _tilePos = tilePos;
}

WaterFall::~WaterFall() {

}

void WaterFall::Update(IP& ip, float elapsedTime, Level& level, ParticleManager& pManager) {
    MovingSprite::Update(ip, elapsedTime);

    if(_splashTimer.getElapsedTime().asMilliseconds() > 100) {
        _splashTimer.restart();
        for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
            WaterField& wf(level.GetWaterField(i));
            if(!wf.IsSurface()) {
                continue;
            }
            if(GetGlobalHitbox().intersects(wf.GetRect())) {
                wf.Splash(getPosition() + sf::Vector2f(MathHelper::RandFloat(-GetGlobalHitbox().width/2.f+1, GetGlobalHitbox().width/2.f-1), GetGlobalHitbox().height/2.f), -MathHelper::RandFloat(3., 5.), pManager, ip);
            }
        }
    }
}

void WaterFall::Draw(IP& ip) {
    MovingSprite::Draw(ip);
}

void WaterFall::Fall(IP& ip, Level& level) {
    for(int i=_tilePos.y+1 ; i<level.GetMap().GetSize().y ; i++) {
        sf::Vector2i curTilePos(_tilePos.x, i);
        sf::FloatRect curRect(sf::Vector2f(curTilePos)*16.f, sf::Vector2f(16, 16));
        level.AddWaterFall(ip, curTilePos, _big);
        for(int j=0 ; j<level.GetNbWaterFields() ; j++) {
            WaterField& wf(level.GetWaterField(j));
            if(!wf.IsSurface()) {
                continue;
            }
            if(wf.GetRect().intersects(curRect)) {
                return;
            }
        }
    }
}
