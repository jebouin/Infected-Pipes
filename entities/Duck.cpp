#include "Duck.h"
#include "IP.h"
#include "Level.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "Renderer.h"
#include "WaterField.h"

Duck::Duck(IP& ip)
    : GameEntity(ip, "duck", sf::IntRect(2, 1, 8, 9), 42) {
    SetInvincible(true);
    if(rand()%2==0) {
        setScale(-1, 1);
    }
}

Duck::~Duck() {

}

void Duck::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager) {
    GameEntity::Update(ip, eTime, level, eManager, pManager);
    bool inSurface = false;
    for(int i=0 ; i<level.GetNbWaterFields() ; i++) {
        WaterField& f(level.GetWaterField(i));
        if(!f.IsSurface()) {
            continue;
        }
        if(!f.GetRect().intersects(GetGlobalHitbox())) {
            continue;
        }
        float dy=0;
        int nb=0;
        for(float x=GetGlobalHitbox().left ; x<=GetGlobalHitbox().left+GetGlobalHitbox().width ; x+=2) {
            dy += f.GetHeight(x);
            nb++;
        }
        dy /= float(nb);
        setPosition(sf::Vector2f(getPosition().x, f.GetRect().top+dy-8));
        SetVel(sf::Vector2f(GetVel().x, 0));
        inSurface = true;
        break;
    }
    if(_inWater && !inSurface) {
        Accelerate(sf::Vector2f(0, -0.002), eTime);
    }
}

void Duck::Draw(IP& ip) {
    GameEntity::Draw(ip);
}
