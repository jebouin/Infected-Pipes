#include "ElectricGun.h"
#include "IP.h"
#include "GameEntity.h"
#include "BulletManager.h"
#include "GunBullet.h"
#include "MathHelper.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "Ennemy.h"

ElectricGun::ElectricGun(IP& ip, const GameEntity& holder, sf::Vector2f relativePos) : Weapon(ip, holder, relativePos, 500) {
    _timeSinceShot = 0;
    _radius = 200;
    _shooting = false;
    _electricity.setPrimitiveType(sf::LinesStrip);
    _subElec.setPrimitiveType(sf::LinesStrip);
}

ElectricGun::~ElectricGun() {

}

void ElectricGun::Update(IP& ip, float eTime, BulletManager& bManager, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    Weapon::Update(ip, eTime, bManager, eManager, level, pManager);
    if(_shooting) {
        //hit enemies
        if(_hitTimer.getElapsedTime().asMilliseconds() > 70) {
            _hitTimer.restart();
            for(int i=0 ; i<_targets.size() ; i++) {
                float dmg = MathHelper::RandFloat(20, 25);
                float hp = _targets[i]->GetHP();
                _targets[i]->Damage(dmg, ip, pManager, sf::Color(255, 255, 0), _targets[i]->getPosition(), sf::Vector2f(0, MathHelper::RandFloat(-.25, -.2)), eManager, level);
                if(dmg >= hp) {
                    _targets.erase(_targets.begin() + i);
                    i--;
                }
            }
        }


        sf::Vector2f mpos = ip._renderer->GetTexture().mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*ip._window))/4);
        _timeSinceShot += eTime;

        //update mid pos
        for(int i=0 ; i<_midPoints.size() ; i++) {
            for(int j=0 ; j<_midPoints[i].size() ; j++) {
                if(j==0) {
                    continue;
                }
                if(rand()%16==0) {
                    _midPoints[i][j] = MathHelper::RandFloat(-24, 24);
                }
            }
        }

        //set vertexes position
        _electricity[0].position = _position;
        _electricity[_electricity.getVertexCount()-1].position = mpos;
        int id = 0;
        for(int i=0 ; i<_midPoints.size() ; i++) {
            sf::Vector2f pos0(_electricity[id].position);
            sf::Vector2f pos1(_electricity[id+_midPoints[i].size()].position);
            float l(MathHelper::GetVecLength(pos0-pos1));
            sf::Vector2f dir = (pos1-pos0)/l;
            for(int j=0 ; j<_midPoints[i].size() ; j++) {
                if(j != 0) {
                    sf::Vector2f pos = pos0 + dir*24.f*float(j);
                    pos += _midPoints[i][j]*sf::Vector2f(-dir.y, dir.x);
                    _electricity[id].position = pos;
                }
                id++;
            }
        }

        /*if(_targets.size() == 0) {
            //gun to mouse
            sf::Vector2f pos0(_position);
            sf::Vector2f pos1(mpos);
            float l(MathHelper::GetVecLength(pos0-pos1));
            sf::Vector2f dir = (pos1-pos0)/l;
            for(int j=0 ; j<_midPoints[0].size() ; j++) {
                sf::Vector2f pos = pos0 + dir*24.f*float(j);
                pos += _midPoints[0][j]*sf::Vector2f(-dir.y, dir.x);
                _electricity[j].position = pos;
            }
            _electricity[_electricity.getVertexCount()-1].position = mpos;
        }*/

        /*for(int i=0 ; i<_midPoints.size()-1 ; i++) {
            for(int j=0 ; j<_midPoints.size() ; j++) {

            }
        }*/

        /*_electricity[0].position = _position;
        for(int i=1 ; i<_electricity.getVertexCount()-1 ; i++) {
            _electricity[i].position = _targets[i-1]->getPosition();
        }
        _electricity[_electricity.getVertexCount()-1].position = mpos;*/

        //sub elec vertexes
        _subElec.clear();
        for(int i=0 ; i<_electricity.getVertexCount()-1 ; i++) {
            sf::Vector2f pos0(_electricity[i].position);
            sf::Vector2f pos1(_electricity[i+1].position);
            float l(MathHelper::GetVecLength(pos0-pos1));
            sf::Vector2f dir((pos1-pos0)/l);
            for(float t=0 ; t<l ; t+=4) {
                sf::Vector2f pos = pos0 + t*dir;
                float lat = MathHelper::RandFloat(-5, 5);
                pos += lat*sf::Vector2f(-dir.y, dir.x);
                _subElec.append(sf::Vertex(pos, sf::Color()));
            }
        }

        //and color
        float intx = 1.f-_timeSinceShot/300.f;
        float b0 = intx*intx*255;
        float b1 = intx*255;
        for(int i=0 ; i<_electricity.getVertexCount() ; i++) {
            _electricity[i].color = sf::Color(200, 200, 255, b0);
        }
        for(int i=0 ; i<_subElec.getVertexCount() ; i++) {
            _subElec[i].color = sf::Color(100, 100, 255, b1);
        }

        if(_timeSinceShot > 300) {
            //finished shooting? clear the targets and the electricity
            _shooting = false;
            _targets.clear();
            _electricity.clear();
            _midPoints.clear();
        }
    }
}

void ElectricGun::Draw(IP& ip) {
    Weapon::Draw(ip);
    if(_shooting) {
        ip._renderer->Draw(_electricity);
        ip._renderer->Draw(_subElec);
    }
}

bool ElectricGun::Use(IP& ip, BulletManager& bManager, float angle, EntityManager& eManager, Level& level, ParticleManager& pManager) {
    if(!Weapon::Use(ip, bManager, angle, eManager, level, pManager)) {
        return false;
    }
    if(_shooting) {
        return false;
    }
    _shooting = true;
    _timeSinceShot = 0;

    //add all the enemies to a list, and begin with the closest one
    vector<Ennemy*> possibleEnemies;
    float minDist = 42000000;
    int bestId = -1;
    for(int i=0 ; i<eManager.GetNbEnnemies() ; i++) {
        Ennemy *e(eManager.GetEnnemy(i));
        float dist = MathHelper::GetVecLength(_position - e->getPosition());
        if(dist < minDist && dist < _radius) {
            minDist = dist;
            bestId = i;
        }
        possibleEnemies.push_back(e);
    }

    if(bestId != -1) {
        _targets.push_back(possibleEnemies[bestId]);

        while(possibleEnemies.size()>0) {
            Ennemy* cure(possibleEnemies[bestId]);
            //find the closest enemy from the current one
            possibleEnemies.erase(possibleEnemies.begin() + bestId);
            float minDist = 42000000;
            for(int i=0 ; i<possibleEnemies.size() ; i++) {
                Ennemy* other(possibleEnemies[i]);
                float dist = MathHelper::GetVecLength(cure->getPosition() - other->getPosition());
                if(dist < minDist) {
                    minDist = dist;
                    bestId = i;
                }
            }
            if(minDist > _radius) {
                break;
            }
            _targets.push_back(possibleEnemies[bestId]);
        }
    }

    sf::Vector2f mpos = ip._renderer->GetTexture().mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*ip._window))/4);
    //create midpoints
    if(bestId == -1) {
        _midPoints.push_back(vector<float>(GetNbPoints(_position, mpos, 24)));
    } else {
        _midPoints.push_back(vector<float>(GetNbPoints(_position, _targets[0]->getPosition(), 24)));
        for(int i=0 ; i<int(_targets.size())-1 ; i++) {
            _midPoints.push_back(vector<float>(GetNbPoints(_targets[i]->getPosition(), _targets[i+1]->getPosition(), 24)));
        }
        _midPoints.push_back(vector<float>(GetNbPoints(_targets[_targets.size()-1]->getPosition(), mpos, 24)));
    }

    //randomize them and create vertexes
    for(int i=0 ; i<_midPoints.size() ; i++) {
        for(int j=0 ; j<_midPoints[i].size() ; j++) {
            _midPoints[i][j] = MathHelper::RandFloat(-24, 24);
            if(j == 0) {
                _midPoints[i][j] = 0;
            }
            if(j == 0 && i>0 && i<_midPoints.size()) {
                _electricity.append(sf::Vertex(_targets[i-1]->getPosition(), sf::Color(255, 255, 255)));
            } else {
                _electricity.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255)));
            }
        }
    }
    _electricity.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255)));

    return true;
}

int ElectricGun::GetNbPoints(sf::Vector2f p0, sf::Vector2f p1, float dist) {
    float gdist(MathHelper::GetVecLength(p0-p1));
    return int(gdist/dist)+1;
}
