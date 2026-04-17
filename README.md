# ChessCPP

A simple chess engine and game interface written in modern C++17.

![License](https://img.shields.io/badge/license-MIT-blue)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-orange)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey)

## Overview

**ChessCPP** is a cross-platform chess application featuring a terminal UI. It supports for now only human vs. human.

## Features

- Rules implementation — castling, en passant, promotion, 
- Bitboard board representation for fast move generation
- Piece-square tables for positional evaluation
- Terminal UI

## Getting Started

### Prerequisites

| Dependency | Version | Notes |
|---|---|---|
| GCC / Clang | GCC 11+ / Clang 13+ | C++17 required |

### To compile app:

Using clang:
```bash
    mkdir build
    clang++ -o build/chess -I include src/* utils/*
```

Using g++:
```bash
    mkdir build
    g++ -o build/chess -I include src/* utils/*
```

### To run app:

```bash
    ./build/chess
```

## Architecture

```
chess/
├── src/
│   ├── main.cpp            # Entry point
│   ├── game.cpp            # Handler of game
│   ├── plane.cpp           # Board representation
│   └── piece.cpp           # Piece representation
├── include/                # Public headers
└── utils/                  # Utility functions
```

## License

Distributed under the **MIT License**. See [LICENSE](LICENSE) for details.