//
// Created by Daron Adams on 2/17/23.
//

#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H

#include <string>
#include "defs.h"

class Board {
public:

    /**
    * Chess board represented using bitboards
    * Maintains 12 (one for each piece type and color)
    */
    Board();

    /*
    * Creates a new board set to the given Fen string
    */
    Board(std::string);

    /*
    * Prints a board
    * White pieces upper case
    * Black pieces lower case
     */
    // std::string printBoard() const;


    /*
    * Sets the board position to the corresponding Fen string
    */
    void setFen(std::string);


    /*
     * Sets board to the standard starting position
     */
    void setStartPosition();

    /*
     * Gets all the pieces corresponding to a certain color
     * and type
     */
    U64 getPieces(Color, PieceType) const;

    /*
     * Get all pieces for that color
     */
    U64 getAllPieces(Color) const;

private:
    /*
     * Array of piece bitboard accessed by [color][piecetype]
     */
    U64 _pieces[2][6];

    /*
     * Array of piece bitboards accessed by [color]
     */
    U64 _allPieces[2];

    /*
     * Bitboard of occupied squares on the board
     */
    U64 _occupied;

    /*
     * Bitboard storing en passant square
     */
    U64 _enPassant;

    /*
     * Keeps track of the active player
     */
    Color _activePlayer = WHITE;

    /*
     * Move clock
     */
    int _moveClock;

    /*
     * Clears all bitboards
     */
    void _clearBitBoards();
};



#endif //CHESS_ENGINE_BOARD_H
