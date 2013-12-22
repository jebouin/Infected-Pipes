#include "ResourceLoader.h"

void ResourceLoader::LoadTexture(string path, string name) {
    sf::Texture t;
    t.loadFromFile(path);
    t.setSmooth(false);
    t.setRepeated(true);
    _textures[name] = t;
    sf::Image i;
    i.loadFromFile(path);
    _images[name] = i;
    cout << name << " loaded! " << endl;
}

sf::Texture& ResourceLoader::GetTexture(string name) {
    return _textures[name];
}

sf::Image& ResourceLoader::GetImage(string name) {
    return _images[name];
}

map<string, sf::Texture> ResourceLoader::_textures;
map<string, sf::Image> ResourceLoader::_images;
