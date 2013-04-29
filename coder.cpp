#include "coder.h"

Coder::Coder(QPixmap *pm, int nx, int ny) :
  Object(pm, nx, ny) {
  facing = 0;
}

void Coder::move() {
  if (dir_ == 0){ //move left
    rotateMe(dir_);
    x_ -= 5;
    facing = 0;
  } else if (dir_ == 1){ //move up
    rotateMe(dir_);
    y_ -= 5;
    facing = 1;
  } else if (dir_ == 2){ //move right
    rotateMe(dir_);
    x_ += 5;
    facing = 2;
  } else if (dir_ == 3){ //move down
    rotateMe(dir_);
    y_ += 5;
    facing = 3;
  }
  setPos(x_, y_);
  return;
}

void Coder::rotateMe(int dir){
  if (facing == dir) return;
  else if (facing == 0){
    if(dir==1){
      rotate(90);
      x_ += pixMap_->width();
      setPos(x_,y_);
    }
    if(dir==2){
      scale(-1,1);
      x_ += pixMap_->width();
      setPos(x_,y_);
    }
    if(dir==3){
      scale(-1,1);
      x_ += pixMap_->width();
      y_ += pixMap_->width();
      setPos(x_,y_);
      rotate(-90);
    }
  }
  else if (facing == 1){
    if(dir==0){
      rotate(-90);
      x_ -= pixMap_->width();
      setPos(x_,y_);
    }
    if(dir==2){
      scale(-1,1);
      rotate(90);
    }
    if(dir==3){
      scale(-1,1);
      y_ += pixMap_->width();
      setPos(x_,y_);
    }
  }
  else if (facing == 2){
    if(dir==0){
      scale(-1,1);
      x_ -= pixMap_->width();
      setPos(x_,y_);
    }
    if(dir==1){
      scale(-1,1);
      rotate(90);
    }
    if(dir==3){
      y_ += pixMap_->width();
      setPos(x_,y_);
      rotate(-90);
    }
  }
  else if (facing == 3){
    if(dir==0){
      scale(-1,1);
      x_ -= pixMap_->width();
      y_ -= pixMap_->width();
      setPos(x_,y_);
      rotate(-90);
    }
    if(dir==1){
      scale(-1,1);
      y_ -= pixMap_->width();
      setPos(x_,y_);
    }
    if(dir==2){
      rotate(90);
      y_ -= pixMap_->width();
      setPos(x_,y_);
    }
  }
}
