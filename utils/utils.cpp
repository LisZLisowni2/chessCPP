#include "utils.hpp"
#include "move.hpp"
#include "game.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define KEY_ENTER 10

// Import certain libraries depending on operating system
#ifdef _WIN32
    #include <conio.h>
    #define KEY_ENTER 13
#else
    #include <unistd.h>
    #include <termios.h>
#endif

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

// Get a single character from the keyboard
char getch() {
    #ifdef _WIN32
        return getch()
    #else
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        // Disable buffor display
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        // Interpretation
        if (ch == '\x1b') {
            if (getchar() == '[') {
                switch (getchar()) {
                    case 'A':
                        ch = KEY_UP;
                        break;
                    case 'B':
                        ch = KEY_DOWN;
                        break;
                    case 'C':
                        ch = KEY_RIGHT;
                        break;
                    case 'D': 
                        ch = KEY_LEFT;
                        break;
                    default:
                        ch = '\x1b';
                        break;
                }
            }
        } else {
            switch (ch) {
                case '\n': 
                    ch = KEY_ENTER;
                    break;
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    #endif
}

// Select the piece based on game state, more precisely board state
std::pair<int, int> selection(Game game) {
    int posX = 0;
    int posY = 0;

    while (true) {
        clearScreen();
        game.plane.displayHighlight(std::pair<int, int>(posX, posY));
        if (game.checkIfIsCheck()) std::cout << "Check!";
        if (game.isWhiteTurn) std::cout << "\nWhite Turn";
        else std::cout << "\nBlack Turn";
        std::cout << "\n\nSelect a piece using arrows\n";
        int ch = getch();

        switch (ch) {
            case KEY_LEFT:
                posX--;
                if (posX < 0) posX = 0;
                break;
            case KEY_RIGHT:
                posX++;
                if (posX > 7) posX = 7;
                break;
            case KEY_DOWN:
                posY++;
                if (posY > 7) posY = 7;
                break;
            case KEY_UP: 
                posY--;
                if (posY < 0) posY = 0;
                break;
            case KEY_ENTER: 
                return std::pair<int, int>(posX, posY);
        }
    }
}

// Select the move based on game state and availables moves
Move selectionMove(Game game, std::vector<Move> moves) {
    int selected = 0;

    while (true) {
        clearScreen();
        auto move = moves[selected];
        game.plane.displayHighlight(move);
        if (game.checkIfIsCheck()) std::cout << "Check!";
        if (game.isWhiteTurn) std::cout << "\nWhite Turn";
        else std::cout << "\nBlack Turn";
        std::cout << "\n\n" << selected + 1 << "/" << moves.size() << "\nSelect a move using left or right. If you want cancel, press down arrow\n";
        int ch = getch();

        switch (ch) {
            case KEY_LEFT:
                selected--;
                if (selected < 0) selected = 0;
                break;
            case KEY_RIGHT:
                selected++;
                if (selected > moves.size() - 1) selected = moves.size() - 1;
                break;
            case KEY_ENTER: return move;
            case KEY_DOWN: {
                auto cancelMove = Move(std::make_shared<Piece>(false, '-'), std::pair<int, int>(-1, -1), false);
                return cancelMove;
            };
        }
    }
}