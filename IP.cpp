#include "IP.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "Level.h"
#include "EntityManager.h"
#include "Player.h"
#include "Background.h"
#include "ParticleManager.h"
#include "GUI.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "MathHelper.h"
#include "ShaderManager.h"
#include "Cursor.h"
#include "SkillsMenu.h"

IP::IP() {
    _window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32), "Infected Pipes");
    //_window = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "Infected Pipes");
    //_window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Infected Pipes", sf::Style::None);
    _window->setVerticalSyncEnabled(true);
    _window->setFramerateLimit(60);
    _window->setMouseCursorVisible(false);
    _renderer = new Renderer(sf::Vector2i(sf::Vector2f(_window->getSize())/4.f));
    _sceneManager = new SceneManager(*this);

    LoadResources();

    _font.loadFromFile("font/font.ttf");
    for(int i=0 ; i<10 ; i++) {
        const sf::Glyph& g(_font.getGlyph('0'+i, 10, false));
    }
    const_cast<sf::Texture&>(_font.getTexture(8)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(16)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(24)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(32)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(48)).setSmooth(false);
    const_cast<sf::Texture&>(_font.getTexture(64)).setSmooth(false);

    _window->setActive(true);
    _cursor = new Cursor(*this);
    //_sceneManager->AddScene(new MainMenu(*this));
    _sceneManager->AddScene(new Game(*this));
    //_sceneManager->AddScene(new SkillsMenu(*this));
    _focused = true;

    while(_window->isOpen()) {
        sf::Event e;
        while(_window->pollEvent(e)) {
            if(e.type == sf::Event::Closed/* || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)*/) {
                _window->close();
            }
            if(e.type == sf::Event::LostFocus) {
                _focused = false;
            }
            if(e.type == sf::Event::GainedFocus) {
                _focused = true;
                _clock.restart();
            }
            if(e.type == sf::Event::Resized) {
                _clock.restart();
            }
        }

        Update();
        Draw();
    }
}

IP::~IP() {
    delete _window;
    _window = 0;
    delete _renderer;
    _renderer = 0;
    delete _sceneManager;
    _sceneManager = 0;
    delete _cursor;
    _cursor = 0;
}

void IP::Update() {
    float eTime = _clock.restart().asMilliseconds();
    if(eTime > 1000.f/30.f) {
        eTime = 1000.f/30.f;
    }
    _sceneManager->Update(eTime, *this);
    if(_sceneManager->GetNbScenes() < 1) {
        _window->close();
    }

    _renderer->Update(*this, eTime);
    _cursor->Update(*this);
}

void IP::Draw() {
    _window->clear();
    _renderer->Clear();

    _sceneManager->Draw(*this);
    _cursor->Draw(*this);

    _renderer->DrawToWindow(*_window, *this);
    _window->display();
}

void IP::LoadResources() {
    ResourceLoader::LoadTexture("gfx/tileset.png", "tileset");
    ResourceLoader::LoadTexture("gfx/character.png", "character");

    ResourceLoader::LoadTexture("gfx/level0back.png", "level0back");
    ResourceLoader::LoadTexture("gfx/level0front.png", "level0front");
    ResourceLoader::LoadTexture("gfx/level1back.png", "level1back");
    ResourceLoader::LoadTexture("gfx/level1front.png", "level1front");
    ResourceLoader::LoadTexture("gfx/miniBoss1back.png", "miniBoss1back");
    ResourceLoader::LoadTexture("gfx/miniBoss1front.png", "miniBoss1front");
    ResourceLoader::LoadTexture("gfx/miniBoss2back.png", "miniBoss2back");
    ResourceLoader::LoadTexture("gfx/miniBoss2front.png", "miniBoss2front");
    ResourceLoader::LoadTexture("gfx/miniBoss3back.png", "miniBoss3back");
    ResourceLoader::LoadTexture("gfx/miniBoss3front.png", "miniBoss3front");
    ResourceLoader::LoadTexture("gfx/level2back.png", "level2back");
    ResourceLoader::LoadTexture("gfx/level2front.png", "level2front");
    ResourceLoader::LoadTexture("gfx/level3back.png", "level3back");
    ResourceLoader::LoadTexture("gfx/level3front.png", "level3front");
    ResourceLoader::LoadTexture("gfx/level4back.png", "level4back");
    ResourceLoader::LoadTexture("gfx/level4front.png", "level4front");

    ResourceLoader::LoadTexture("gfx/spiderock.png", "spiderock");
    ResourceLoader::LoadTexture("gfx/rockWorm.png", "rockWorm");
    ResourceLoader::LoadTexture("gfx/bat.png", "bat");
    ResourceLoader::LoadTexture("gfx/snail.png", "snail");
    ResourceLoader::LoadTexture("gfx/snowBallEnemy.png", "snowBallEnemy");
    ResourceLoader::LoadTexture("gfx/slimey.png", "slimey");
    ResourceLoader::LoadTexture("gfx/slime.png", "slime");
    ResourceLoader::LoadTexture("gfx/wormBossBody.png", "wormBossBody");
    ResourceLoader::LoadTexture("gfx/wormBossHead.png", "wormBossHead");
    ResourceLoader::LoadTexture("gfx/fireBall.png", "fireBall");
    ResourceLoader::LoadTexture("gfx/turtle.png", "turtle");
    ResourceLoader::LoadTexture("gfx/snowMan.png", "snowMan");
    ResourceLoader::LoadTexture("gfx/fireWormBoss.png", "fireWormBoss");
    ResourceLoader::LoadTexture("gfx/fireWormBossTurret.png", "fireWormBossTurret");
    ResourceLoader::LoadTexture("gfx/fireWormBossCannon.png", "fireWormBossCannon");
    ResourceLoader::LoadTexture("gfx/fist.png", "fist");
    ResourceLoader::LoadTexture("gfx/flyingSkull.png", "flyingSkull");
    ResourceLoader::LoadTexture("gfx/missileBall.png", "missileBall");

    ResourceLoader::LoadTexture("gfx/duck.png", "duck");
    ResourceLoader::LoadTexture("gfx/mouse.png", "mouse");
    ResourceLoader::LoadTexture("gfx/skull.png", "skull");
    ResourceLoader::LoadTexture("gfx/igloo.png", "igloo");
    ResourceLoader::LoadTexture("gfx/stalactite.png", "stalactite");

    ResourceLoader::LoadTexture("gfx/pipe.png", "pipe");
    ResourceLoader::LoadTexture("gfx/zombie.png", "zombie");
    ResourceLoader::LoadTexture("gfx/nightBackground.png", "nightBackground");
    ResourceLoader::LoadTexture("gfx/rockyBackground.png", "rockyBackground");
    ResourceLoader::LoadTexture("gfx/lavaBackground.png", "lavaBackground");
    ResourceLoader::LoadTexture("gfx/lavaBackground2.png", "lavaBackground2");
    ResourceLoader::LoadTexture("gfx/iceBackground.png", "iceBackground");
    ResourceLoader::LoadTexture("gfx/iceBackground2.png", "iceBackground2");
    ResourceLoader::LoadTexture("gfx/forestBackground.png", "forestBackground");
    ResourceLoader::LoadTexture("gfx/mountainBackground.png", "mountainBackground");

    ResourceLoader::LoadTexture("gfx/lifeBar.png", "lifeBar");
    ResourceLoader::LoadTexture("gfx/lifeBarBorder.png", "lifeBarBorder");
    ResourceLoader::LoadTexture("gfx/xpBar.png", "xpBar");
    ResourceLoader::LoadTexture("gfx/xpBarBorder.png", "xpBarBorder");
    ResourceLoader::LoadTexture("gfx/levelIndicator.png", "levelIndicator");
    ResourceLoader::LoadTexture("gfx/cursor.png", "cursor");
    ResourceLoader::LoadTexture("gfx/difficultyIndicator.png", "difficultyIndicator");
    ResourceLoader::LoadTexture("gfx/chest.png", "chest");
    ResourceLoader::LoadTexture("gfx/skillIcons.png", "skillIcons");

    ResourceLoader::LoadTexture("gfx/littleRockBullet.png", "littleRockBullet");
    ResourceLoader::LoadTexture("gfx/arrow.png", "arrow");
    ResourceLoader::LoadTexture("gfx/laser.png", "laser");
    ResourceLoader::LoadTexture("gfx/fireBallBullet.png", "fireBallBullet");
    ResourceLoader::LoadTexture("gfx/bullet.png", "bullet");
    ResourceLoader::LoadTexture("gfx/snowBallBullet.png", "snowBallBullet");
    ResourceLoader::LoadTexture("gfx/grenade.png", "grenade");
    ResourceLoader::LoadTexture("gfx/dualFireBullet.png", "dualFireBullet");
    ResourceLoader::LoadTexture("gfx/boneBullet.png", "boneBullet");
    ResourceLoader::LoadTexture("gfx/missile.png", "missile");

    ResourceLoader::LoadTexture("gfx/blood0.png", "blood0");
    ResourceLoader::LoadTexture("gfx/blood1.png", "blood1");
    ResourceLoader::LoadTexture("gfx/laserParticle.png", "laserParticle");
    ResourceLoader::LoadTexture("gfx/waterParticle.png", "waterParticle");
    ResourceLoader::LoadTexture("gfx/rockParticle.png", "rockParticle");
    ResourceLoader::LoadTexture("gfx/rockParticle2.png", "rockParticle2");
    ResourceLoader::LoadTexture("gfx/rockParticle3.png", "rockParticle3");
    ResourceLoader::LoadTexture("gfx/rockParticle4.png", "rockParticle4");
    ResourceLoader::LoadTexture("gfx/smokeParticle.png", "smokeParticle");
    ResourceLoader::LoadTexture("gfx/featherParticle.png", "featherParticle");
    ResourceLoader::LoadTexture("gfx/rockWormHead.png", "rockWormHead");
    ResourceLoader::LoadTexture("gfx/rockWormBlood.png", "rockWormBlood");
    ResourceLoader::LoadTexture("gfx/snailParticle.png", "snailParticle");
    ResourceLoader::LoadTexture("gfx/snailParticle2.png", "snailParticle2");
    ResourceLoader::LoadTexture("gfx/snowParticle.png", "snowParticle");
    ResourceLoader::LoadTexture("gfx/slimeParticle.png", "slimeParticle");
    ResourceLoader::LoadTexture("gfx/littleBubble.png", "littleBubble");
    ResourceLoader::LoadTexture("gfx/littleRockParticle.png", "littleRockParticle");
    ResourceLoader::LoadTexture("gfx/fireParticle.png", "fireParticle");
    ResourceLoader::LoadTexture("gfx/fireParticle2.png", "fireParticle2");
    ResourceLoader::LoadTexture("gfx/explosion.png", "explosion");
    ResourceLoader::LoadTexture("gfx/bigExplosion.png", "bigExplosion");
    ResourceLoader::LoadTexture("gfx/emberParticle.png", "emberParticle");
    ResourceLoader::LoadTexture("gfx/turtleParticle.png", "turtleParticle");
    ResourceLoader::LoadTexture("gfx/turtleParticle2.png", "turtleParticle2");
    ResourceLoader::LoadTexture("gfx/turtleHead.png", "turtleHead");
    ResourceLoader::LoadTexture("gfx/snowFlake.png", "snowFlake");
    ResourceLoader::LoadTexture("gfx/snowSmokeParticle.png", "snowSmokeParticle");
    ResourceLoader::LoadTexture("gfx/snowRockParticle.png", "snowRockParticle");
    ResourceLoader::LoadTexture("gfx/snowRockParticle2.png", "snowRockParticle2");
    ResourceLoader::LoadTexture("gfx/fingerParticle.png", "fingerParticle");
    ResourceLoader::LoadTexture("gfx/fingerParticle2.png", "fingerParticle2");
    ResourceLoader::LoadTexture("gfx/skullParticle.png", "skullParticle");
    ResourceLoader::LoadTexture("gfx/skullParticle2.png", "skullParticle2");
    ResourceLoader::LoadTexture("gfx/skullParticle3.png", "skullParticle3");
    ResourceLoader::LoadTexture("gfx/skullParticle4.png", "skullParticle4");
    ResourceLoader::LoadTexture("gfx/skullFeather.png", "skullFeather");
    ResourceLoader::LoadTexture("gfx/skullFeather2.png", "skullFeather2");
    ResourceLoader::LoadTexture("gfx/fistUpParticle.png", "fistUpParticle");
    ResourceLoader::LoadTexture("gfx/littleImpact.png", "littleImpact");
    ResourceLoader::LoadTexture("gfx/missileSmoke.png", "missileSmoke");

    ResourceLoader::LoadTexture("gfx/fir.png", "fir");
    ResourceLoader::LoadTexture("gfx/moon.png", "moon");
    ResourceLoader::LoadTexture("gfx/cloud.png", "cloud");
    ResourceLoader::LoadTexture("gfx/stars.png", "stars");
    ResourceLoader::LoadTexture("gfx/falls.png", "falls");
    ResourceLoader::LoadTexture("gfx/bigFalls.png", "bigFalls");
    ResourceLoader::LoadTexture("gfx/title.png", "title");
    ResourceLoader::LoadTexture("gfx/clouds.png", "clouds");

    ResourceLoader::LoadTexture("gfx/arms.png", "arms");
}
