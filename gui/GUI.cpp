#include "GUI.h"
#include "IP.h"
#include "Character.h"
#include "TextureLoader.h"
#include "MathHelper.h"
#include "LifeBar.h"
#include "XPBar.h"

GUI::GUI(IP& ip, TextureLoader& tLoader, Character& character) {
    _lifeBar = new LifeBar(ip, character, tLoader);
    _xpBar = new XPBar(ip, character, tLoader);
}

GUI::~GUI() {
    delete _lifeBar;
    delete _xpBar;
}

void GUI::Update(IP& ip) {
    _lifeBar->Update(ip);
    _xpBar->Update(ip);
}

void GUI::Draw(IP& ip) {
    _lifeBar->Draw(ip);
    _xpBar->Draw(ip);
}
