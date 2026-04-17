#ifndef PIECE_HPP
#define PIECE_HPP
#pragma once

#include <string>
#include <ostream>
#include <utility>

enum PieceType {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5,
    NONE = -1
};

class Piece {
    private:
        bool isWhite;
        char identifier; // lowercase = white, uppercase = black
        PieceType type;
        std::pair<int, int> position;
        bool isMoved;      // True if this piece has moved at any point in the game (used for castling)
        bool isNowMoved;   // True only during the immediately following turn (used for en passant)
    public:
        Piece(bool _isWhite, char _id, PieceType _type = PieceType::NONE, std::pair<int, int> _startPosition = std::pair<int, int>(0, 0));

        // A copy function 
        Piece operator=(const Piece* other) {
            if (this == other) {
                return *this;
            }

            this->position = other->position;
            this->isWhite = other->isWhite;
            this->identifier = other->identifier;
            this->type = other->type;

            return *this;
        }

        // The comparision functions
        bool operator==(const Piece* other) {
            return (this->identifier == other->identifier && this->position == other->position && this->isWhite == other->isWhite);
        }

        bool operator!=(const Piece* other) {
            return !(*this == other);
        }

        // A display function
        friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

        Piece() : isWhite(false), identifier(' '), position(std::pair<int, int>(0, 0)) {};

        void setPosition(int& X, int& Y) {
            position = std::pair<int, int>(X, Y);
        }

        void setPosition(std::pair<int, int> newPos) {
            position = newPos;
        }

        std::pair<int, int> getPosition() {
            return position;
        }

        char getID() {
            return identifier;
        }

        PieceType getType() {
            return type;
        }

        bool getIsWhite() {
            return isWhite;
        }

        bool getIsMoved() {
            return isMoved;
        }

        void setIsMoved(bool value) {
            isMoved = value;
        }

        void setIsNowMoved(bool value) {
            isNowMoved = value;
        }

        bool getIsNowMoved() {
            return isNowMoved;
        }

        void updateType(char _id, PieceType _type) {
            identifier = _id;
            type = _type;
        }
};

#endif
