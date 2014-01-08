#ifndef PARTICLEMANAGER_H_INCLUDED
#define PARTICLEMANAGER_H_INCLUDED

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"



class IP;
class Particle;
class Level;

class ParticleManager {
    public:
    ParticleManager();
    ~ParticleManager();
    void Update(IP& ip, float elapsedTime, Level& level);
    void DrawBack(IP& ip);
    void DrawFront(IP& ip);
    void AddParticle(Particle *p);
    int GetCount();
    Particle* GetParticle(int id);

    private:
    std::vector<Particle*> _particles;
};

#endif // PARTICLEMANAGER_H_INCLUDED
