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
    Quit,
    Restart
};

class InputHandler {
public:
    InputAction pollAction() const;
};
