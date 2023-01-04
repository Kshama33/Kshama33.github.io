#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop: public Piece {
    public:
        Bishop(int x, int y, Board *board, bool owner);
        ~Bishop();
        std::vector<Move> getAllValidMoves() override;
        void move(int newX, int newY) override;
};

#endif
