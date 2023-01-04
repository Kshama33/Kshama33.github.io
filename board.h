#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "piece.h"
#include "move.h"
#include "player.h"
#include "subject.h"

class Piece;
class Player;

class Board: public Subject {
    private:
        const int size = 8;
        Piece ***board;
    public:
        Board();
        ~Board();
        //implement the castling move

        void move(Move &m);
        bool moveResultsInCapture(Move &m);
        void put(int x, int y, Piece *p);
        void remove(int x, int y);
        Piece* at(int x, int y) const override;

        void promote(int x, int y, char newType);

        void standardSetup();
        void clear();
};

std::ostream& operator<<(std::ostream &out, Board &b);

#endif
