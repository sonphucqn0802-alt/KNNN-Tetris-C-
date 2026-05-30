/*
 * Cai dat viec doc phim va anh xa dau vao thanh hanh dong cua nguoi choi.
 */
#include "InputHandler.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif
namespace {
#ifndef _WIN32
int readCharNonBlocking(){
    termios oldTerm{};
    if (tcgetattr(STDIN_FILENO, &oldTerm) != 0){
        return -1;
    }
    termios newTerm = oldTerm;
    newTerm.c_lflag &= static_cast<unsigned>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
    const int oldFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldFlags | O_NONBLOCK);
    const int ch = getchar();
    fcntl(STDIN_FILENO, F_SETFL, oldFlags);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
    return ch;
}
#endif
}
InputAction InputHandler::pollAction() const {
#ifdef _WIN32
    if (!_kbhit()){
        return InputAction::None;
    }
    int ch = _getch();
    if (ch == 0 || ch == 224){
        ch = _getch();
        switch (ch){
            case 72: return InputAction::RotateClockwise;
            case 75: return InputAction::MoveLeft;
            case 77: return InputAction::MoveRight;
            case 80: return InputAction::SoftDrop;
            default: return InputAction::None;
        }
    }
#else
    const int ch = readCharNonBlocking();
    if (ch < 0){
        return InputAction::None;
    }
#endif
    switch (ch){
        case 'a': case 'A': return InputAction::MoveLeft;
        case 'd': case 'D': return InputAction::MoveRight;
        case 's': case 'S': return InputAction::SoftDrop;
        case 'w': case 'W': case 'x': case 'X': return InputAction::RotateClockwise;
        case 'z': case 'Z': return InputAction::RotateCounterClockwise;
        case ' ': return InputAction::HardDrop;
        case 'p': case 'P': return InputAction::Pause;
        case 'r': case 'R': return InputAction::Restart;
        case 'q': case 'Q': case 27: return InputAction::Quit;
        default: return InputAction::None;
    }
}
