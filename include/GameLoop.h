#pragma once

#include "AudioManager.h"
#include "Board.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "SaveManager.h"
#include "ScoreManager.h"
#include "Tetromino.h"

#include <random>

class GameLoop {
public:
    GameLoop();
    void run();

private:
    Tetromino randomPiece();
    void resetGame();
    void spawnPiece();
    void handleInput(InputAction action);
    bool tryMove(int dx, int dy);
    bool tryRotate(bool clockwise);
    void hardDrop();
    void stepDown();
    Tetromino ghostPiece() const;

    Board board_;
    ScoreManager score_;
    SaveManager save_;
    AudioManager audio_;
    InputHandler input_;
    Renderer renderer_;
    std::mt19937 rng_;

    Tetromino current_;
    Tetromino next_;
    int highScore_;
    bool running_;
    bool paused_;
    bool gameOver_;
};
