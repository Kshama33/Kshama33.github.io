#include "move.h"

Move::Move(int sx, int sy, int ex, int ey): startX{sx}, startY{sy}, endX{ex}, endY{ey} {};

bool Move::operator==(Move &o) {
    return (startX == o.startX && startY == o.startY && endX == o.endX && endY == o.endY);
}
