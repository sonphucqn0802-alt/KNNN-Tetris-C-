#include "AudioManager.h"

#include <iostream>

namespace {
void beep() {
    std::cout << '\a';
}
}

void AudioManager::playMove() const {}

void AudioManager::playRotate() const {}

void AudioManager::playLineClear() const {
    beep();
}

void AudioManager::playGameOver() const {
    beep();
}
