#ifndef SUPERBUG_H
#define SUPERBUG_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"

/** SuperBug class inherits from Object class */
class SuperBug : public Object {
public:
  /** SuperBug constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  SuperBug(QPixmap *pm, int nx, int ny);
  /** SuperBug's move function */
  void move();
  /** Checks to see if object is a SuperBug object
   *@return true */
  bool isSuperBug() {return true;}

};

#endif // SUPERBUG_H
