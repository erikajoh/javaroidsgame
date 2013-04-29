#include "object.h"

Object::Object(QPixmap *p, int nx, int ny) {
  pixMap_ = p;
  setPixmap(*p);
  x_ = nx;
  y_ = ny;
  setPos(x_, y_);
  dir_ = -1;
}

int Object::getX(){
  return x_;
}

int Object::getY(){
  return y_;
}

int Object::width(){
  return pixMap_->width();
}

int Object::height(){
  return pixMap_->height();
}

void Object::setDir(int dir){
  dir_ = dir;
}

int Object::getDir(){
  return dir_;
}
