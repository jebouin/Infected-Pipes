#include "TextureLoader.h"
#include "IP.h"

TextureLoader::TextureLoader(IP& ip) {
    AddTexture("tileset.png", "tileset");
    AddTexture("character.png", "character");
    AddTexture("level0.png", "level0");
    AddTexture("level1.png", "level1");
    AddTexture("level2.png", "level2");
    AddTexture("pipe.png", "pipe");
    AddTexture("zombie.png", "zombie");
    AddTexture("spiderock.png", "spiderock");
    AddTexture("rockWorm.png", "rockWorm");
    AddTexture("nightBackground.png", "nightBackground");
    AddTexture("rockyBackground.png", "rockyBackground");
    AddTexture("blood0.png", "blood0");
    AddTexture("blood1.png", "blood1");
    AddTexture("lifeBar.png", "lifeBar");
    AddTexture("lifeBarBorder.png", "lifeBarBorder");
    AddTexture("xpBar.png", "xpBar");
    AddTexture("xpBarBorder.png", "xpBarBorder");
    AddTexture("levelIndicator.png", "levelIndicator");
    AddTexture("cursor.png", "cursor");
}

TextureLoader::~TextureLoader() {

}

void TextureLoader::AddTexture(string path, string name) {
    sf::Texture t;
    sf::Image i;
    i.loadFromFile("gfx/" + path);
    t.loadFromFile("gfx/" + path);
    t.setSmooth(false);
    _textures[name] = t;
    _images[name] = i;
}

sf::Texture& TextureLoader::GetTexture(string name) {
    return _textures[name];
}

sf::Image& TextureLoader::GetImage(string name) {
    return _images[name];
}
