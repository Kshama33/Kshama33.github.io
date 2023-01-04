#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "piece.h"
#include "board.h"
#include "move.h"

class Board;
class Move;
class Piece;

class Player {
    protected:
        bool colour;
        Board *board;
        std::vector<Move> validMoves;
        Piece *findKing();
    public:
        Player(bool colour, Board *b);
        virtual ~Player() = default;
        bool isWhite();
        bool getAllValidMoves();
        bool noMoves();
        virtual bool isHuman() = 0;
        virtual void move(Move &m) = 0;
};

#endif
