#include "ParticleManager.h"
#include "IP.h"
#include "Level.h"
#include "Particle.h"
#include "Renderer.h"

ParticleManager::ParticleManager() {

}

ParticleManager::~ParticleManager() {
    for(int i=0 ; i<_particles.size() ; i++) {
        delete _particles[0];
        _particles.erase(_particles.begin());
    }
}

void ParticleManager::Update(IP& ip, float elapsedTime, Level& level) {
    for(int i=0 ; i<_particles.size() ; i++) {
        _particles[i]->Update(ip, elapsedTime, level);
        if(!_particles[i]->IsAlive()) {
            delete _particles[i];
            _particles.erase(_particles.begin() + i);
            i--;
        }
    }
}

void ParticleManager::Draw(IP& ip) {
    for(int i=0 ; i<_particles.size() ; i++) {
        ip._renderer->Draw(*_particles[i]);
    }
}

void ParticleManager::AddParticle(Particle *p) {
    _particles.push_back(p);
}

int ParticleManager::GetCount() {
    return _particles.size();
}

Particle* ParticleManager::GetParticle(int id) {
    if(id < 0 || id >= GetCount()) {
        return NULL;
    }
    return _particles[id];
}