#include "HealingFly.h"
#include "IP.h"
#include "Renderer.h"
#include "ResourceLoader.h"
#include "AnimationTable.h"
#include "Animation.h"
#include "Character.h"
#include "MathHelper.h"

HealingFly::HealingFly(IP& ip)
    : sf::Sprite(ResourceLoader::GetTexture("healingFly")) {
    _anims = new AnimationTable();
    _anims->AddAnimation("c", Animation(2, 1, sf::Vector2i(0, 0), sf::Vector2i(10, 8), true));
    _anims->SetAnimation("c");
    setOrigin(sf::Vector2f(5, 4));
    _vel = sf::Vector2f(0, 0);

    //heart
    _healing = false;
    _healingProgress = 0;
    _heart.setTexture(ResourceLoader::GetTexture("healingFly"));
    _heart.setTextureRect(sf::IntRect(0, 8, 7, 6));
    _heart.setOrigin(sf::Vector2f(_heart.getTextureRect().width, _heart.getTextureRect().height) / 2.f);
    _heartAnims = new AnimationTable();
    _heartAnims->AddAnimation("c", Animation(2, 200, sf::Vector2i(0, 8), sf::Vector2i(7, 6), true));
    _heartAnims->SetAnimation("c");
    NewHealingTime();

    _anims->Update();
    setTextureRect(_anims->GetRect());
    _heartAnims->Update();
    _heart.setTextureRect(_heartAnims->GetRect());
}

HealingFly::~HealingFly() {
    delete _anims;
    _anims = 0;
    delete _heartAnims;
    _heartAnims = 0;
}

void HealingFly::Update(IP& ip, float eTime, Level& level, ParticleManager& pManager, Character& character) {
    _anims->Update();
    setTextureRect(_anims->GetRect());
    _heartAnims->Update();
    _heart.setTextureRect(_heartAnims->GetRect());
    float dist = MathHelper::GetVecLength(getPosition() - character.getPosition());
    sf::Vector2f dir = -(getPosition() - character.getPosition())/dist;
    _vel += dir*dist*.000006f*eTime;
    if(_moveTimer.getElapsedTime().asMilliseconds() >= 100) {
        _moveTimer.restart();
        _vel += eTime*MathHelper::Ang2Vec(MathHelper::Deg2Rad(MathHelper::RandFloat(0, 360)))*MathHelper::RandFloat(.1, 2.)*.01f;
    }
    _vel -= _vel*.1f;

    float healingTime(_healingTimer.getElapsedTime().asMilliseconds());
    if(!_healing) {
        if(healingTime > _nextHealingTime && dist<=200) {
            _healing = true;
            _healingProgress = 0;
            _healingTimer.restart();
            NewHealingTime();
        }
    } else {
        _healingProgress = healingTime/800;
        if(_healingProgress >= 1) {
            _healing = false;
            _healingTimer.restart();
            character.SetHP(character.GetHP() + 5);
        } else {
            sf::Vector2f hpos = getPosition() + (character.getPosition() - getPosition())*_healingProgress;
            _heart.setPosition(hpos);
        }
    }

    setPosition(getPosition() + _vel*eTime);
    cout << dist << endl;
    cout << getPosition().x << " " << getPosition().y << endl;
}

void HealingFly::Draw(IP& ip) {
    ip._renderer->Draw(*this);
    if(_healing) {
        ip._renderer->Draw(_heart);
    }
}

void HealingFly::NewHealingTime() {
    _nextHealingTime = MathHelper::RandFloat(900, 1600);
}
