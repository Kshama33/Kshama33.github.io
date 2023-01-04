#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook: public Piece {
    public:
        Rook(int x, int y, Board *board, bool owner);
        ~Rook();
        std::vector<Move> getAllValidMoves() override;
        void move(int newX, int newY) override;
};

#endif
