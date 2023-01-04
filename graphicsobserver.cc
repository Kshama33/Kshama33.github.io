#include "subject.h"
#include "observer.h"
#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(Subject *subj): subj{subj}, w{new Xwindow{680, 680}}, board{new char*[8]} {
    for (int i = 0; i < 8; i++) {
        board[i] = new char[8];
        for (int j = 0; j < 8; j++) {
            board[i][j] = '\0';
        }
    }
    notify();
}

void GraphicsObserver::notify() {
    bool black = false;
    for (int i = 0; i < 8; i++) {
        if (board[i][i] == '\0') {
            w->drawString(18, 45 + 80 * i, std::to_string((char)(8 - i)));
            w->drawString(77 + 80 * i, 665, std::string{(char)('a' + i)});
        }
        for (int j = 0; j < 8; j++) {
            if (!subj->at(j, i) && board[j][i] != ' ') {
                board[j][i] = ' ';
                w->fillRectangle(40 + 80 * j, 80 * i, 80, 80, black ? w->Orange : w->White);
            } else if (subj->at(j, i) && board[j][i] != subj->at(j, i)->getID()) {
                w->fillRectangle(40 + 80 * j, 80 * i, 80, 80, black ? w->Orange : w->White);
                w->drawString(77 + 80 * j, 45 + (80 * i), std::string{subj->at(j, i)->getID()});
                board[j][i] = subj->at(j, i)->getID();
            }
            black = !black;
        }
        black = !black;
    }
}

GraphicsObserver::~GraphicsObserver() {
    for (int i = 0; i < 8; i++) {
        delete[] board[i];
    }
    delete[] board;
    delete w;
}
