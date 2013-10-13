#include "WaterField.h"
#include "IP.h"
#include "Renderer.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "MathHelper.h"

WaterField::WaterField(sf::FloatRect rect, float resolution) {
    _rect = rect;
    _nbPoints = rect.width/resolution;
    _resolution = rect.width/_nbPoints;
    for(int i=0 ; i<_nbPoints ; i++) {
        _springs.push_back(Spring{rect.height, rect.height, 0});
    }
    _vertexes.setPrimitiveType(sf::Quads);
}

WaterField::~WaterField() {

}

void WaterField::Update(float elapsedTime) {
    const float k = 0.65f;
    const float d = 0.15f;
    const float spread = 0.2;
    for(int i=0 ; i<_nbPoints ; i++) {
        Spring& s(_springs[i]);
        float x = s._length - s._nLength;
        float acc = -k*x - d*s._velocity;
        s._velocity += acc*elapsedTime/50.f;
        s._length += s._velocity*elapsedTime/50.f;

        if(s._length < 0) {
            s._length = 0;
            s._velocity = 0;
        }
        if(s._length > _rect.height+12) {
            s._length = _rect.height+12;
            s._velocity = 0;
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
}

void WaterField::Draw(IP& ip){
    _vertexes.clear();

    static sf::Color topc(177, 181, 191, 200);
    static sf::Color waterc(106, 129, 193, 80);
    static sf::Color downc(106, 129, 193, 80);

    float baseY = _rect.top+_rect.height;
    for(int i=0 ; i<_nbPoints-1 ; i++) {
        float x0 = float(i)/float(_nbPoints-1)*_rect.width+_rect.left;
        float x1 = float(i+1)/float(_nbPoints-1)*_rect.width+_rect.left;
        sf::Vector2f p0 = sf::Vector2f(x0, baseY - _springs[i]._length);
        sf::Vector2f p1 = sf::Vector2f(x1, baseY - _springs[i+1]._length);

        _vertexes.append(sf::Vertex(p0, topc));
        _vertexes.append(sf::Vertex(p1, topc));
        _vertexes.append(sf::Vertex(sf::Vector2f(p1.x, p1.y+1), topc));
        _vertexes.append(sf::Vertex(sf::Vector2f(p0.x, p0.y+1), topc));

        _vertexes.append(sf::Vertex(sf::Vector2f(p0.x, p0.y+1), waterc));
        _vertexes.append(sf::Vertex(sf::Vector2f(p1.x, p1.y+1), waterc));
        _vertexes.append(sf::Vertex(sf::Vector2f(x1, baseY), downc));
        _vertexes.append(sf::Vertex(sf::Vector2f(x0, baseY), downc));
    }
    ip._renderer->Draw(_vertexes);
}

void WaterField::Splash(sf::Vector2f pos, float force, ParticleManager& pManager, IP& ip) {
    if(pos.x < _rect.left || pos.x > _rect.left+_rect.width) {
        return;
    }
    int id = int((pos.x-_rect.left)/_rect.width*_nbPoints);
    _springs[id]._velocity = force;

    float y = _rect.top+_rect.height - _springs[id]._length;
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
                                   sf::IntRect(1, 1, 3, 3));
        p->SetCollideWithWater(false);
        pManager.AddParticle(p);
    }
}

sf::FloatRect WaterField::GetRect() {
    return _rect;
}
