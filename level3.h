#ifndef L3PLAYER_H
#define L3PLAYER_H

#include "aiplayer.h"

class Level3: public AIPlayer {
    public:
        Level3(bool colour, Board *b);
        virtual ~Level3();

        void move(Move &m) override;
};

#endif
