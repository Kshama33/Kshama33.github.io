#include "queen.h"

Queen::Queen(int x, int y, Board *board, bool owner): Piece{owner ? 'Q' : 'q', x, y, board, owner} {}

Queen::~Queen() {}

std::vector<Move> Queen::getAllValidMoves() {
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
    line = getMovesInLine(x + 1, 1, y + 1, 1);
    moves.insert(moves.end(), line.begin(), line.end());
    line = getMovesInLine(x + 1, 1, y - 1, -1);
    moves.insert(moves.end(), line.begin(), line.end());
    line = getMovesInLine(x - 1, -1, y + 1, 1);
    moves.insert(moves.end(), line.begin(), line.end());
    line = getMovesInLine(x - 1, -1, y - 1, -1);
    moves.insert(moves.end(), line.begin(), line.end());

    return moves;
}

void Queen::move(int newX, int newY) {
    x = newX;
    y = newY;
}
