#ifndef L4PLAYER_H
#define L4PLAYER_H

// Level 4 is basically the same as level 3, but it will take moves that end the game if it sees them.

#include "aiplayer.h"

class Level4: public AIPlayer {
    public:
        Level4(bool colour, Board *b);
        virtual ~Level4();

        void move(Move &m) override;
};

#endif
