#include "Animation.h"

Animation::Animation(int nbFrames, float frameTime, sf::Vector2i pos, sf::Vector2i size, bool loop) {
    _frameTime = frameTime;
    _nbFrames = nbFrames;
    _curFrame = 0;
    _pos = pos;
    _size = size;
    _loop = loop;
    _finished = false;
}

Animation::~Animation() {

}

void Animation::Update() {
    if(_loop) {
        _curFrame = int(_timer.getElapsedTime().asMilliseconds() / _frameTime) % _nbFrames;
    } else {
        _curFrame = int(_timer.getElapsedTime().asMilliseconds() / _frameTime);
        if(_curFrame >= _nbFrames) {
            _finished = true;
            _curFrame = _nbFrames -1;
        }
    }
}

void Animation::Restart() {
    _curFrame = 0;
    _timer.restart();
    _finished = false;
}

int Animation::GetCurFrame() {
    return _curFrame;
}

sf::IntRect Animation::GetRect() {
    return sf::IntRect(_pos+sf::Vector2i(_curFrame*_size.x, 0), _size);
}

bool Animation::IsFinished() {
    return _finished;
}
