#ifndef CODER_H
#define CODER_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include <vector>
#include "object.h"

using namespace std;

class Coder : public Object {
public:
  Coder(QPixmap *pm, int nx, int ny);
  void move();
  void rotateMe(int dir);
  bool isCode() {return false;}
  bool isCoffee() {return false;}
  bool isBluescreen() {return false;}
  bool isBug() {return false;}
  bool isDebugger() {return false;}

 private:
  int facing; //0 is left, 1 is up, 2 is right, 3 is down

};

#endif // CODER_H
