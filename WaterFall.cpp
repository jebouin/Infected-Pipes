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

WaterFall::WaterFall(IP& ip, sf::Vector2i tilePos, bool big, bool lava)
    : MovingSprite(ip, big ? "bigFalls" : "falls", big ? sf::IntRect(0, 0, 16, 16) : sf::IntRect(0, 0, 6, 16), true) {
    _big = big;
    _lava = lava;
    AnimationTable& t(GetAnims());
    if(big) {
        t.AddAnimation("waterFall", new Animation(8, 30, sf::Vector2i(0, 0), sf::Vector2i(16, 16), true));
        t.AddAnimation("lavaFall", new Animation(8, 50, sf::Vector2i(0, 16), sf::Vector2i(16, 16), true));
    } else {
        t.AddAnimation("waterFall", new Animation(8, 30, sf::Vector2i(0, 0), sf::Vector2i(6, 16), true));
        t.AddAnimation("lavaFall", new Animation(8, 50, sf::Vector2i(0, 16), sf::Vector2i(6, 16), true));
    }
    t.SetAnimation((lava ? "lavaFall" : "waterFall"));
    setPosition(sf::Vector2f(tilePos*16) + sf::Vector2f(8, 4));
    _tilePos = tilePos;
    SetCollideWithWater(false);

    _down = false;
    _shape.setPointCount(2 + (big?16:6) + 1);
    _shape.setPoint(0, sf::Vector2f(tilePos*16) + sf::Vector2f(big?16:11, -4));
    _shape.setPoint(1, sf::Vector2f(tilePos*16) + sf::Vector2f(big?0:5, -4));
}

WaterFall::~WaterFall() {

}

void WaterFall::Update(IP& ip, float elapsedTime, Level& level, ParticleManager& pManager) {
    MovingSprite::Update(ip, elapsedTime);

    if(_splashTimer.getElapsedTime().asMilliseconds() > (_lava ? 400 : 100)) {
        _splashTimer.restart();
        for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
            WaterField& wf(level.GetWaterField(i));
            if(!wf.IsSurface()) {
                continue;
            }
            if(GetGlobalHitbox().intersects(wf.GetRect())) {
                wf.Splash(getPosition() + sf::Vector2f(MathHelper::RandFloat(-GetGlobalHitbox().width/2.f+1, GetGlobalHitbox().width/2.f-1), GetGlobalHitbox().height/2.f), (_lava ? -MathHelper::RandFloat(1.7, 2.4) : -MathHelper::RandFloat(3., 5.)), pManager, ip);
            }
        }
    }

    _down = false;
    if(!_lava) {
        for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
            WaterField& wf(level.GetWaterField(i));
            if(!wf.IsSurface()) {
                continue;
            }
            if(GetGlobalHitbox().intersects(wf.GetRect())) {
                _down = true;
                //set the points corresponding to the field
                for(int i=2 ; i<_shape.getPointCount() ; i++) {
                    float x = i-2 + _shape.getPoint(1).x;
                    float l = wf.GetHeight(x);
                    _shape.setPoint(i, sf::Vector2f(x, (wf.GetRect().top+wf.GetRect().height)-l+1));
                }
            }
        }
    }

    _shape.setTexture(getTexture());
    _shape.setTextureRect(getTextureRect());

}

void WaterFall::Draw(IP& ip) {
    if(_down) {
        ip._renderer->Draw(_shape);
    } else {
        MovingSprite::Draw(ip);
    }
}

void WaterFall::Fall(IP& ip, Level& level) {
    for(int i=_tilePos.y+1 ; i<level.GetMap().GetSize().y ; i++) {
        sf::Vector2i curTilePos(_tilePos.x, i);
        sf::FloatRect curRect(sf::Vector2f(curTilePos)*16.f, sf::Vector2f(16, 16));
        level.AddWaterFall(ip, curTilePos, _big, _lava);
        if(_lava) {
            continue;
        }
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

bool WaterFall::IsLava() {
    return _lava;
}
