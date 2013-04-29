#include "bluescreen.h"

Bluescreen::Bluescreen(QPixmap *pm, int nx, int ny) :
  Object(pm, nx, ny) {
  t_ = 1;
  t0_ = 0;
  ct_ = 0;
  v_ = 0;
}

void Bluescreen::move() {
  if(x_ <= 0 || x_ >= 545 || y_ <= 0 || y_ >= 511){
    this->hide();
    return;
  }
  ct_++;
  if(ct_ == t_){
    if(dir_ < 3) dir_++;
    else dir_ = 0;
    ct_ = 0;
    int temp = t_;
    t_ += t0_;
    t0_ = temp;
    v_++;
  }
  if(dir_==0){
    x_+=v_;
    y_-=v_;
  } else if(dir_==1){
    x_-=v_;
    y_-=v_;
  } else if(dir_==2){
    x_-=v_;
    y_+=v_;
  } else if(dir_==3){
    x_+=v_;
    y_+=v_;
  }
  if(x_ <= 0 || x_ >= 545 || y_ <= 0 || y_ >= 511){
    this->hide();
    return;
  }
  setPos(x_,y_);
  return;
}
