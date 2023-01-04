#include "subject.h"
#include "observer.h"
#include "textobserver.h"

TextObserver::TextObserver(Subject *subj, std::ostream &out): subj{subj}, out{out} {};

void TextObserver::notify() {
    bool black = false;
    for (int i = 0; i < 8; i++) {
        out << 8 - i << ' '; // row number
        for (int j = 0; j < 8; j++) {
            if (!subj->at(j, i)) out << (black ? '_' : ' '); // default behaviour for no piece
            else out << subj->at(j, i)->getID();
            black = !black;
        }
        out << std::endl;
        black = !black;
    }
    out << std::endl;
    out << "  abcdefgh" << std::endl;
}

TextObserver::~TextObserver() {}
