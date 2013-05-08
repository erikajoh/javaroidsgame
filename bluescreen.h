#ifndef BLUESCREEN_H
#define BLUESCREEN_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include <cmath>
#include "object.h"

/** Bluescreen class inherits from Object class */
class Bluescreen : public Object {
public:
  /** Bluescreen constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  Bluescreen(QPixmap *pm, int nx, int ny);
  /** Bluescreen's move function, uses fibonacci sequence */
  void move();
  /** Checks to see if object is a Bluescreen object
   *@return true */
  bool isBluescreen() {return true;}

 private:
  /** Ints to store values for fibonacci sequence */
  int t_, t0_, ct_, v_;

};

#endif // BLUESCREEN_H
