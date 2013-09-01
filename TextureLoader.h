#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED

#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using namespace std;

class TextureLoader {
    public:
    TextureLoader();
    ~TextureLoader();
    void AddTexture(string path, string name);
    sf::Texture& GetTexture(string name);
    sf::Image& GetImage(string name);

    private:
    map<string, sf::Texture> _textures;
    map<string, sf::Image> _images;
};

#endif // TEXTURELOADER_H_INCLUDED
