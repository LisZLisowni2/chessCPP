#include "piece.hpp"
#include <string>
#include <ostream>

Piece::Piece(bool _isWhite, char _id, PieceType _type, std::pair<int, int> _startPosition) {
    isWhite = _isWhite;
    identifier = _id;
    type = _type;
    position = _startPosition;
    isMoved = false;
    isNowMoved = false;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    os << piece.identifier;
    return os;
};