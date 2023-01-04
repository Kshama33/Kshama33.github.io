#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"
#include <stdexcept>

class AIPlayer: public Player {
    public:
        AIPlayer(bool colour, Board *b);
        virtual ~AIPlayer();

        bool isHuman() override;
        virtual void move(Move &m) override = 0;
};

#endif
