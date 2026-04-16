#include "game.hpp"
#include "utils.hpp"
#include "move.hpp"
#include <iostream>
#include <vector>

std::vector<Move> Game::legalMoves(std::shared_ptr<Piece> piece) {
    std::vector<Move> moves;
    auto table = plane.getTable();
    auto pos = piece->getPosition();
    int x = pos.first;
    int y = pos.second;
    bool isWhite = piece->getIsWhite();

    auto addMove = [&](int toX, int toY, bool isCapture) {
        moves.push_back(Move(piece, {toX, toY}, isCapture));
    };

    auto multiplierMoves = [&](std::vector<std::pair<int, int>> dirs) {
        for (auto dir : dirs) {
            int multiplier = 1;
            while (true) {
                std::pair<int, int> finalPos = {x + dir.first * multiplier, y + dir.second * multiplier};
                if (!(finalPos.first <= 7 && finalPos.first >= 0 && finalPos.second <= 7 && finalPos.second >= 0)) break;
                if (plane.getTable()[finalPos.second][finalPos.first] != nullptr) {
                    if (plane.getTable()[finalPos.second][finalPos.first]->getIsWhite() != isWhite) {
                        addMove(finalPos.first, finalPos.second, true);
                    }
                    break;
                } else {
                    addMove(finalPos.first, finalPos.second, false);
                }
                multiplier++;
            }
        }
    };

    switch (piece->getType()) {
        case PieceType::PAWN: {
            int dir = piece->getIsWhite() ? -1 : 1;
            int startRank = piece->getIsWhite() ? 6 : 1;
            int endRank = isWhite ? 0 : 7;
            auto isPromoting = (y + dir == endRank);

            // Forward movement
            bool frontEmpty = table[y + dir][x] == 0;
            if (frontEmpty) {
                addMove(x, y + dir, false);
                if (isPromoting) moves.back().isPromoting = true;
                
                bool canDoubleMove = (y == startRank) && table[y + 2*dir][x] == 0;
                if (canDoubleMove)
                addMove(x, y + 2*dir, false);
            }
            
            // Diagonal captures
            if (x < 7 && table[y + dir][x + 1] != 0 && table[y + dir][x + 1]->getIsWhite() != isWhite) {
                addMove(x + 1, y + dir, true);
                if (isPromoting) moves.back().isPromoting = true;
            }
            
            if (x > 0 && table[y + dir][x - 1] != 0 && table[y + dir][x - 1]->getIsWhite() != isWhite) {
                addMove(x - 1, y + dir, true);
                if (isPromoting) moves.back().isPromoting = true;
            }
            
            // En passant
            int enPassantRank = isWhite ? 3 : 4;
            char enemyID = isWhite ? 'I' : 'i';
            auto enemyPiece = plane.pieceFromPos({x + dir, y});
            if (y == enPassantRank && enemyPiece != nullptr && enemyPiece->getID() == enemyID && enemyPiece->getIsNowMoved()) {
                addMove(x + dir, y - dir, true);
                moves.back().isEnPassant = true;
            } 
            enemyPiece = plane.pieceFromPos({x - dir, y});
            if (y == enPassantRank && enemyPiece != nullptr && enemyPiece->getID() == enemyID && enemyPiece->getIsNowMoved()) {
                addMove(x - dir, y + dir, true);
                moves.back().isEnPassant = true;
            } 
            break;
        }
        case PieceType::KNIGHT: {
            std::vector<std::pair<int, int>> dirs = {
                {2, 1},
                {2, -1},
                {-2, 1},
                {-2, -1},
                {1, 2},
                {1, -2},
                {-1, 2},
                {-1, -2}
            };

            for (auto dir : dirs) {
                std::pair<int, int> finalPos = {x + dir.first, y + dir.second};
                if (!(finalPos.first <= 7 && finalPos.first >= 0 && finalPos.second <= 7 && finalPos.second >= 0)) continue;
                if (plane.getTable()[finalPos.second][finalPos.first] != nullptr) {
                    if (plane.getTable()[finalPos.second][finalPos.first]->getIsWhite() != isWhite) {
                        addMove(finalPos.first, finalPos.second, true);
                    }
                } else {
                    addMove(finalPos.first, finalPos.second, false);
                }
            }
            break;
        }
        case PieceType::BISHOP: {
            std::vector<std::pair<int, int>> dirs = {
                {1, 1},
                {-1, -1},
                {-1, 1},
                {1, -1},
            };

            multiplierMoves(dirs);
            break;
        }
        case PieceType::ROOK: {
            std::vector<std::pair<int, int>> dirs = {
                {1, 0},
                {-1, 0},
                {0, 1},
                {0, -1},
            };

            multiplierMoves(dirs);
            break;
        }
        case PieceType::QUEEN: {
            std::vector<std::pair<int, int>> dirs = {
                {1, 0},
                {-1, 0},
                {0, 1},
                {0, -1},
                {1, 1},
                {-1, -1},
                {-1, 1},
                {1, -1},
            };

            multiplierMoves(dirs);
            break;
        }
        case PieceType::KING: {
            std::vector<std::pair<int, int>> dirs = {
                {1, 0},
                {-1, 0},
                {0, 1},
                {0, -1},
                {1, 1},
                {-1, -1},
                {-1, 1},
                {1, -1},
            };
            
            for (auto dir : dirs) {
                std::pair<int, int> finalPos = {x + dir.first, y + dir.second};
                if (!(finalPos.first <= 7 && finalPos.first >= 0 && finalPos.second <= 7 && finalPos.second >= 0)) continue;
                if (plane.getTable()[finalPos.second][finalPos.first] != nullptr) {
                    if (plane.getTable()[finalPos.second][finalPos.first]->getIsWhite() != isWhite) {
                        addMove(finalPos.first, finalPos.second, true);
                    }
                } else {
                    addMove(finalPos.first, finalPos.second, false);
                }
            }

            auto castling = [&](int xCheck, int xFinal) {
                int posY = isWhite ? 7 : 0;
                char ID = isWhite ? 'r' : 'R';
                char ID2 = isWhite ? 'k' : 'K';
                auto rookAnotherSide = plane.getTable()[posY][xCheck];
                bool isRookAnotherSide = rookAnotherSide != nullptr && rookAnotherSide->getIsWhite() == isWhite && rookAnotherSide->getID() == ID;
                auto king = plane.getTable()[posY][4];
                bool isKingNotMoved = king != nullptr && king->getID() == ID2 && !king->getIsMoved();
                bool isPathClear = true;
                if (xCheck > xFinal) {
                    for (int i = 5; i < xFinal; i++) { 
                        if (plane.getTable()[posY][i] != nullptr) { 
                            isPathClear = false;
                            break;
                        }
                    }
                } else {
                    for (int i = xFinal; i < 4; i++) { 
                        if (plane.getTable()[posY][i] != nullptr) { 
                            isPathClear = false;
                            break;
                        }
                    }
                }
                if (isRookAnotherSide && isKingNotMoved && isPathClear) { 
                    addMove(xFinal, posY, false);
                    moves.back().isCastling = true;
                }
            };

            // Short Castling
            castling(7, 6);

            // Long Castling
            castling(0, 2);
            break;
        }
        case PieceType::NONE: {
            break;
        }
    }

    return moves;
}

bool Game::checkIfIsCheck() {
    char kingCallsign = isWhiteTurn ? 'k' : 'K';
    auto kingPiece = plane.findPiece(kingCallsign);

    for (auto piece : plane.getPieces()) {
        if (piece->getIsWhite() != isWhiteTurn) {
            auto pos = piece->getPosition();
            if (plane.getTable()[pos.second][pos.first] != piece) {
                continue;
            }

            auto moves = legalMoves(piece);
            for (auto move : moves) {
                if (move.finalPos == kingPiece->getPosition()) return true;
            }
        }
    }

    return false;
}

bool Game::checkIfMoveIsSafe(Move& move) {
    auto piece = move.piece;
    auto startPos = piece->getPosition();
    int toX = move.finalPos.first;
    int toY = move.finalPos.second;

    auto capturedPiece = plane.getTable()[toY][toX];
    bool originalMoved = piece->getIsMoved();

    plane.getTable()[startPos.second][startPos.first] = nullptr;
    plane.getTable()[toY][toX] = piece;
    piece->setPosition({toX, toY});

    bool kingInDanger = checkIfIsCheck();

    plane.getTable()[startPos.second][startPos.first] = piece;
    plane.getTable()[toY][toX] = capturedPiece;
    piece->setPosition(startPos);
    piece->setIsMoved(originalMoved);

    return !kingInDanger;
}

bool Game::checkIfIsGameOver() {
    char kingCallsign = isWhiteTurn ? 'k' : 'K';
    auto kingPiece = plane.findPiece(kingCallsign);
    if (kingPiece == nullptr) return true;

    for (auto piece : plane.getPieces()) {
        if (piece->getIsWhite() == isWhiteTurn) {
            auto moves = legalMoves(piece);

            for (auto& move : moves) {
                if (checkIfMoveIsSafe(move)) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Game::isGameOver() {
    if (checkIfIsGameOver()) {
        if (checkIfIsCheck()) {
            std::cout << "Checkmate!";
        } else {
            std::cout << "Stalemate!";
        }
        return true;
    }
    return false;
}

void Game::run() {
    while (!isGameOver()) {
        auto selectedPiece = selection(*this);
        auto piece = plane.pieceFromPos(selectedPiece);
        if (piece == nullptr) continue;
        if (piece->getIsWhite() != isWhiteTurn) continue;
        auto startPos = piece->getPosition();
        auto movesRaw = legalMoves(piece);
        auto moves = std::vector<Move>();
        for (auto& move : movesRaw) {
            if (checkIfMoveIsSafe(move)) moves.push_back(move);
        }
        if (moves.size() == 0) {
            // clearScreen();
            std::cout << "No legal move. Choose another piece.\nPress any key to continue";
            getch();
            continue;
        };
        auto selectedMove = selectionMove(*this, moves);
        if (selectedMove.piece->getType() == PieceType::NONE) continue;
        plane.update(selectedMove);
        history.push_back(MoveHistory(piece, startPos, selectedMove.finalPos, selectedMove.isCapturing));
        piece->setIsMoved(true);
        piece->setIsNowMoved(true);
        isWhiteTurn = !isWhiteTurn;
    }
}