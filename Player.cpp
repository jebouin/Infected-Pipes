#include "Player.h"
#include "IP.h"
#include "Character.h"
#include "Renderer.h"
#include "Level.h"
#include "Map.h"
#include "MathHelper.h"
#include "AnimationTable.h"
#include "ParticleManager.h"
#include "BulletManager.h"
#include "GUI.h"
#include "Camera.h"
#include "SkillTree.h"

Player::Player(IP& ip, EntityManager& eManager) {
    _character = new Character(ip);
    _character->setPosition(sf::Vector2f(48, 32));
    _camera = new Camera(sf::FloatRect(0, 0, ip._renderer->GetTexture().getSize().x, ip._renderer->GetTexture().getSize().y));
    _skillTree = new SkillTree(ip);
}

Player::~Player() {
    delete _camera;
    _camera = 0;
    delete _character;
    _character = 0;
    delete _skillTree;
    _skillTree = 0;
}

void Player::Update(IP& ip, float eTime, Level& level, EntityManager& eManager, ParticleManager& pManager, BulletManager& bManager) {
    float speed = 0.0005f;
    Map& map(level.GetMap());
    if(!_character->EnteringPipe()) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            _character->GoRight(eTime);
            _camera->GoRight();
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            _character->GoLeft(eTime);
            _camera->GoLeft();
        } else {
            if(_character->_inWater) {
                if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    _character->GetAnims().SetAnimation("idle");
                }
            } else {
                _character->GetAnims().SetAnimation("idle");
            }
            _camera->GoCenter();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _character->EnterPipe(level);
            _character->PlatformDrop(level);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            level.OpenChest(*_character, ip);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _character->Jump(level, eTime);
        } else {
            _character->StopJumping();
        }
    }

    _character->Update(ip, eTime, level, eManager, pManager, bManager, *this);
    _camera->Update(ip, eTime, level, *_character);

    ip._renderer->GetTexture().setView(*_camera);
}

void Player::Draw(IP& ip) {
    _character->Draw(ip);
}

void Player::DrawFront(IP& ip) {
    _character->DrawFront(ip);
}

sf::View& Player::GetView() {
    return *_camera;
}

Character& Player::GetCharacter() {
    return *_character;
}

SkillTree& Player::GetSkillTree() {
    return *_skillTree;
}
