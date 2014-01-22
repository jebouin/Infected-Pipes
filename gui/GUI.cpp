#include "GUI.h"
#include "IP.h"
#include "Character.h"
#include "ResourceLoader.h"
#include "MathHelper.h"
#include "LifeBar.h"
#include "XPBar.h"
#include "LevelIndicator.h"
#include "DifficultyIndicator.h"
#include "Level.h"
#include "WaveIndicator.h"

GUI::GUI(IP& ip, Character& character, Level& level) {
    _lifeBar = new LifeBar(ip, character);
    _xpBar = new XPBar(ip, character);
    _levelIndicator = new LevelIndicator(ip, character);
    _difficultyIndicator = new DifficultyIndicator(ip, level);
    _waveIndicator = new WaveIndicator(ip);
    //_waveIndicator->AnnounceWave(ip, -42);
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
    delete _waveIndicator;
    _waveIndicator = 0;
}

void GUI::Update(IP& ip, float eTime) {
    _lifeBar->Update(ip);
    _xpBar->Update(ip);
    _levelIndicator->Update(ip);
    _difficultyIndicator->Update(ip);
    _waveIndicator->Update(ip, eTime);
}

void GUI::Draw(IP& ip) {
    _lifeBar->Draw(ip);
    _xpBar->Draw(ip);
    _levelIndicator->Draw(ip);
    _difficultyIndicator->Draw(ip);
    _waveIndicator->Draw(ip);
}

WaveIndicator& GUI::GetWaveIndicator() {
    return *_waveIndicator;
}
