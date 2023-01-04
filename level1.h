#ifndef L1PLAYER_H
#define L1PLAYER_H

#include "aiplayer.h"

class Level1: public AIPlayer {
    public:
        Level1(bool colour, Board *b);
        virtual ~Level1();

        void move(Move &m) override;
};

#endif
