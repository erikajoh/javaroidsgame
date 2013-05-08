#ifndef COFFEE_H
#define COFFEE_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"

/** Coffee class inherits from Object class */
class Coffee : public Object {
public:
  /** Coffee constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  Coffee(QPixmap *pm, int nx, int ny);
  /** Coffee's move function */
  void move();
  /** Checks to see if object is a Coffee object
   *@return true */
  bool isCoffee() {return true;}

};

#endif // COFFEE_H
