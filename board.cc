#include <iostream>
#include <stdexcept>
#include "board.h"
#include "rook.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include "queen.h"

using namespace std;

Board::Board() {
    board = new Piece**[size];
    for (int i = 0; i < size; i++) {
        board[i] = new Piece*[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = nullptr;
        }
    }
}

// Delete the 2D board array
Board::~Board() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

void Board::move(Move &m) {
    Piece *p1 = board[m.startX][m.startY];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(board[i][j] != nullptr){
                Piece *p = board[i][j];
                if((p->getID()=='p'|| p->getID()=='P') && p->owner==p1->owner){
                    static_cast<Pawn*>(p)->double_move=false;
                }
            }
        }
    }
    if (m.startX != m.endX || m.startY != m.endY) {
        Piece *p = board[m.startX][m.startY];
        if((p->getID()=='p'||p->getID()=='P')&&(m.endY-m.startY==2 || m.startY-m.endY==2)){
            static_cast<Pawn*>(p)->double_move=true;
        }
        if((p->getID()=='p'||p->getID()=='P') && static_cast<Pawn*>(p)->enPassant()=='r'){
            delete board[m.startX+1][m.startY];
            board[m.startX+1][m.startY] = nullptr;
        }
        if ((p->getID() == 'k' || p->getID() == 'K') && (m.endX - m.startX == 2 || m.startX - m.endX == 2) && m.endY == m.startY ) {
            if (!static_cast<King*>(p)->inCheck() ){
            if (m.endX - m.startX == 2) {          
                Move m2(m.startX + 3, m.startY, m.startX + 1, m.startY);
                move(m2);
            } else if (m.startX - m.endX == 2) {
                Move m2(m.startX - 4, m.startY, m.startX - 1, m.startY);
                move(m2);
            }
            }
            
        }


        board[m.startX][m.startY] = nullptr;
        delete board[m.endX][m.endY];
        board[m.endX][m.endY] = p;
        p->move(m.endX, m.endY);

    }

    
}

bool Board::moveResultsInCapture(Move &m) {
    return (board[m.endX][m.endY] && board[m.startX][m.startY] && board[m.endX][m.endY]->owner != board[m.startX][m.startY]->owner);
}

void Board::put(int x, int y, Piece *p) {
    board[x][y] = p;
}

void Board::remove(int x, int y) {
    delete board[x][y];
    board[x][y] = nullptr;
}

Piece* Board::at(int x, int y) const {
    return board[x][y];
}

void Board::promote(int x, int y, char newType) {
    if (!board[x][y] || (board[x][y]->getID() != 'p' && board[x][y]->getID() != 'P')) throw(std::invalid_argument{"Error: Non-pawn piece selected for promotion."});
    Piece *p = nullptr;
    switch (newType) {
        case 'Q': case 'q':
            p = new Queen{x, y, this, board[x][y]->owner};
            break;
        case 'N': case 'n':
            p = new Knight{x, y, this, board[x][y]->owner};
            break;
        case 'R': case 'r':
            p = new Rook{x, y, this, board[x][y]->owner};
            break;
        case 'B': case 'b':
            p = new Bishop{x, y, this, board[x][y]->owner};
            break;
        default:
            throw(std::out_of_range{"Error: Pawn cannot be promoted to that piece type. Please enter another type: "});
    }
    delete board[x][y];
    board[x][y] = p;
}

void Board::clear() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
}

void Board::standardSetup() {
    clear();

    board[0][0] = new Rook{0, 0, this, false};
    board[1][0] = new Knight{1, 0, this, false};
    board[2][0] = new Bishop{2, 0, this, false};
    board[3][0] = new Queen{3, 0, this, false};
    board[4][0] = new King{4, 0, this, false};
    board[5][0] = new Bishop{5, 0, this, false};
    board[6][0] = new Knight{6, 0, this, false};
    board[7][0] = new Rook{7, 0, this, false};
    
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn{i, 1, this, false};
        board[i][6] = new Pawn{i, 6, this, true};
    }

    board[0][7] = new Rook{0, 7, this, true};
    board[1][7] = new Knight{1, 7, this, true};
    board[2][7] = new Bishop{2, 7, this, true};
    board[4][7] = new King{4, 7, this, true};
    board[3][7] = new Queen{3, 7, this, true};
    board[5][7] = new Bishop{5, 7, this, true};
    board[6][7] = new Knight{6, 7, this, true};
    board[7][7] = new Rook{7, 7, this, true};
}
