#pragma once

#include "Board.h"
#include "ScoreManager.h"
#include "Tetromino.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const Board& board,
              const Tetromino& current,
              const Tetromino& ghost,
              const Tetromino& next,
              const ScoreManager& score,
              int highScore,
              bool paused,
              bool gameOver) const;

private:
    void clearScreen() const;

    mutable bool firstDraw_;
};
