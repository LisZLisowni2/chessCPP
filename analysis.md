# Chess

Chess is a strategic board game played by two players on a 64-square chessboard using pieces.
The set consists of major/minor pieces and pawns. Each piece has a unique way of moving, a specific starting quantity on the board, and a point value.
| Piece	| Description |	Starting Quantity | Notes | Point |
| --- | --- | --- | --- | --- | 
| Pawn | The weakest unit; can only move 1 square forward. If it reaches the end (rank 1 or 8), it can promote to any piece. | 8 | Can move 2 squares on its first move. | 1 | 
| Bishop | A piece that moves exclusively diagonally. | 2 | Stays on its starting square color throughout the game. | 3 | 
| Knight | A piece that moves in an "L" shape. | 2 | The only piece capable of jumping over others. | 3 | 
| Rook | A piece that moves horizontally and vertically, but not diagonally. | 2 | Cannot jump over other pieces. | 5 | 
| Queen | The most powerful piece; moves along any axis (vertical, horizontal, diagonal). | 1 | Combines the movement of a Bishop and a Rook. | 9 | 
| King | Moves one square in any direction, including diagonally. | 1 | Cannot move into check (a square under attack). | N/A |

## Rules of the Game

### Initial Setup

![Initial setup](https://chessforkids.pl/wp-content/uploads/2025/10/1-1.png)

### Basic rules

The board is set up with a white square in the bottom-right corner. The queens start on their own color (White Queen on white, Black Queen on black).
General Rules

The goal of each player is to put the opponent's King into a position where it cannot make any move to escape capture; this is called Checkmate. If a player has no legal moves and their King is not in check, the game ends in a draw, known as Stalemate.

White always moves first. A move is considered legal if:

- The pieces move according to their specific rules and do not violate fundamental game mechanics.
- A player does not capture their own pieces.
- The King does not end up in Check (a situation where the King is under direct attack).

Players alternate turns. The game continues until checkmate, stalemate, or a draw due to insufficient material.
Special Rules
- Castling: If neither the King nor the Rook has moved yet, and the path between them is clear and not under attack, the King can move two squares toward the Rook, and the Rook hops over the King to the adjacent square.

Short castling:

![Short castling](https://upload.wikimedia.org/wikipedia/commons/0/04/SCD_castle_kingside.png)

Long castling:

![Long castling](https://upload.wikimedia.org/wikipedia/commons/0/03/SCD_castle_queenside.png)

- En Passant: A special pawn capture. If an opponent moves a pawn two squares forward and lands horizontally adjacent to your pawn (on the 4th or 5th rank), you may capture it on your very next turn as if it had only moved one square.

![En passant](https://upload.wikimedia.org/wikipedia/commons/a/ae/Ajedrez_captura_al_paso_del_peon.png)

![Gif en passant](https://www.coolmathgames.com/sites/default/files/inline-images/What%20is%20en%20passant%20Gameplay.gif)

- Promotion: When a pawn reaches the opposite end of the board (the 8th or 1st rank), it must be exchanged for any other piece (usually a Queen).

## Program Logic

### General Overview

The program will be written in C++. At the start, it will generate the board and use character casing (uppercase/lowercase) to distinguish between White and Black pieces. Moves will be recorded using Standard Chess Notation. Before every move, the system will validate its legality and display an error message if the move is invalid. It will also continuously check for Check, Checkmate, and Stalemate.
Requirements and Functionalities

- Modular program for easy addition of new parts
- Generating an 8x8 board and updating it during the game
- Performing legal moves by the player
- Checking whether the player's king is in check.
- Checking whether the player's king still exists.
- Displaying an appropriate message after the game
- Operating the game using the keyboard so that you don't have to learn chess notation
- Clear and aesthetic code
- Meaningful naming of variables and constants in English