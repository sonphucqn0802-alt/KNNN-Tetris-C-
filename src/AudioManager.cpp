/*
 * Cai dat viec phat nhac nen, hieu ung am thanh va dieu chinh am luong.
 */
#include "AudioManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

AudioManager::AudioManager()
    : enabled_(true) {}

void AudioManager::setEnabled(bool enabled) {
    enabled_ = enabled;
}

bool AudioManager::isEnabled() const {
    return enabled_;
}

void AudioManager::playMove() const {
    playTone(600, 20);
}

void AudioManager::playRotate() const {
    playTone(750, 25);
}

void AudioManager::playLineClear() const {
    playTone(900, 60);
}

void AudioManager::playGameOver() const {
    playTone(250, 120);
}

void AudioManager::playTone(int frequency, int durationMs) const {
    if (!enabled_) {
        return;
    }

#ifdef _WIN32
    Beep(frequency, durationMs);
#else
    (void)frequency;
    (void)durationMs;
#endif
}
