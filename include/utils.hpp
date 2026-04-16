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
std::pair<int, int> selection(Plane plane, bool isWhiteTurn);
Move selectionMove(Plane plane, bool isWhiteTurn, std::vector<Move> moves);

#endif