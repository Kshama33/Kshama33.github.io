#include "king.h"

using namespace std;

King::King(int x, int y, Board *board, bool owner): Piece{owner ? 'K' : 'k', x, y, board, owner} {}

King::~King() {}

std::vector<Move> King::getAllValidMoves() {
    std::vector<Move> moves;
    if(x == 4 && y == 0) {
        if(board->at(0, 0) && board->at(0, 0)->getID() == 'r' && !board->at(1, 0) && !board->at(2, 0) && !board->at(3, 0)) {
            moves.emplace_back(x, y, x-2, y);
        }
        if(board->at(7, 0) && board->at(7, 0)->getID() == 'r' && !board->at(5, 0) && !board->at(6, 0)) {
            moves.emplace_back(x, y, x+2, y);
        }
    }
    if(x == 4 && y == 7) {
        if(board->at(0, 7) && board->at(0, 7)->getID() == 'R' && !board->at(1, 7) && !board->at(2, 7) && !board->at(3, 7)) {
            moves.emplace_back(x, y, x-2, y);
        }
        if(board->at(7, 7) && board->at(7, 7)->getID() == 'R' && !board->at(5, 7) && !board->at(6, 7)) {
            moves.emplace_back(x, y, x+2, y);
        }
    }

    if (y > 0) {
        if (x > 0 && (!board->at(x - 1, y - 1) || board->at(x - 1, y - 1)->owner != owner)) moves.emplace_back(x, y, x - 1, y - 1); 
        if (!board->at(x, y - 1) || board->at(x, y - 1)->owner != owner) moves.emplace_back(x, y, x, y - 1);
        if (x < 7 && (!board->at(x + 1, y - 1) || board->at(x + 1, y - 1)->owner != owner)) moves.emplace_back(x, y, x + 1, y - 1);
    }

    if (x > 0 && (!board->at(x - 1, y) || board->at(x - 1, y)->owner != owner)) moves.emplace_back(x, y, x - 1, y); 
    if (x < 7 && (!board->at(x + 1, y) || board->at(x + 1, y)->owner != owner)) moves.emplace_back(x, y, x + 1, y);


    if (y < 7) {
        if (x > 0 && (!board->at(x - 1, y + 1) || board->at(x - 1, y + 1)->owner != owner)) moves.emplace_back(x, y, x - 1, y + 1); 
        if (!board->at(x, y + 1) || board->at(x, y + 1)->owner != owner) moves.emplace_back(x, y, x, y + 1);
        if (x < 7 && (!board->at(x + 1, y + 1) || board->at(x + 1, y + 1)->owner != owner)) moves.emplace_back(x, y, x + 1, y + 1);
    }

    return moves;
}

void King::move(int newX, int newY) {
    x = newX;
    y = newY;
}

bool King::inCheck() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->at(i, j) && board->at(i, j)->owner != owner) {
                std::vector<Move> moves = board->at(i, j)->getAllValidMoves();
                for (Move &m : moves) {
                    if (m.endX == x && m.endY == y) return true;
                }
            }
        }
    }
    return false;
}

bool King::moveResultsInCheck(Move &m) {
    Piece *s = board->at(m.startX, m.startY);
    Piece *e = board->at(m.endX, m.endY);
    board->put(m.startX, m.startY, nullptr);
    s->testMove(m.endX, m.endY);
    board->put(m.endX, m.endY, s);
    bool retval = inCheck();
    s->testMove(m.startX, m.startY);
    board->put(m.startX, m.startY, s);
    board->put(m.endX, m.endY, e);
    return retval;
}

