#ifndef L2PLAYER_H
#define L2PLAYER_H

#include "aiplayer.h"

class Level2: public AIPlayer {
    public:
        Level2(bool colour, Board *b);
        virtual ~Level2();

        void move(Move &m) override;
};

#endif
