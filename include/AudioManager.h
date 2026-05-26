/*
 * Khai bao cac thanh phan dieu khien nhac nen va hieu ung am thanh.
 */
#pragma once

class AudioManager {
public:
    AudioManager();

    void setEnabled(bool enabled);
    bool isEnabled() const;

    void playMove() const;
    void playRotate() const;
    void playLineClear() const;
    void playGameOver() const;

private:
    void playTone(int frequency, int durationMs) const;

    bool enabled_;
};
