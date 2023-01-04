#include "player.h"

Player::Player(bool colour, Board *b): colour{colour}, board{b} {}

Piece *Player::findKing() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->at(i, j) && board->at(i, j)->owner == colour && (board->at(i, j)->getID() == 'k' || board->at(i, j)->getID() == 'K')) {
                return board->at(i, j);
            }
        }
    }
    return nullptr;
}

bool Player::getAllValidMoves() {
    validMoves.clear();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->at(i, j) && board->at(i, j)->owner == colour) {
                std::vector<Move> pieceMoves = board->at(i, j)->getAllValidMoves();
                validMoves.insert(validMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    Piece *k = findKing();
    for (auto i = validMoves.begin(); i < validMoves.end();) {
        if (k->moveResultsInCheck(*i)) i = validMoves.erase(i);
        else i++;
    }

    return k->inCheck();
}

bool Player::isWhite() {
    return colour;
}

bool Player::noMoves() {
    return validMoves.size() == 0;
}
