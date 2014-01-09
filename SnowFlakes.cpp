#include "SnowFlakes.h"
#include "IP.h"
#include "Level.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "MathHelper.h"
#include "Renderer.h"

SnowFlakes::SnowFlakes(IP& ip) {
    _ssize = ip._renderer->GetSize();
    _view.setSize(sf::Vector2f(_ssize));
    _view.setCenter(sf::Vector2f(_ssize)/2.f);
    _points.setPrimitiveType(sf::Points);
    Reset(0);
}

SnowFlakes::~SnowFlakes() {

}

void SnowFlakes::Reset(int power) {
    int div = (power==0 ? 400 : (power==1 ? 100 : (power==2 ? 50 : 30)));
    float nb = _ssize.x*_ssize.y/div;
    std::cout << nb << std::endl;
    for(int i=0 ; i<nb ; i++) {
        float z = float(i%100)/50.f + 1.3f;
        sf::Vector2f pos(MathHelper::RandFloat(0, _ssize.x), MathHelper::RandFloat(0, _ssize.y));
        float b = MathHelper::RandFloat(0, 1);
        float b0 = MathHelper::Interpolate(b, 200, 255);
        float b1 = MathHelper::Interpolate(b, 120, 200);
        float alpha = 255.f - float(i%10)/10.f*255.f;
        sf::Color c(b1, b1, b0, alpha);
        switch(power) {
        case 0:
            _vels.push_back(MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(45, 135)))*MathHelper::RandFloat(.02, .04));
            break;
        case 1:
            _vels.push_back(MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(110, 160)))*MathHelper::RandFloat(.09, .15));
            break;
        case 2:
            _vels.push_back(MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(130, 150)))*MathHelper::RandFloat(.19, .23));
            break;
        case 3:
            _vels.push_back(MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(145, 160)))*MathHelper::RandFloat(.60, .64));
            break;
        }
        _basePos.push_back(pos);
        _points.append(sf::Vertex(pos, c));
    }
}

void SnowFlakes::Update(IP& ip, float eTime, Level& level, ParticleManager& pManager, sf::View& prevView) {
    for(int i=0 ; i<_vels.size() ; i++) {
        sf::Vector2f& basePos(_basePos[i]);
        sf::Vector2f& pos(_points[i].position);
        float z = float(i%100)/50.f + 1.3f;
        basePos += _vels[i]*eTime/z;

        //set the real pos, with the z pos (z pos depends on the index, optimization!)
        pos = basePos - (prevView.getCenter()/z);
        if(pos.x < 0) {
            pos.x = _ssize.x;
        }
        if(pos.x > _ssize.x) {
            pos.x = 0;
        }
        if(pos.y > _ssize.y) {
            pos.y = 0;
        }
        if(pos.y < 0) {
            pos.y = _ssize.y;
        }
        basePos = (prevView.getCenter()/z)+pos;
    }
}

void SnowFlakes::Draw(IP& ip, sf::View& prevView) {
    sf::RenderTexture& rt(ip._renderer->GetTexture());
    rt.setView(_view);
    ip._renderer->Draw(_points);
    rt.setView(prevView);
}
