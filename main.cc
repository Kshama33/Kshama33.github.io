#include <iostream>
#include <string>
#include "humanplayer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "move.h"
#include "player.h"
#include "textobserver.h"
#include "graphicsobserver.h"

using namespace std;

// Turns chess move codes (e.g. c2, f5, etc.) into x-y coordinates. The function will change the x and y variables passed to it.
void getXY(string move, int &x, int &y) {
    x = move[0] - 'a';
    y = '8' - move[1];
}

Player *getPlayer(bool colour, Board *b) {
    string cmd;
    cin >> cmd;
    if (cmd == "human") {
        return new HumanPlayer{colour, b};
    } else if (cmd == "computer1") {
        return new Level1{colour, b};
    } else if (cmd == "computer2") {
        return new Level2{colour, b};
    } else if (cmd == "computer3") {
        return new Level3{colour, b};
    } else if (cmd == "computer4") {
        return new Level4{colour, b};
    } else return nullptr;
}

int main() {
    srand(time(NULL)); // get a random seed based on system time
    double wscore = 0, bscore = 0; // white and black players' scores
    bool turn = true; // white goes first by default, but we can change this in setup mode

    // Initialize board and player pointers
    Board *b = new Board;
    Player *white = nullptr;
    Player *black = nullptr;

    b->standardSetup();

    // Initialize observers
    TextObserver *tObs = new TextObserver{b, cout};
    GraphicsObserver *gObs = new GraphicsObserver{b};
    b->attach(tObs);
    b->attach(gObs);

    // Command interpreter
    string cmd;
    while (cin >> cmd) {
        if (cmd == "setup") {
            b->clear();
            b->notifyObservers();
            string cm;
            while (true) {
                cin >> cm;
                if(cm == "done"){
                    bool valid = true;

                    int whiteKings = 0;
                    int blackKings = 0;

                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            Piece *p = b->at(j, i);

                            if (p && (i == 0 || i == 7) && (p->getID() == 'p' || p->getID() == 'P')) valid = false;
                            else if (p && p->getID() == 'K') {
                                whiteKings++;
                                if (p->inCheck()) valid = false;
                            } else if (p && p->getID() == 'k') {
                                blackKings++;
                                if (p->inCheck()) valid = false;
                            }
                            if (!valid) break;
                        }
                        if (!valid) break;
                    }
                    if (whiteKings != 1 || blackKings != 1) valid = false;
                    if (!valid) cout << "Invalid board setup." << endl;
                    else break;
                } else if (cm == "+"){
                    string ch;
                    string p1;
                    int x;
                    int y;
                    cin >> ch >> p1;
                    getXY(p1, x, y);
                    if(ch=="P"){
                        b->remove(x,y);
                        b->put(x,y,new Pawn{x, y, b, true});
                    }else if(ch=="p"){
                        b->remove(x,y);
                        b->put(x,y,new Pawn{x, y, b, false});
                    }else if(ch=="R"){
                        b->remove(x,y);
                        b->put(x,y,new Rook{x, y, b, true});
                    }else if(ch=="r"){
                        b->remove(x,y);
                        b->put(x,y,new Rook{x, y, b, false});
                    }else if(ch=="K"){
                        b->remove(x,y);
                        b->put(x,y,new King{x, y, b, true});
                    }else if(ch=="k"){
                        b->remove(x,y);
                        b->put(x,y,new King{x, y, b, false});
                    }else if(ch=="Q"){
                        b->remove(x,y);
                        b->put(x,y,new Queen{x, y, b, true});
                    }else if(ch=="q"){
                        b->remove(x,y);
                        b->put(x,y,new Queen{x, y, b, false});
                    }else if(ch=="N"){
                        b->remove(x,y);
                        b->put(x,y,new Knight{x, y, b, true});
                    }else if(ch=="n"){
                        b->remove(x,y);
                        b->put(x,y,new Knight{x, y, b, false});
                    }else if(ch=="B"){
                        b->remove(x,y);
                        b->put(x,y,new Bishop{x, y, b, true});
                    }else if(ch=="b"){
                        b->remove(x,y);
                        b->put(x,y,new Bishop{x, y, b, false});
                    }
                    b->notifyObservers();
                }else if (cm=="-"){
                    string p1;
                    int x;
                    int y;
                    cin >> p1;
                    getXY(p1, x, y);
                    b->remove(x, y);
                    b->notifyObservers();
                }else if (cm=="="){
                    string colour;
                    cin>>colour;
                    if(colour=="black"){
                        turn=false;
                    }else if(colour=="white"){
                        turn=true;
                    }
                }
            } 
        } else if (cmd == "game") {
            white = getPlayer(true, b);
            black = getPlayer(false, b);
            if (white == nullptr || black == nullptr) {
                cout << "Error: Invalid input when entering player types. Game not started." << endl;
                delete white;
                white = nullptr;
                delete black;
                black = nullptr;
                continue;
            }
            bool inGame = true;

            b->notifyObservers();
            if (turn) cout << "White's turn" << endl;
            else cout << "Black's turn" << endl;
            bool inCheck = (turn ? white : black)->getAllValidMoves();
            if (inCheck && (turn ? white : black)->noMoves()) {
                if (turn) {
                    cout << "Checkmate! Black wins" << endl;
                    bscore++;
                } else {
                    cout << "Checkmate! White wins" << endl;
                    wscore++;
                }
                inGame = false;
            } else if ((turn ? white : black)->noMoves()) {
                cout << "Stalemate" << endl;
                wscore += 0.5;
                bscore += 0.5;
                inGame = false;
            } else if (inCheck) {
                if (turn) cout << "White is in check!" << endl;
                else cout << "Black is in check!" << endl;
            }

            while (inGame && cin >> cmd) {
                while (inGame) {
                    if (cmd == "move" && (turn ? white : black)->isHuman()) {
                        string startPos, endPos;
                        cin >> startPos >> endPos;
                        int sx, sy, ex, ey;
                        getXY(startPos, sx, sy);
                        getXY(endPos, ex, ey);
                        Move m{sx, sy, ex, ey};
                        try {
                            (turn ? white : black)->move(m);
                            break;
                        } catch (out_of_range &r) {
                            cout << r.what() << endl;
                            b->notifyObservers();
                        }
                    } else if (cmd == "move" && !(turn ? white : black)->isHuman()) {
                        Move m{-1, -1, -1, -1};
                        try {
                            (turn ? white : black)->move(m);
                            break;
                        } catch (out_of_range &r) {
                            cout << r.what() << endl;
                            b->notifyObservers();
                        }
                    } else if (cmd == "resign") {
                        (turn ? bscore : wscore)++;
                        inGame = false;
                        break;
                    } else if (cin.eof()) break;
                    cin >> cmd;
                }
                if (!inGame) break;
                turn = !turn;

                b->notifyObservers();
                if (turn) cout << "White's turn" << endl;
                else cout << "Black's turn" << endl;
                bool inCheck = (turn ? white : black)->getAllValidMoves();
                if (inCheck && (turn ? white : black)->noMoves()) {
                    if (turn) {
                        cout << "Checkmate! Black wins" << endl;
                        bscore++;
                    } else {
                        cout << "Checkmate! White wins" << endl;
                        wscore++;
                    }
                    inGame = false;
                } else if ((turn ? white : black)->noMoves()) {
                    cout << "Stalemate" << endl;
                    wscore += 0.5;
                    bscore += 0.5;
                    inGame = false;
                } else if (inCheck) {
                    if (turn) cout << "White is in check!" << endl;
                    else cout << "Black is in check!" << endl;
                }
            }

            // end of game
            delete white;
            white = nullptr;
            delete black;
            black = nullptr;

            // standard setup for next game
            b->standardSetup();
            turn = true;
        }
    }

    cout << "Final Score:" << endl;
    cout << "White: " << wscore << endl;
    cout << "Black: " << bscore << endl;

    b->detach(tObs);
    b->detach(gObs);
    delete tObs;
    delete gObs;
    delete b;
    delete white;
    delete black;
}
