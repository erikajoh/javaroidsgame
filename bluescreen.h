#ifndef BLUESCREEN_H
#define BLUESCREEN_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include <cmath>
#include "object.h"

class Bluescreen : public Object {
public:
  Bluescreen(QPixmap *pm, int nx, int ny);
  void move();
  bool isCode() {return false;}
  bool isCoffee() {return false;}
  bool isBluescreen() {return true;}
  bool isBug() {return false;}
  bool isDebugger() {return false;}

 private:
  int t_, t0_, ct_, v_;

};

#endif // BLUESCREEN_H
