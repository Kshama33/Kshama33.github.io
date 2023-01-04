#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen: public Piece {
    public:
        Queen(int x, int y, Board *board, bool owner);
        ~Queen();
        std::vector<Move> getAllValidMoves() override;
        void move(int newX, int newY) override;
};

#endif
