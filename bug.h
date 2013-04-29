#ifndef BUG_H
#define BUG_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"

class Bug : public Object {
public:
  Bug(QPixmap *pm, int nx, int ny);
  void move();
  bool isCode() {return false;}
  bool isCoffee() {return false;}
  bool isBluescreen() {return false;}
  bool isBug() {return true;}
  bool isDebugger() {return false;}

};

#endif // BUG_H
