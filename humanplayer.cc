#include "humanplayer.h"

#include <stdexcept>

HumanPlayer::HumanPlayer(bool colour, Board *b): Player{colour, b} {}

void HumanPlayer::move(Move &m) {
    for (Move &i: validMoves) {
        if (i == m) {
            board->move(m);
            return;
        } 
    }
    throw(std::out_of_range{"Error: Invalid move."});
}

bool HumanPlayer::isHuman() {
    return true;
}
