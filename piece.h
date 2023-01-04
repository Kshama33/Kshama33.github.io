#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include "board.h"
#include "move.h"
#include "player.h"

class Board;
class Player;
class Move;

class Piece {
    protected:
        int x, y;
        Board *board;
        char id;
        std::vector<Move> getMovesInLine(int x, int xStep, int y, int yStep);
    public:
        bool owner;
        Piece(char id, int x, int y, Board *board, bool owner);
        virtual ~Piece();
        char getID();
        virtual std::vector<Move> getAllValidMoves() = 0;
        virtual void move(int newX, int newY) = 0;
        virtual void testMove(int newX, int newY);
        virtual bool inCheck();
        virtual bool moveResultsInCheck(Move &m);

};

#endif
