#include "aiplayer.h"

AIPlayer::AIPlayer(bool colour, Board *b): Player{colour, b} {}

AIPlayer::~AIPlayer() {}

bool AIPlayer::isHuman() {
    return false;
}
