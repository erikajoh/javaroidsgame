#ifndef COFFEE_H
#define COFFEE_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"

class Coffee : public Object {
public:
  Coffee(QPixmap *pm, int nx, int ny);
  void move();
  bool isCode() {return false;}
  bool isCoffee() {return true;}
  bool isBluescreen() {return false;}
  bool isBug() {return false;}
  bool isDebugger() {return false;}

};

#endif // COFFEE_H
