#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include "plane.hpp"
#include "piece.hpp"
#include "move.hpp"
#include <memory>
#include <vector>

class Game {
    private:
        bool isWhiteTurn;
        std::vector<MoveHistory> history; // Ununsed currently
        Plane plane;
    public:
        Game() : isWhiteTurn(true), plane(Plane()) {};

        friend std::pair<int, int> selection(Game game);
        friend Move selectionMove(Game game, std::vector<Move> moves);
        std::vector<Move> legalMoves(std::shared_ptr<Piece> piece);
        bool checkIfIsCheck();
        bool checkIfIsGameOver();
        bool isGameOver();
        bool checkIfMoveIsSafe(Move& move);
        void run();
};

#endif