#include "level4.h"

Level4::Level4(bool colour, Board *b): AIPlayer{colour, b} {}

Level4::~Level4() {}

void Level4::move(Move &m) {
    if (validMoves.size() == 0) throw(std::out_of_range{"Error: No moves available."});
    std::vector<Move> preferred;

    // Check for game-ending moves
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
        // Do test move
        Piece *s = board->at(m.startX, m.startY);
        Piece *e = board->at(m.endX, m.endY);
        board->put(m.startX, m.startY, nullptr);
        s->testMove(m.endX, m.endY);
        board->put(m.endX, m.endY, s);

        // check if game will end (opponent has no moves)
        std::vector<Move> opponentMoves;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board->at(i, j) && board->at(i, j)->owner != colour) {
                    std::vector<Move> pm = board->at(i, j)->getAllValidMoves();
                    opponentMoves.insert(opponentMoves.end(), pm.begin(), pm.end());
                }
            }
        }

        // Undo the test move
        s->testMove(m.startX, m.startY);
        board->put(m.startX, m.startY, s);
        board->put(m.endX, m.endY, e);
        
        if (opponentMoves.size() == 0) {
            // Actually do the move
            board->move(m);
            return;
        }
    }

    // If we can find a move that allows a piece to avoid capture and doesn't open up another piece to being captured, take it
    std::vector<Move> opponentMoves;
    std::vector<Piece *> piecesInDanger;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->at(i, j) && board->at(i, j)->owner != colour) {
                std::vector<Move> pm = board->at(i, j)->getAllValidMoves();
                opponentMoves.insert(opponentMoves.end(), pm.begin(), pm.end());
            }
        }
    }
    for (Move &m: opponentMoves) if (board->moveResultsInCapture(m)) piecesInDanger.emplace_back(board->at(m.endX, m.endY));
    for (Piece *p: piecesInDanger) {
        std::vector<Move> pm = p->getAllValidMoves();
        for (Move &m: pm) {
            // Do move
            Piece *s = board->at(m.startX, m.startY);
            Piece *e = board->at(m.endX, m.endY);
            board->put(m.startX, m.startY, nullptr);
            s->testMove(m.endX, m.endY);
            board->put(m.endX, m.endY, s);

            // Check for capture avoidance
            std::vector<Move> opponentMoves2;
            std::vector<Piece *> piecesInDanger2;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board->at(i, j) && board->at(i, j)->owner != colour) {
                        std::vector<Move> pm2 = board->at(i, j)->getAllValidMoves();
                        opponentMoves2.insert(opponentMoves2.end(), pm2.begin(), pm2.end());
                    }
                }
            }
            for (Move &m: opponentMoves2) if (board->moveResultsInCapture(m)) piecesInDanger2.emplace_back(board->at(m.endX, m.endY));
            if (piecesInDanger2.size() < piecesInDanger.size()) preferred.emplace_back(m); // Only add the move if it decreases the # of pieces that could be captured

            // Undo the move
            s->testMove(m.startX, m.startY);
            board->put(m.startX, m.startY, s);
            board->put(m.endX, m.endY, e);
        }
    }
    if (preferred.size() > 0) {
        board->move(preferred[std::rand() % preferred.size()]);
        return;
    }

    // Capturing move if there's no need to avoid capture
    for (Move m: validMoves) {
        if (board->moveResultsInCapture(m)) preferred.emplace_back(m.startX, m.startY, m.endX, m.endY);
    }
    if (preferred.size() > 0) {
        board->move(preferred[std::rand() % preferred.size()]);
        return;
    }

    // Checking move if no captures are available
    for (Move m: validMoves) {
        if (enemyKing->moveResultsInCheck(m)) preferred.emplace_back(m.startX, m.startY, m.endX, m.endY);
    }
    if (preferred.size() > 0) {
        board->move(preferred[std::rand() % preferred.size()]);
        return;
    }

    // Random move if no captures or checks are available
    board->move(validMoves[std::rand() % validMoves.size()]);
}
