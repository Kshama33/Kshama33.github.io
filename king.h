#ifndef KING_H
#define KING_H

#include "piece.h"

class King: public Piece {
    public:
        King(int x, int y, Board *board, bool owner);
        ~King();
        std::vector<Move> getAllValidMoves() override;
        void move(int x, int y) override;
        bool inCheck() override;
        bool moveResultsInCheck(Move &m) override;


    private:
};

#endif
