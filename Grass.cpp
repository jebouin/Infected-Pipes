#include "Grass.h"
#include "IP.h"
#include "Level.h"
#include "Renderer.h"

Grass::Grass(IP& ip, Level& level) {
    _grass.setPrimitiveType(sf::Lines);
}

Grass::~Grass() {

}

void Grass::Update(IP& ip) {

}

void Grass::Draw(IP& ip) {
    ip._renderer->Draw(_grass);
}
