#include "superbug.h"

SuperBug::SuperBug(QPixmap *pm, int nx, int ny) :
  Object(pm, nx, ny) {
}

void SuperBug::move() {
 if (dir_ == 0){ //move left
   x_ -= 2;
 } else if (dir_ == 1){ //move up
   y_ -= 2;
 } else if (dir_ == 2){ //move right
   x_ += 2;
  } else if (dir_ == 3){ //move down
   y_ += 2;
 } else if (dir_ == 4){ //move diagonal up and right
    x_ += 2;
    y_ -= 2;
  } else if (dir_ == 5){ //move diagonal up and left
    x_ -= 2;
    y_ -= 2;
  } else if (dir_ == 6){ //move diagonal down and right
    x_ += 2;
    y_ += 2;
  } else if (dir_ == 7){ //move diagonal down and left
    x_ -= 2;
    y_ += 2;
  }
  setPos(x_, y_);
  return;
}
