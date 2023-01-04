#ifndef MOVE_H
#define MOVE_H

class Move {
    public:
        Move(int sx, int sy, int ex, int ey);
        int startX, startY, endX, endY;
        bool operator==(Move &o);
};

#endif
