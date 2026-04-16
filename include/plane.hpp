#ifndef PLANE_HPP
#define PLANE_HPP
#pragma once

#include "piece.hpp"
#include "move.hpp"
#include <vector>
#include <utility>
#include <memory>

class Plane {
    private:
        std::shared_ptr<Piece> table[8][8];
        std::vector<std::shared_ptr<Piece>> pieces;
    public:
        Plane();

        void update(Move move);
        void display();
        std::shared_ptr<Piece> pieceFromPos(std::pair<int, int> position);
        void displayHighlight(std::pair<int, int> position);
        void displayHighlight(Move move);
        auto& getTable() {
            return table;
        }
        auto& getPieces() {
            return pieces;
        }
        std::shared_ptr<Piece> findPiece(char id);
};

#endif