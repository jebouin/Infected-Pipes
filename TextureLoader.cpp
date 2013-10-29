#include "TextureLoader.h"
#include "IP.h"

TextureLoader::TextureLoader(IP& ip) {
    AddTexture("tileset.png", "tileset");
    AddTexture("character.png", "character");

    AddTexture("level0back.png", "level0back");
    AddTexture("level0front.png", "level0front");
    AddTexture("level1back.png", "level1back");
    AddTexture("level1front.png", "level1front");
    AddTexture("miniBoss1back.png", "miniBoss1back");
    AddTexture("miniBoss1front.png", "miniBoss1front");
    AddTexture("miniBoss2back.png", "miniBoss2back");
    AddTexture("miniBoss2front.png", "miniBoss2front");
    AddTexture("level2back.png", "level2back");
    AddTexture("level2front.png", "level2front");
    AddTexture("level3back.png", "level3back");
    AddTexture("level3front.png", "level3front");

    AddTexture("spiderock.png", "spiderock");
    AddTexture("rockWorm.png", "rockWorm");
    AddTexture("bat.png", "bat");
    AddTexture("snail.png", "snail");
    AddTexture("snowBallEnemy.png", "snowBallEnemy");
    AddTexture("slimey.png", "slimey");
    AddTexture("slime.png", "slime");
    AddTexture("wormBossBody.png", "wormBossBody");
    AddTexture("wormBossHead.png", "wormBossHead");
    AddTexture("fireBall.png", "fireBall");
    AddTexture("turtle.png", "turtle");

    AddTexture("duck.png", "duck");
    AddTexture("mouse.png", "mouse");
    AddTexture("skull.png", "skull");

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
    AddTexture("rockParticle3.png", "rockParticle3");
    AddTexture("rockParticle4.png", "rockParticle4");
    AddTexture("smokeParticle.png", "smokeParticle");
    AddTexture("featherParticle.png", "featherParticle");
    AddTexture("rockWormHead.png", "rockWormHead");
    AddTexture("rockWormBlood.png", "rockWormBlood");
    AddTexture("snailParticle.png", "snailParticle");
    AddTexture("snailParticle2.png", "snailParticle2");
    AddTexture("snowParticle.png", "snowParticle");
    AddTexture("slimeParticle.png", "slimeParticle");
    AddTexture("littleBubble.png", "littleBubble");
    AddTexture("littleRockParticle.png", "littleRockParticle");
    AddTexture("fireParticle.png", "fireParticle");
    AddTexture("fireParticle2.png", "fireParticle2");
    AddTexture("explosion.png", "explosion");
    AddTexture("emberParticle.png", "emberParticle");

    AddTexture("fir.png", "fir");
    AddTexture("moon.png", "moon");
    AddTexture("cloud.png", "cloud");
    AddTexture("stars.png", "stars");
    AddTexture("falls.png", "falls");
    AddTexture("bigFalls.png", "bigFalls");

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
