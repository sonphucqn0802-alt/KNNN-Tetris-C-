#include "InputHandler.h"

#include <cctype>

#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif

namespace {
#ifndef _WIN32
class TerminalRawMode {
public:
    TerminalRawMode() {
        tcgetattr(STDIN_FILENO, &old_);
        termios raw = old_;
        raw.c_lflag &= static_cast<unsigned>(~(ICANON | ECHO));
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);

        oldFlags_ = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldFlags_ | O_NONBLOCK);
    }

    ~TerminalRawMode() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_);
        fcntl(STDIN_FILENO, F_SETFL, oldFlags_);
    }

private:
    termios old_{};
    int oldFlags_{};
};

TerminalRawMode& rawMode() {
    static TerminalRawMode mode;
    return mode;
}
#endif

InputAction actionFromChar(int ch) {
    switch (std::tolower(ch)) {
    case 'a':
        return InputAction::MoveLeft;
    case 'd':
        return InputAction::MoveRight;
    case 's':
        return InputAction::SoftDrop;
    case ' ':
        return InputAction::HardDrop;
    case 'w':
    case 'x':
        return InputAction::RotateClockwise;
    case 'z':
        return InputAction::RotateCounterClockwise;
    case 'p':
        return InputAction::Pause;
    case 'r':
        return InputAction::Restart;
    case 'q':
    case 27:
        return InputAction::Quit;
    default:
        return InputAction::None;
    }
}
}

InputAction InputHandler::pollAction() const {
#ifdef _WIN32
    if (!_kbhit()) {
        return InputAction::None;
    }

    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
        case 72:
            return InputAction::RotateClockwise;
        case 75:
            return InputAction::MoveLeft;
        case 77:
            return InputAction::MoveRight;
        case 80:
            return InputAction::SoftDrop;
        default:
            return InputAction::None;
        }
    }

    return actionFromChar(ch);
#else
    rawMode();

    unsigned char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) <= 0) {
        return InputAction::None;
    }

    if (ch == 27) {
        unsigned char seq[2]{};
        if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0 && seq[0] == '[') {
            switch (seq[1]) {
            case 'A':
                return InputAction::RotateClockwise;
            case 'B':
                return InputAction::SoftDrop;
            case 'C':
                return InputAction::MoveRight;
            case 'D':
                return InputAction::MoveLeft;
            default:
                return InputAction::None;
            }
        }
        return InputAction::Quit;
    }

    return actionFromChar(ch);
#endif
}
