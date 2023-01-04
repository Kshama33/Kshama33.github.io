#include "piece.h"

Piece::Piece(char id, int x, int y, Board *board, bool owner):
    x{x}, y{y}, board{board}, id{id}, owner{owner} {}

std::vector<Move> Piece::getMovesInLine(int x, int xStep, int y, int yStep) {
    std::vector<Move> moves;
    int i = x;
    int j = y;

    while (i >= 0 && i < 8 && j >= 0 && j < 8) {
        if (board->at(i, j) == nullptr) moves.emplace_back(x - xStep, y - yStep, i, j); // nothing here
        else if (board->at(i, j)->owner != owner) { // can capture, but can't go past
            moves.emplace_back(x - xStep, y - yStep, i, j);
            break;
        } else break; // own piece, can't go past
        i += xStep;
        j += yStep;
    }
    
    return moves;
}

char Piece::getID() {
    return id;
}

Piece::~Piece() {}

bool Piece::inCheck() {
    return false;
}

bool Piece::moveResultsInCheck(Move &m) {
    return false;
}

void Piece::testMove(int newX, int newY) {
    x = newX;
    y = newY;
}


