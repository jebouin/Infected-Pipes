#include "GUI.h"
#include "IP.h"
#include "Character.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "LifeBar.h"
#include "XPBar.h"
#include "LevelIndicator.h"
#include "Cursor.h"
#include "DifficultyIndicator.h"
#include "Level.h"

GUI::GUI(IP& ip, TextureLoader& tLoader, Character& character, Level& level) {
    _lifeBar = new LifeBar(ip, character, tLoader);
    _xpBar = new XPBar(ip, character, tLoader);
    _levelIndicator = new LevelIndicator(ip, character, tLoader);
    _difficultyIndicator = new DifficultyIndicator(ip, level, tLoader);
    _cursor = new Cursor(ip, tLoader);
}

GUI::~GUI() {
    delete _lifeBar;
    _lifeBar = 0;
    delete _xpBar;
    _xpBar = 0;
    delete _levelIndicator;
    _levelIndicator = 0;
    delete _difficultyIndicator;
    _difficultyIndicator = 0;
    delete _cursor;
    _cursor = 0;
}

void GUI::Update(IP& ip) {
    _lifeBar->Update(ip);
    _xpBar->Update(ip);
    _levelIndicator->Update(ip);
    _difficultyIndicator->Update(ip);
    _cursor->Update(ip);
}

void GUI::Draw(IP& ip) {
    _lifeBar->Draw(ip);
    _xpBar->Draw(ip);
    _levelIndicator->Draw(ip);
    _difficultyIndicator->Draw(ip);
    _cursor->Draw(ip);
}
