#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight: public Piece {
    private:
        bool goodKnightMove(int x, int y);
    public:
        Knight(int x, int y, Board *board, bool owner);
        ~Knight();
        std::vector<Move> getAllValidMoves() override;
        void move(int x, int y) override;
};

#endif
