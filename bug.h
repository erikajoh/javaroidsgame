#ifndef BUG_H
#define BUG_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"

/** Bug class inherits from Object class */
class Bug : public Object {
public:
  /** Bug constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  Bug(QPixmap *pm, int nx, int ny);
  /** Bug's move function */
  void move();
  /** Checks to see if object is a Code object
   *@return false */
  bool isCode() {return false;}
  /** Checks to see if object is a Coffee object
   *@return false */
  bool isCoffee() {return false;}
  /** Checks to see if object is a Bluescreen object
   *@return false */
  bool isBluescreen() {return false;}
  /** Checks to see if object is a Bug object
   *@return true */
  bool isBug() {return true;}
  /** Checks to see if object is a Debugger object
   *@return false */
  bool isDebugger() {return false;}

};

#endif // BUG_H
