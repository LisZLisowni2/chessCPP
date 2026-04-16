#ifndef MOVE_HPP
#define MOVE_HPP
#pragma once

#include "plane.hpp"
#include "piece.hpp"
#include <memory>
#include <utility>

struct Move
{
    std::shared_ptr<Piece> piece;
    std::pair<int, int> finalPos;
    bool isCapturing;
    bool isCastling;
    bool isEnPassant;
    bool isPromoting;
    bool isCheck;

    Move(std::shared_ptr<Piece> _piece, std::pair<int, int> _finalPos, bool _isCapturing) {
        piece = _piece;
        finalPos = _finalPos;
        isCapturing = _isCapturing;
        isCastling = false;
        isEnPassant = false;
        isPromoting = false;
        isCheck = false;
    }
};

struct MoveHistory
{
    char pieceID;
    std::pair<int, int> startPos;
    std::pair<int, int> finalPos;
    bool isCapturing;

    MoveHistory(std::shared_ptr<Piece> _piece, std::pair<int, int> _startPos, std::pair<int, int> _finalPos, bool _isCapturing) {
        pieceID = _piece->getID();
        startPos = _startPos;
        finalPos = _finalPos;
        isCapturing = _isCapturing;
    }
};

#endif