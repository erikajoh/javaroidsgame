#ifndef CODE_H
#define CODE_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"
#include "bug.h"
#include <vector>

using namespace std;

class Code : public Object {
public:
  Code(QPixmap *pm, int nx, int ny);
  void move();
  bool isCode() {return true;}
  bool isCoffee() {return false;}
  bool isBluescreen() {return false;}
  bool isBug() {return false;}
  bool isDebugger() {return false;}

};

#endif // CODE_H
