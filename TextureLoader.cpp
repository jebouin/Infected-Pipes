#include "TextureLoader.h"
#include "IP.h"

TextureLoader::TextureLoader(IP& ip) {
    AddTexture("tileset.png", "tileset");
    AddTexture("character.png", "character");

    AddTexture("level0back.png", "level0back");
    AddTexture("level0front.png", "level0front");
    AddTexture("level1back.png", "level1back");
    AddTexture("level1front.png", "level1front");

    AddTexture("spiderock.png", "spiderock");
    AddTexture("rockWorm.png", "rockWorm");
    AddTexture("bat.png", "bat");
    AddTexture("snail.png", "snail");
    AddTexture("snowBallEnemy.png", "snowBallEnemy");

    AddTexture("pipe.png", "pipe");
    AddTexture("zombie.png", "zombie");
    AddTexture("nightBackground.png", "nightBackground");
    AddTexture("rockyBackground.png", "rockyBackground");
    AddTexture("lifeBar.png", "lifeBar");
    AddTexture("lifeBarBorder.png", "lifeBarBorder");
    AddTexture("xpBar.png", "xpBar");
    AddTexture("xpBarBorder.png", "xpBarBorder");
    AddTexture("levelIndicator.png", "levelIndicator");
    AddTexture("cursor.png", "cursor");
    AddTexture("difficultyIndicator.png", "difficultyIndicator");
    AddTexture("chest.png", "chest");

    AddTexture("bow.png", "bow");

    AddTexture("littleRockBullet.png", "littleRockBullet");
    AddTexture("arrow.png", "arrow");
    AddTexture("laser.png", "laser");

    AddTexture("blood0.png", "blood0");
    AddTexture("blood1.png", "blood1");
    AddTexture("laserParticle.png", "laserParticle");
    AddTexture("waterParticle.png", "waterParticle");
    AddTexture("rockParticle.png", "rockParticle");
    AddTexture("rockParticle2.png", "rockParticle2");
    AddTexture("smokeParticle.png", "smokeParticle");
    AddTexture("featherParticle.png", "featherParticle");
    AddTexture("rockWormHead.png", "rockWormHead");
    AddTexture("rockWormBlood.png", "rockWormBlood");
    AddTexture("snailParticle.png", "snailParticle");
    AddTexture("snailParticle2.png", "snailParticle2");
    AddTexture("snowParticle.png", "snowParticle");

    AddTexture("fir.png", "fir");
    AddTexture("moon.png", "moon");
    AddTexture("cloud.png", "cloud");
    AddTexture("stars.png", "stars");

    AddTexture("arms.png", "arms");
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
