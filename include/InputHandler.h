/**
 * @class InputHandler
 * @brief Dinh nghia giao dien doc phim va chuyen thanh hanh dong trong game.
 */
#pragma once
enum class InputAction {
    None,
    MoveLeft,
    MoveRight,
    SoftDrop,
    HardDrop,
    RotateClockwise,
    RotateCounterClockwise,
    Pause,
    Restart,
    Quit
};
class InputHandler {
    public:
    InputAction pollAction() const;
};
