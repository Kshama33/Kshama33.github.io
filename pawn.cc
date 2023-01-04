#include "pawn.h"

Pawn::Pawn(int x, int y, Board *board, bool owner): Piece{owner ? 'P' : 'p', x, y, board, owner}, firstMove{true} {}

Pawn::~Pawn() {}

std::vector<Move> Pawn::getAllValidMoves() {
    std::vector<Move> moves;
    
    if (owner) {
        if (y > 0 && !board->at(x, y - 1)) moves.emplace_back(x, y, x, y - 1); // regular move
        if (firstMove && y > 1 && !board->at(x, y - 1) && !board->at(x, y - 2)){
            moves.emplace_back(x, y, x, y - 2); // double move
        } 
        if (x > 0 && y > 0 && board->at(x - 1, y - 1) && board->at(x - 1, y - 1)->owner != owner) moves.emplace_back(x, y, x - 1, y - 1); // left capture
        if (x < 7 && y > 0 && board->at(x + 1, y - 1) && board->at(x + 1, y - 1)->owner != owner) moves.emplace_back(x, y, x + 1, y - 1); // right capture
        if (x>0 && y>0 && enPassant()=='l'){
            moves.emplace_back(x, y, x - 1, y - 1);
        } // left capture en Passant
        if (x < 7 && y > 0 && enPassant()=='r'){
            moves.emplace_back(x, y, x + 1, y - 1);
        } // right capture en Passant
    } else {
        if (y < 7 && !board->at(x, y + 1)) moves.emplace_back(x, y, x, y + 1); // regular move
        if (firstMove && y < 6 && !board->at(x, y + 1) && !board->at(x, y + 2)){
            moves.emplace_back(x, y, x, y + 2); // double move
        } 
        if (x > 0 && y < 7 && board->at(x - 1, y + 1) && board->at(x - 1, y + 1)->owner != owner) moves.emplace_back(x, y, x - 1, y + 1); // left capture
        if (x < 7 && y < 7 && board->at(x + 1, y + 1) && board->at(x + 1, y + 1)->owner != owner) moves.emplace_back(x, y, x + 1, y + 1); // right capture
        if (x > 0 && y < 7 && enPassant()=='l'){
            moves.emplace_back(x, y, x - 1, y + 1);
        }// left capture en Passant

        if (x < 7 && y < 7 && enPassant()=='r'){
            moves.emplace_back(x, y, x + 1, y + 1);
        } // right capture en Passant
    } 

    return moves;
}


void Pawn::move(int newX, int newY) {
    firstMove = false;

    x = newX;
    y = newY;

    if ((owner && y == 0) || (!owner && y == 7)) {
        char newType;
        while (true) {
            std::cin >> newType;
            try {
                board->promote(newX, newY, newType);
                break;
            } catch (std::out_of_range &r) {
                std::cout << r.what();
            }
        }
    }
}

char Pawn::enPassant(){
    char ch='n';
    if(x==0 || y==7){
        return ch;
    }
    if (owner){
        if (x>0 && y>0 && board->at(x-1, y - 1)==nullptr && board->at(x-1, y)){
            if(board->at(x-1,y)->getID()=='p' && board->at(x-1,y)->owner != owner){
                if(static_cast<Pawn*>(board->at(x-1,y))->double_move){
                    ch='l';
                    return ch;
                }
            }
        } // left capture en Passant
        if (x < 7 && y > 0 && board->at(x + 1, y - 1)==nullptr && board->at(x + 1, y)){
            if(board->at(x+1,y)->getID()=='p'&& board->at(x+1,y)->owner != owner){
                if(static_cast<Pawn*>(board->at(x+1,y))->double_move){
                   ch='r';
                   return ch;
                }
            }
        }// right capture en Passant 
    }else{
        if (x > 0 && y < 7 && board->at(x - 1, y + 1)==nullptr && board->at(x - 1, y)){
            if(board->at(x-1,y)->getID()=='P' && board->at(x-1,y)->owner != owner){
                if(static_cast<Pawn*>(board->at(x-1,y))->double_move){
                    ch='l';
                    return ch;
                }
            }
        }// left capture en Passant

        if (x < 7 && y < 7 && board->at(x + 1, y + 1)==nullptr && board->at(x + 1, y)){
            if(board->at(x+1,y)->getID()=='P'&& board->at(x+1,y)->owner != owner){
                if(static_cast<Pawn*>(board->at(x+1,y))->double_move){
                    ch='r';
                    return ch;
                }
            }
        } // right capture en Passant

    }
    return ch;
}
