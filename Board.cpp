//
// Created by Daron Adams on 2/17/23.
//

#include <sstream>
#include "Board.h"

Board::Board() {
    setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(std::string fen) {
    setFen(fen);
}

void Board::setFen(std::string fenStr) {
    std::istringstream fenSteam(fenStr);
    std::string token;

    _clearBitBoards();

}

void Board::setStartPosition() {

}

void Board::_clearBitBoards() {
    for (Color color: {WHITE, BLACK}) {
        for (PieceType pieceType : {PAWN, KING, KNIGHT, BISHOP, QUEEN, ROOK}) {
            _pieces[color][pieceType] = EMPTY;
        }
        _allPieces[WHITE] = EMPTY;
        _allPieces[BLACK] = EMPTY;
    }
    _occupied = EMPTY;
    _enPassant = EMPTY;
}

U64 Board::getAllPieces(Color) const {
    return 0;
}

U64 Board::getPieces(Color color, PieceType pieceType) const {
    return _pieces[color][pieceType];
}
