#include "GameLoop.h"

#include <algorithm>
#include <chrono>
#include <thread>

GameLoop::GameLoop()
    : rng_(std::random_device{}()),
      current_(TetrominoType::I),
      next_(randomPiece()),
      highScore_(save_.loadHighScore()),
      running_(true),
      paused_(false),
      gameOver_(false) {
    resetGame();
}

void GameLoop::run() {
    using clock = std::chrono::steady_clock;
    auto lastFall = clock::now();
    auto lastRender = clock::now();

    while (running_) {
        handleInput(input_.pollAction());

        const auto now = clock::now();
        if (!paused_ && !gameOver_ &&
            std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFall).count() >= score_.getFallDelayMs()) {
            stepDown();
            lastFall = now;
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRender).count() >= 80) {
            renderer_.draw(board_, current_, ghostPiece(), next_, score_, highScore_, paused_, gameOver_);
            lastRender = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    highScore_ = std::max(highScore_, score_.getScore());
    save_.saveHighScore(highScore_);
}

Tetromino GameLoop::randomPiece() {
    std::uniform_int_distribution<int> distribution(0, 6);
    return Tetromino(static_cast<TetrominoType>(distribution(rng_)));
}

void GameLoop::resetGame() {
    board_.reset();
    score_.reset();
    paused_ = false;
    gameOver_ = false;
    next_ = randomPiece();
    spawnPiece();
}

void GameLoop::spawnPiece() {
    current_ = next_;
    current_.setPosition(3, 0);
    next_ = randomPiece();

    if (!board_.isValidPosition(current_)) {
        gameOver_ = true;
        highScore_ = std::max(highScore_, score_.getScore());
        save_.saveHighScore(highScore_);
        audio_.playGameOver();
    }
}

void GameLoop::handleInput(InputAction action) {
    if (action == InputAction::None) {
        return;
    }

    if (action == InputAction::Quit) {
        running_ = false;
        return;
    }

    if (action == InputAction::Restart) {
        resetGame();
        return;
    }

    if (action == InputAction::Pause) {
        if (!gameOver_) {
            paused_ = !paused_;
        }
        return;
    }

    if (paused_ || gameOver_) {
        return;
    }

    switch (action) {
    case InputAction::MoveLeft:
        tryMove(-1, 0);
        break;
    case InputAction::MoveRight:
        tryMove(1, 0);
        break;
    case InputAction::SoftDrop:
        if (tryMove(0, 1)) {
            score_.addSoftDrop();
        }
        break;
    case InputAction::HardDrop:
        hardDrop();
        break;
    case InputAction::RotateClockwise:
        tryRotate(true);
        break;
    case InputAction::RotateCounterClockwise:
        tryRotate(false);
        break;
    default:
        break;
    }
}

bool GameLoop::tryMove(int dx, int dy) {
    Tetromino moved = current_;
    moved.move(dx, dy);
    if (!board_.isValidPosition(moved)) {
        return false;
    }

    current_ = moved;
    audio_.playMove();
    return true;
}

bool GameLoop::tryRotate(bool clockwise) {
    Tetromino rotated = current_;
    if (clockwise) {
        rotated.rotateClockwise();
    } else {
        rotated.rotateCounterClockwise();
    }

    const int kicks[] = {0, -1, 1, -2, 2};
    for (int kick : kicks) {
        Tetromino candidate = rotated;
        candidate.move(kick, 0);
        if (board_.isValidPosition(candidate)) {
            current_ = candidate;
            audio_.playRotate();
            return true;
        }
    }

    return false;
}

void GameLoop::hardDrop() {
    int rows = 0;
    while (tryMove(0, 1)) {
        ++rows;
    }
    score_.addHardDrop(rows);
    stepDown();
}

void GameLoop::stepDown() {
    if (tryMove(0, 1)) {
        return;
    }

    board_.lockPiece(current_);
    const int cleared = board_.clearFullLines();
    if (cleared > 0) {
        score_.addClearedLines(cleared);
        audio_.playLineClear();
    }
    spawnPiece();
}

Tetromino GameLoop::ghostPiece() const {
    Tetromino ghost = current_;
    Tetromino candidate = ghost;
    candidate.move(0, 1);
    while (board_.isValidPosition(candidate)) {
        ghost = candidate;
        candidate.move(0, 1);
    }
    return ghost;
}
