#include "knight.h"

Knight::Knight(int x, int y, Board *board, bool owner): Piece{owner ? 'N' : 'n', x, y, board, owner} {}

Knight::~Knight() {}

bool Knight::goodKnightMove(int x, int y) {
    return 0 <= x && x < 8 && 0 <= y && y < 8 && (!board->at(x, y) || board->at(x, y)->owner != owner);
}

std::vector<Move> Knight::getAllValidMoves() {
    std::vector<Move> moves;
    
    // Knight moves
    // Allow moves unless square is out of bounds or there is an allied piece on it
    if (goodKnightMove(x + 2, y + 1)) moves.emplace_back(x, y, x + 2, y + 1);
    if (goodKnightMove(x - 2, y + 1)) moves.emplace_back(x, y, x - 2, y + 1);
    if (goodKnightMove(x + 2, y - 1)) moves.emplace_back(x, y, x + 2, y - 1);
    if (goodKnightMove(x - 2, y - 1)) moves.emplace_back(x, y, x - 2, y - 1);
    if (goodKnightMove(x + 1, y + 2)) moves.emplace_back(x, y, x + 1, y + 2);
    if (goodKnightMove(x - 1, y + 2)) moves.emplace_back(x, y, x - 1, y + 2);
    if (goodKnightMove(x + 1, y - 2)) moves.emplace_back(x, y, x + 1, y - 2);
    if (goodKnightMove(x - 1, y - 2)) moves.emplace_back(x, y, x - 1, y - 2);

    return moves;
}

void Knight::move(int newX, int newY) {
    x = newX;
    y = newY;
}
