#include "debugger.h"

Debugger::Debugger(QPixmap *pm, int nx, int ny) :
  Object(pm, nx, ny) {
}

void Debugger::move() {
 if (dir_ == 0){ //move left
    x_ -= 10;
  } else if (dir_ == 1){ //move up
    y_ -= 10;
  } else if (dir_ == 2){ //move right
    x_ += 10;
  } else if (dir_ == 3){ //move down
    y_ += 10;
  }
  setPos(x_, y_);
  return;
}
