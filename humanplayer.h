#ifndef HPLAYER_H
#define HPLAYER_H

#include <iostream>
#include <vector>
#include "player.h"

class HumanPlayer: public Player {
    public:
        HumanPlayer(bool colour, Board *b);
        void move(Move &m) override;
        bool isHuman() override;
};

#endif
