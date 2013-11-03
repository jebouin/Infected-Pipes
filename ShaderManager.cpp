#include "ShaderManager.h"

ShaderManager::ShaderManager() {
    _front = new sf::RenderTexture();
    _back = new sf::RenderTexture();
    _temp = new sf::RenderTexture();
}

ShaderManager::~ShaderManager() {
    Clear();
    delete _back;
    delete _front;
    delete _front;
    _front = 0;
    _back = 0;
    _front = 0;
}

void ShaderManager::Update(float eTime) {

}

void ShaderManager::Draw(sf::RenderTexture& rt) {
    _front->create(rt.getSize().x, rt.getSize().y);
    _back->create(rt.getSize().x, rt.getSize().y);
    _temp->create(rt.getSize().x, rt.getSize().y);
    sf::Sprite s(rt.getTexture());
    _back->clear();
    _back->draw(s);
    _back->display();

    for(int i=0 ; i<_shaders.size() ; i++) {
        /*_front->clear();
        sf::Sprite s(_back->getTexture());
        _front->draw(s, _shaders[i]);
        _front->display();

        // swap front and back buffers
        //draw front on temp
        _temp->clear();
        s = sf::Sprite(_front->getTexture());
        _temp->draw(s);
        _temp->display();

        //front on back
        _front = _back;

        //temp on back
        _back->clear();
        s = sf::Sprite(_temp->getTexture());
        _back->draw(s);
        _back->display();*/

        _temp = _front;
        _front = _back;
        _back = _temp;
    }


    s = sf::Sprite(_back->getTexture());
    rt.clear();
    rt.draw(s);
    rt.display();

    Clear();
}

void ShaderManager::AddShader(sf::Shader* shader) {
    _shaders.push_back(shader);
}

void ShaderManager::Clear() {
    for(int i=0 ; i<_shaders.size() ; i++) {
        _shaders[i] = 0;
    }
    _shaders.clear();
}
