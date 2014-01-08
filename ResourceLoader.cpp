#include "ResourceLoader.h"

void ResourceLoader::LoadTexture(std::string path, std::string name) {
    sf::Texture t;
    t.loadFromFile(path);
    t.setSmooth(false);
    t.setRepeated(true);
    _textures[name] = t;
    sf::Image i;
    i.loadFromFile(path);
    _images[name] = i;
    std::cout << name << " loaded! " << std::endl;
}

sf::Texture& ResourceLoader::GetTexture(std::string name) {
    return _textures[name];
}

sf::Image& ResourceLoader::GetImage(std::string name) {
    return _images[name];
}

std::map<std::string, sf::Texture> ResourceLoader::_textures;
std::map<std::string, sf::Image> ResourceLoader::_images;
