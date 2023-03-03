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
    std::istringstream fenStream(fenStr);
    std::string token;

    _clearBitBoards();

    U64 boardPosition = 56; // a8 == index 56
    fenStream >> token;
    for (auto currentChar : token) {
        switch (currentChar) {
            case 'p': _pieces[BLACK][PAWN] |= (ONE << boardPosition++);
                break;
            case 'r': _pieces[BLACK][ROOK] |= (ONE << boardPosition++);
                break;
            case 'n': _pieces[BLACK][KNIGHT] |= (ONE << boardPosition++);
                break;
            case 'b': _pieces[BLACK][BISHOP] |= (ONE << boardPosition++);
                break;
            case 'q': _pieces[BLACK][QUEEN] |= (ONE << boardPosition++);
                break;
            case 'k': _pieces[BLACK][KING] |= (ONE << boardPosition++);
                break;
            case 'P': _pieces[WHITE][PAWN] |= (ONE << boardPosition++);
                break;
            case 'R': _pieces[WHITE][ROOK] |= (ONE << boardPosition++);
                break;
            case 'N': _pieces[WHITE][KNIGHT] |= (ONE << boardPosition++);
                break;
            case 'B': _pieces[WHITE][BISHOP] |= (ONE << boardPosition++);
                break;
            case 'Q': _pieces[WHITE][QUEEN] |= (ONE << boardPosition++);
                break;
            case 'K': _pieces[WHITE][KING] |= (ONE << boardPosition++);
                break;
            case '/': boardPosition -= 16; // Go down one rank
                break;
            default:boardPosition += static_cast<U64>(currentChar - '0');
        }
    }

    fenStream >> token;
    _activePlayer = token == "w" ? WHITE : BLACK;

    fenStream >> token;
    _castlingRights = 0;
    for (auto currentChar : token) {
        switch (currentChar) {
            case 'K': _castlingRights |= 0x1;
                break;
            case 'Q': _castlingRights |= 0x2;
                break;
            case 'k': _castlingRights |= 0x4;
                break;
            case 'q': _castlingRights |= 0x8;
                break;
        }
    }

    fenStream >> _moveClock;
}

void Board::setStartPosition() {
    setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
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

U64 Board::getAllPieces(Color color) const {
    return _allPieces[color];
}

U64 Board::getPieces(Color color, PieceType pieceType) const {
    return _pieces[color][pieceType];
}

std::string Board::printBoard() const {
    std::string prettyString = "8 ";
    int rank = 8;
    int squaresSoFar = 0;

    U64 boardPos = 56;

    while (squaresSoFar < 64) {
        U64 square = ONE << boardPos;
        bool squareOccupied = (square & _occupied) != 0;

        if (squareOccupied) {
            if (square & _pieces[WHITE][PAWN]) prettyString += " P ";
            else if (square & _pieces[BLACK][PAWN]) prettyString += " p ";

            else if (square & _pieces[WHITE][ROOK]) prettyString += " R ";
            else if (square & _pieces[BLACK][ROOK]) prettyString += " r ";

            else if (square & _pieces[WHITE][KNIGHT]) prettyString += " N ";
            else if (square & _pieces[BLACK][KNIGHT]) prettyString += " n ";

            else if (square & _pieces[WHITE][BISHOP]) prettyString += " B ";
            else if (square & _pieces[BLACK][BISHOP]) prettyString += " b ";

            else if (square & _pieces[WHITE][QUEEN]) prettyString += " Q ";
            else if (square & _pieces[BLACK][QUEEN]) prettyString += " q ";

            else if (square & _pieces[WHITE][KING]) prettyString += " K ";
            else if (square & _pieces[BLACK][KING]) prettyString += " k ";
        } else {
            prettyString += " . ";
    }
        squaresSoFar++;

        if ((squaresSoFar % 8 == 0) && (squaresSoFar != 64)) {
            switch (squaresSoFar / 8) {
                case 1:
                    prettyString += "       ";
                    prettyString += getActivePlayer() == WHITE ? "White" : "Black";
                    prettyString += " to Move";
                    break;
                case 2:
                    prettyString +="         Half-move Clock: ";
                    prettyString += std::to_string(_moveClock);
                    break;
                case 3:
                    prettyString += "         Castling Rights: ";
                    prettyString += _castlingRights & 1 ? "K" : "";
                    prettyString += _castlingRights & 2 ? "Q" : "";
                    prettyString += _castlingRights & 4 ? "k" : "";
                    prettyString += _castlingRights & 8 ? "q" : "";
            }
            prettyString += "\n" + std::to_string(--rank) + "  ";
            boardPos -= 16;
        }
        boardPos++;
    }
    prettyString +="\n\n     A   B   C   D   E   F   G   H";
    return prettyString;
}

Color Board::getActivePlayer() const {
    return _activePlayer;
}
