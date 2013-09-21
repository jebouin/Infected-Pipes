#include "GUI.h"
#include "IP.h"
#include "Character.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "LifeBar.h"
#include "XPBar.h"
#include "LevelIndicator.h"
#include "Cursor.h"

GUI::GUI(IP& ip, TextureLoader& tLoader, Character& character) {
    _lifeBar = new LifeBar(ip, character, tLoader);
    _xpBar = new XPBar(ip, character, tLoader);
    _levelIndicator = new LevelIndicator(ip, character, tLoader);
    _cursor = new Cursor(ip, tLoader);
}

GUI::~GUI() {
    delete _lifeBar;
    delete _xpBar;
    delete _levelIndicator;
    delete _cursor;
}

void GUI::Update(IP& ip) {
    _lifeBar->Update(ip);
    _xpBar->Update(ip);
    _levelIndicator->Update(ip);
    _cursor->Update(ip);
}

void GUI::Draw(IP& ip) {
    _lifeBar->Draw(ip);
    _xpBar->Draw(ip);
    _levelIndicator->Draw(ip);
    _cursor->Draw(ip);
}
