#include "level1.h"

Level1::Level1(bool colour, Board *b): AIPlayer{colour, b} {}

Level1::~Level1() {}

void Level1::move(Move &m) {
    if (validMoves.size() == 0) throw(std::out_of_range{"Error: No moves available."});
    board->move(validMoves[std::rand() % validMoves.size()]);
}
