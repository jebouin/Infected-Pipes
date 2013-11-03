#ifndef SHADERMANAGER_H_INCLUDED
#define SHADERMANAGER_H_INCLUDED

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();
    void Update(float eTime);
    void Draw(sf::RenderTexture& rt);
    void AddShader(sf::Shader* shader);

private:
    void Clear();

    sf::RenderTexture *_back;
    sf::RenderTexture *_front;
    sf::RenderTexture *_temp;
    vector<sf::Shader*> _shaders;
};

#endif // SHADERMANAGER_H_INCLUDED
