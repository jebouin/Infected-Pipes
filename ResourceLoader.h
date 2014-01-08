#ifndef RESOURCELOADER_H_INCLUDED
#define RESOURCELOADER_H_INCLUDED

#include <map>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>



class ResourceLoader {
public:
    static void LoadTexture(std::string path, std::string name);
    static sf::Texture& GetTexture(std::string name);
    static sf::Image& GetImage(std::string name);

private:
    static std::map<std::string, sf::Texture> _textures;
    static std::map<std::string, sf::Image> _images;
};

#endif // RESOURCELOADER_H_INCLUDED
