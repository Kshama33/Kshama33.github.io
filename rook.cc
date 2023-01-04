#include "rook.h"

Rook::Rook(int x, int y, Board *board, bool owner): Piece{owner ? 'R' : 'r', x, y, board, owner} {}

Rook::~Rook() {}

std::vector<Move> Rook::getAllValidMoves() {
    std::vector<Move> moves;
    std::vector<Move> line;

    line = getMovesInLine(x + 1, 1, y, 0);
    moves.insert(moves.end(), line.begin(), line.end());
    line = getMovesInLine(x - 1, -1, y, 0);
    moves.insert(moves.end(), line.begin(), line.end());
    line = getMovesInLine(x, 0, y + 1, 1);
    moves.insert(moves.end(), line.begin(), line.end());
    line = getMovesInLine(x, 0, y - 1, -1);
    moves.insert(moves.end(), line.begin(), line.end());

    return moves;
}

void Rook::move(int newX, int newY) {
    x = newX;
    y = newY;
}
