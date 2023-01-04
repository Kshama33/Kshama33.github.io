#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn: public Piece {
    private:
        bool firstMove;
    public:
        bool double_move=false; 
        Pawn(int x, int y, Board *board, bool owner);
        ~Pawn();
        std::vector<Move> getAllValidMoves() override;
        void move(int x, int y) override;
        char enPassant();
};

#endif
