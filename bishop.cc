#include "bishop.h"

Bishop::Bishop(int x, int y, Board *board, bool owner): Piece{owner ? 'B' : 'b', x, y, board, owner} {}

Bishop::~Bishop() {}

std::vector<Move> Bishop::getAllValidMoves() {
    std::vector<Move> moves;
    std::vector<Move> line;

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

void Bishop::move(int newX, int newY) {
    x = newX;
    y = newY;
}
