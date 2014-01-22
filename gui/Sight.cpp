#include "Sight.h"
#include "IP.h"
#include "ResourceLoader.h"
#include "MathHelper.h"
#include "Renderer.h"

Sight::Sight(IP& ip) {
    _lines.setPrimitiveType(sf::Lines);
    for(int i=0 ; i<8 ; i++) {
        _lines.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color(255, 255, 255)));
    }
}

Sight::~Sight() {

}

void Sight::Update(IP& ip) {
    sf::Vector2f mpos = sf::Vector2f(sf::Mouse::getPosition(*ip._window))/4.f;
    float time = _timer.getElapsedTime().asMilliseconds();
    for(int i=0 ; i<4 ; i++) {
        float angle = float(i)*90 + 45;
        float dist = sin(time/1000.f*PI*2.f)*5.f;
        _lines[i*2].position = mpos + MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle))*(10.f + dist);
        _lines[i*2+1].position = mpos + MathHelper::Ang2Vec(MathHelper::Deg2Rad(angle))*(20.f + dist);
    }
}

void Sight::Draw(IP& ip) {
    ip._renderer->Draw(_lines);
}
