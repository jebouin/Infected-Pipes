#ifndef RESOURCELOADER_H_INCLUDED
#define RESOURCELOADER_H_INCLUDED

#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class ResourceLoader {
public:
    static void LoadTexture(string path, string name);
    static sf::Texture& GetTexture(string name);
    static sf::Image& GetImage(string name);

private:
    static map<string, sf::Texture> _textures;
    static map<string, sf::Image> _images;
};

#endif // RESOURCELOADER_H_INCLUDED
