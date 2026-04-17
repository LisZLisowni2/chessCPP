#ifndef UTILS_HPP
#define UTILS_HPP
#pragma once

#include <string>
#include <utility>
#include <vector>
#include "plane.hpp"
#include "move.hpp"

char getch();
void clearScreen();
std::pair<int, int> selection(Plane plane, bool isWhiteTurn);  // Handles input loop, returns chosen square
Move selectionMove(Plane plane, bool isWhiteTurn, std::vector<Move> moves);  // Returns chosen move from legal moves list, or a NONE-type move if cancelled

#endif