#include "WaterField.h"
#include "IP.h"
#include "Renderer.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "MathHelper.h"

WaterField::WaterField(sf::FloatRect rect, float resolution, bool surface, bool lava, bool limited) {
    _rect = rect;
    _surface = surface;
    _nbPoints = rect.width/resolution;
    _resolution = rect.width/_nbPoints;
    _vertexes.setPrimitiveType(sf::Quads);
    _lava = lava;
    _limited = limited;

    sf::Color waterTopC(177, 181, 191, 200);
    sf::Color waterC(106, 129, 193, 80);
    sf::Color waterDownC(106, 129, 193, 80);
    sf::Color lavaTopC(183, 153, 78, 255);
    sf::Color lavaC(142, 90, 27, 255);
    sf::Color lavaDownC(142, 90, 27, 255);
    _topc = (_lava ? lavaTopC : waterTopC);
    _c = (_lava ? lavaC : waterC);
    _downc = (_lava ? lavaDownC : waterDownC);

    if(_surface) {
        for(int i=0 ; i<_nbPoints ; i++) {
            _springs.push_back(Spring{rect.height, rect.height, 0});
        }
    } else {
        vector<sf::Vector2f> corners = MathHelper::Rect2Corners(_rect);
        //sf::Color c(rand()%256, rand()%256, rand()%256, 80);
        for(int i=0 ; i<corners.size() ; i++) {
            _vertexes.append(sf::Vertex(corners[i], _c));
        }
    }
}

WaterField::~WaterField() {

}

void WaterField::Update(IP& ip, float elapsedTime, ParticleManager& pManager) {
    if(!_surface) {
        return;
    }

    const float k = _lava ? 0.01 : 0.65f;
    const float d = _lava ? .1 : 0.15f;
    const float spread = 0.2;
    for(int i=0 ; i<_nbPoints ; i++) {
        Spring& s(_springs[i]);
        float x = s._length - s._nLength;
        float acc = -k*x - d*s._velocity;
        s._velocity += acc*elapsedTime/50.f;
        s._length += s._velocity*elapsedTime/50.f;

        if(_limited) {
            if(s._length < -4) {
                s._length = -4;
                s._velocity = 0;
            }
            if(s._length > _rect.height+4) {
                s._length = _rect.height+4;
                s._velocity = 0;
            }
        }
    }

    float *rd = new float[_nbPoints];
    float *ld = new float[_nbPoints];
    float ispeed = 100;
    for(int j=0 ; j<8 ; j++) {
        for(int i=0 ; i<_springs.size() ; i++) {
            if(i > 0) {
                ld[i] = spread*(_springs[i]._length-_springs[i-1]._length);
                _springs[i-1]._velocity += ld[i]*elapsedTime/ispeed;
            }
            if(i < _springs.size()-1) {
                rd[i] = spread*(_springs[i]._length-_springs[i+1]._length);
                _springs[i+1]._velocity += rd[i]*elapsedTime/ispeed;
            }
        }
    }

    for(int i=0 ; i<_springs.size() ; i++) {
        if(i > 0) {
            _springs[i-1]._length += ld[i]*elapsedTime/ispeed;
        }
        if(i < _springs.size()-1) {
            _springs[i+1]._length += rd[i]*elapsedTime/ispeed;
        }
    }

    delete [] rd;
    delete [] ld;

    if(_lava && _surface) {
        float pps = GetRect().width/16.f;
        float particleTime = 1.f/pps;
        float t = _particleTimer.getElapsedTime().asSeconds();
        if(t >= particleTime) {
            _particleTimer.restart();
            for(int i=0 ; i<t/particleTime ; i++) {
                Particle *p = new Particle(ip, "emberParticle",
                                       sf::Vector2f(GetRect().left+MathHelper::RandFloat(0, GetRect().width), GetRect().top+MathHelper::RandFloat(0, GetRect().height)),
                                       MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-70, -110))) * MathHelper::RandFloat(0.05, 0.1),
                                       MathHelper::RandFloat(-.1, .1),
                                       MathHelper::RandFloat(4000, 20000),
                                       sf::Vector2f(1, 1),
                                       sf::Vector2f(1, 1),
                                       255,
                                       0,
                                       false,
                                       false,
                                       false,
                                       sf::IntRect(1, 1, 3, 1), rand()%2==0);
                p->SetCollideWithWater(false);
                pManager.AddParticle(p);
            }
        }
    }
}

void WaterField::Draw(IP& ip, sf::RenderTexture& rt){
   if(_surface) {
        _vertexes.clear();
        float baseY = _rect.top+_rect.height;
        for(int i=0 ; i<_nbPoints-1 ; i++) {
            float x0 = float(i)/float(_nbPoints-1)*_rect.width+_rect.left;
            float x1 = float(i+1)/float(_nbPoints-1)*_rect.width+_rect.left;
            sf::Vector2f p0 = sf::Vector2f(x0, baseY - _springs[i]._length);
            sf::Vector2f p1 = sf::Vector2f(x1, baseY - _springs[i+1]._length);

            _vertexes.append(sf::Vertex(p0, _topc));
            _vertexes.append(sf::Vertex(p1, _topc));
            _vertexes.append(sf::Vertex(sf::Vector2f(p1.x, p1.y+4), _c));
            _vertexes.append(sf::Vertex(sf::Vector2f(p0.x, p0.y+4), _c));

            _vertexes.append(sf::Vertex(sf::Vector2f(p0.x, p0.y+4), _c));
            _vertexes.append(sf::Vertex(sf::Vector2f(p1.x, p1.y+4), _c));
            _vertexes.append(sf::Vertex(sf::Vector2f(x1, baseY), _downc));
            _vertexes.append(sf::Vertex(sf::Vector2f(x0, baseY), _downc));
        }
    }

    if(_lava) {
        rt.draw(_vertexes);
    } else {
        ip._renderer->Draw(_vertexes);
    }
}

void WaterField::Splash(sf::Vector2f pos, float force, ParticleManager& pManager, IP& ip) {
    if(!_surface) {
        return;
    }
    if(pos.x < _rect.left || pos.x > _rect.left+_rect.width) {
        return;
    }

    int id = int((pos.x-_rect.left)/_rect.width*_nbPoints);
    _springs[id]._velocity = force;
    _springs[min(id+1, _nbPoints-1)]._velocity = force;

    float y = _rect.top+_rect.height - _springs[id]._length;
    if(!_lava) {
        for(int i=0 ; i<5 ; i++) {
            Particle *p = new Particle(ip, "waterParticle",
                                       sf::Vector2f(pos.x, y),
                                       MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(-70, -110))) * MathHelper::RandFloat(0.1, 0.3),
                                       0,
                                       MathHelper::RandFloat(100, 500),
                                       sf::Vector2f(1, 1),
                                       sf::Vector2f(1, 1),
                                       255,
                                       0,
                                       true,
                                       true,
                                       true,
                                       sf::IntRect(1, 1, 3, 3), false);
            p->SetCollideWithWater(false);
            pManager.AddParticle(p);
        }
    }
}

bool WaterField::IsInWater(MovingSprite& sprite) {

}

void WaterField::SetLimited(bool l) {
    _limited = l;
}

sf::FloatRect WaterField::GetRect() {
    return _rect;
}

bool WaterField::IsSurface() {
    return _surface;
}

bool WaterField::IsLava() {
    return _lava;
}

int WaterField::GetId(float x) {
    if(x < _rect.left || x > _rect.left+_rect.width) {
        return -1;
    }
    return int((x-_rect.left)/_rect.width*_nbPoints);
}

float WaterField::GetHeight(float x) {
    if(!_surface) {
        return -1;
    }
    int id = GetId(x);
    if(id == -1) {
        return -1;
    }
    return _springs[id]._length;
}

float WaterField::GetY(float x) {
    float height = GetHeight(x);
    if(height == -1) {
        return -1;
    }
    return _rect.top+_rect.height-height;
}
