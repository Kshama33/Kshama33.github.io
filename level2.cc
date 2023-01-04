#include "level2.h"

Level2::Level2(bool colour, Board *b): AIPlayer{colour, b} {}

Level2::~Level2() {}

void Level2::move(Move &m) {
    if (validMoves.size() == 0) throw(std::out_of_range{"Error: No moves available."});
    std::vector<Move> preferred;

    // Capturing move is the default behaviour
    for (Move m: validMoves) {
        if (board->moveResultsInCapture(m)) preferred.emplace_back(m.startX, m.startY, m.endX, m.endY);
    }
    if (preferred.size() > 0) {
        board->move(preferred[std::rand() % preferred.size()]);
        return;
    }

    // Checking move if no captures are available
    Piece *enemyKing = nullptr;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->at(i, j) && (board->at(i, j)->getID() == 'k' || board->at(i, j)->getID() == 'K') && board->at(i, j)->owner != colour) {
                enemyKing = board->at(i, j);
                break;
            }
        }
        if (enemyKing) break;
    }
    for (Move m: validMoves) {
        if (enemyKing->moveResultsInCheck(m)) preferred.emplace_back(m.startX, m.startY, m.endX, m.endY);
    }
    if (preferred.size() > 0) {
        board->move(preferred[std::rand() % preferred.size()]);
        return;
    }

    // Random move if no captues or checks are available
    board->move(validMoves[std::rand() % validMoves.size()]);
}
