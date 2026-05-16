/*
 * Khoi dong chuong trinh va ket noi cac module chinh cua game Tetris.
 */
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

#define H 20
#define W 15

char board[H][W] = {} ;
char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

int x=4,y=0,b=1;
void gotoxy(int cx, int cy) {
    COORD c = { (SHORT)(cx * 2), (SHORT)cy };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void printCell(char ch) {
    switch (ch) {
        case '#': cout << "##"; break;
        case ' ': cout << "  "; break;

        case 'I': cout << "[]"; break;
        case 'O': cout << "()"; break;
        case 'T': cout << "<>"; break;
        case 'S': cout << "{}"; break;
        case 'Z': cout << "/\\"; break;
        case 'J': cout << "||"; break;
        case 'L': cout << "=="; break;

        default:  cout << "[]"; break;
    }
}
void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' && y+j < H)
                board[y+i][x+j] = ' ';
}
void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' )
                board[y+i][x+j] = blocks[b][i][j];
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if ((i==H-1) || (j==0) || (j == W-1)) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw() {
    gotoxy(0, 0);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printCell(board[i][j]);
        }
        cout << "\n";
    }
    COORD info = { (SHORT)(W * 2 + 2), 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "=== TETRIS ===";

    info.Y = 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "Lines : " << linesCleared << "   ";

    info.Y = 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    int level = linesCleared / 5 + 1;
    cout << "Level : " << level << "   ";

    info.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "Speed : " << speed << "ms  ";

    info.Y = 8;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "[A/D] Move";

    info.Y = 9;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "[W]   Rotate";

    info.Y = 10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "[X]   Drop";

    info.Y = 11;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
    cout << "[Q]   Quit";
}
bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;
                if ( tx<1 || tx >= W-1 || ty >= H-1) return false;
                if ( board[ty][tx] != ' ') return false;
            }
    return true;
}
// Hàm này kiểm tra dòng đầy, xóa dòng, rồi kéo các dòng phía trên xuống.
void removeLine() {
    for (int i = H-2; i > 0; i--) {
        bool full = true;

        // Kiểm tra dòng i có đầy hay không
        // Chỉ kiểm tra từ cột 1 đến W-2, không kiểm tra tường hai bên
        for (int j = 1; j < W-1; j++) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }

        // Nếu dòng đầy thì xóa dòng
        if (full) {
            for (int ii = i; ii > 0; ii--) {
                for (int j = 1; j < W-1; j++) {
                    board[ii][j] = board[ii-1][j];
                }
            }

            i++;
            linesCleared++;

            draw();
            _sleep(150);
        }
    }
}

int main()
{
    srand(time(0));
    b = rand() % 7;

    system("cls");
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c=='a' && canMove(-1,0)) x--;
            if (c=='d' && canMove(1,0) ) x++;
            if (c=='x' && canMove(0,1))  y++;
            if (c=='q') break;
        }
        if (canMove(0,1)) y++;
        else {
            block2Board();
            removeLine();
            x = 5; y = 0; b = rand() % 7;
        }
        block2Board();
        draw();
        _sleep(200);
    }
    return 0;
}