#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"

class Debugger : public Object {
public:
  Debugger(QPixmap *pm, int nx, int ny);
  void move();
  bool isCode() {return false;}
  bool isCoffee() {return false;}
  bool isBluescreen() {return false;}
  bool isBug() {return false;}
  bool isDebugger() {return true;}

};

#endif // DEBUGGER_H
