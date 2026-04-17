#include "plane.hpp"
#include "piece.hpp"
#include "utils.hpp"
#include "termcolor.hpp"
#include <typeinfo>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>

Plane::Plane() {
    // White pieces
    pieces.push_back(std::make_shared<Piece>(true, 'r', PieceType::ROOK, std::pair<int, int>(0, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'r', PieceType::ROOK, std::pair<int, int>(7, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'n', PieceType::KNIGHT, std::pair<int, int>(1, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'n', PieceType::KNIGHT, std::pair<int, int>(6, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'b', PieceType::BISHOP, std::pair<int, int>(2, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'b', PieceType::BISHOP, std::pair<int, int>(5, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'q', PieceType::QUEEN, std::pair<int, int>(3, 7)));
    pieces.push_back(std::make_shared<Piece>(true, 'k', PieceType::KING, std::pair<int, int>(4, 7)));
    for (int i = 0; i < 8; i++) {
        pieces.push_back(std::make_shared<Piece>(true, 'i', PieceType::PAWN, std::pair<int, int>(i, 6)));
    }
    // Black pieces
    pieces.push_back(std::make_shared<Piece>(false, 'R', PieceType::ROOK, std::pair<int, int>(0, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'R', PieceType::ROOK, std::pair<int, int>(7, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'N', PieceType::KNIGHT, std::pair<int, int>(1, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'N', PieceType::KNIGHT, std::pair<int, int>(6, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'B', PieceType::BISHOP, std::pair<int, int>(2, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'B', PieceType::BISHOP, std::pair<int, int>(5, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'Q', PieceType::QUEEN, std::pair<int, int>(3, 0)));
    pieces.push_back(std::make_shared<Piece>(false, 'K', PieceType::KING, std::pair<int, int>(4, 0)));
    for (int i = 0; i < 8; i++) {
        pieces.push_back(std::make_shared<Piece>(false, 'I', PieceType::PAWN, std::pair<int, int>(i, 1)));
    }

    for (auto& piece : pieces) {
        std::pair<int, int> pos = piece->getPosition();
        table[pos.second][pos.first] = piece;
    }
}

void Plane::display() {
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            std::cout << "    A B C D E F G H\n";
            std::cout << "    ---------------";
        }

        if (i == 9) {
            std::cout << "    ---------------\n";
            std::cout << "    A B C D E F G H";
        }

        if (i > 0 && i < 9) {
            for (int j = 0; j < 10; j++) {
                if (j == 0) {
                    std::cout << 9 - i << " | ";
                    continue;
                }
                if (j == 9) {
                    std::cout << "| " << 9 - i;
                    continue;
                }
                if (table[i - 1][j - 1] == 0) {
                    std::cout << "  ";
                    continue;
                };
                std::cout << table[i - 1][j - 1] << " ";
            }
        }
        std::cout << "\n";
    }
}

// Preview the cursor of user
void Plane::displayHighlight(std::pair<int, int> position) {
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            std::cout << "    A B C D E F G H\n";
            std::cout << "    ---------------";
        }

        if (i == 9) {
            std::cout << "    ---------------\n";
            std::cout << "    A B C D E F G H";
        }

        if (i > 0 && i < 9) {
            for (int j = 0; j < 10; j++) {
                if (j == 0) {
                    std::cout << 9 - i << " | ";
                    continue;
                }
                if (j == 9) {
                    std::cout << "| " << 9 - i;
                    continue;
                }
                
                if (table[i - 1][j - 1] == 0) {
                    if (i - 1 == position.second && j - 1 == position.first) std::cout << termcolor::on_bright_white << " " << termcolor::reset << " ";
                    else std::cout << "  ";
                    continue;
                };
                if (i - 1 == position.second && j - 1 == position.first) std::cout << termcolor::on_bright_white << *table[i - 1][j - 1] << termcolor::reset << " ";
                else std::cout << *table[i - 1][j - 1] << " ";
            }
        }
        std::cout << "\n";
    }
}

// Previews the piece at its final position without modifying board state
void Plane::displayHighlight(Move move) {
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            std::cout << "    A B C D E F G H\n";
            std::cout << "    ---------------";
        }

        if (i == 9) {
            std::cout << "    ---------------\n";
            std::cout << "    A B C D E F G H";
        }

        if (i > 0 && i < 9) {
            for (int j = 0; j < 10; j++) {
                if (j == 0) {
                    std::cout << 9 - i << " | ";
                    continue;
                }
                if (j == 9) {
                    std::cout << "| " << 9 - i;
                    continue;
                }

                if (i - 1 == move.finalPos.second && j - 1 == move.finalPos.first) std::cout << termcolor::on_bright_white << *move.piece << termcolor::reset << " ";
                else if (table[i - 1][j - 1] == 0) {
                    std::cout << "  ";
                }
                else std::cout << *table[i - 1][j - 1] << " ";
            }
        }
        std::cout << "\n";
    }
}

std::shared_ptr<Piece> Plane::pieceFromPos(std::pair<int, int> position) {
    return table[position.second][position.first];
}

// Applies move in order: handle capture → move rook if castling → 
// reset table → move piece → handle promotion → rebuild table
void Plane::update(Move move) {
    if (move.isCapturing) {
        std::shared_ptr<Piece> capturedPiece;
        if (move.isEnPassant) {
            auto isWhite = move.piece->getIsWhite();
            auto capturedPiecePos = isWhite ? std::make_pair(move.finalPos.first, move.finalPos.second + 1) : std::make_pair(move.finalPos.first, move.finalPos.second - 1);
            capturedPiece = pieceFromPos(capturedPiecePos);
        } else {
            capturedPiece = pieceFromPos(move.finalPos);
        }
        auto tempPieces = pieces;
        pieces.clear();
        auto it = std::find(tempPieces.begin(), tempPieces.end(), capturedPiece);
        for (auto piece : tempPieces) {
            if (piece != (*it)) pieces.push_back(piece);
        }
    } 

    if (move.isCastling) {
        auto isWhite = move.piece->getIsWhite();
        auto rightSideRook = pieceFromPos(isWhite ? std::make_pair(7, 7) : std::make_pair(7, 0));
        auto leftSideRook = pieceFromPos(isWhite ? std::make_pair(0, 7) : std::make_pair(0, 0));
        if (move.finalPos.first == 6) {
            rightSideRook->setPosition(isWhite ? std::make_pair(5, 7) : std::make_pair(5, 0));
        } else if (move.finalPos.first == 2) {
            leftSideRook->setPosition(isWhite ? std::make_pair(3, 7) : std::make_pair(3, 0));
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto piece = pieceFromPos({i, j});
            if (piece != nullptr) piece->setIsNowMoved(false); // Clear double-push flag from last turn; en passant is only valid immediately after
            
            table[i][j] = nullptr;
        }
    }

    move.piece->setPosition(move.finalPos);

    if (move.isPromoting) {
        auto isWhite = move.piece->getIsWhite();
        bool isTransformed = false;
        while (!isTransformed) {
            std::shared_ptr<Piece> newPiece;
            std::cout << "How to promote? Type a piece you choose\n";
            std::cout << "(Q)ueen (R)ook (B)ishop K(N)ight: ";
            char id = getch();
            switch (id) {
                case 'Q':
                case 'q': {
                    move.piece->updateType((isWhite ? 'q' : 'Q'), PieceType::QUEEN);
                    isTransformed = true;
                    break;
                }
                case 'R':
                case 'r': {
                    move.piece->updateType((isWhite ? 'r' : 'R'), PieceType::ROOK);
                    isTransformed = true;
                    break;
                }
                case 'B':
                case 'b': {
                    move.piece->updateType((isWhite ? 'b' : 'B'), PieceType::BISHOP);
                    isTransformed = true;
                    break;
                }
                case 'N':
                case 'n': {
                    move.piece->updateType((isWhite ? 'n' : 'N'), PieceType::KNIGHT);
                    isTransformed = true;
                    break;
                }
                default:
                    std::cout << "Unknown piece. Press any key to continue.";
                    getch();
            }
        }
    }
    
    for (auto& piece : pieces) {
        std::pair<int, int> pos = piece->getPosition();
        table[pos.second][pos.first] = piece;
    }
}

std::shared_ptr<Piece> Plane::findPiece(char id) {
    for (auto& p : pieces) {
        if (p->getID() == id) { 
            return p;
        }
    }

    return nullptr;
}