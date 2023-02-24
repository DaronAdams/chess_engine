//
// Created by Daron Adams on 2/17/23.
//

#include "Board.h"

Board::Board() {
    setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(std::string fen) {
    setFen(fen);
}

void Board::setFen(std::string) {

}

void Board::setStartPosition() {

}

void Board::_clearBitBoards() {

}

U64 Board::getAllPieces(Color) const {
    return 0;
}

U64 Board::getPieces(Color color, PieceType pieceType) const {
    return _pieces[color][pieceType];
}
