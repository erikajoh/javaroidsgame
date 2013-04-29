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
  /** Checks to see if object is a Code object
   *@return false */
  bool isCode() {return false;}
  /** Checks to see if object is a Coffee object
   *@return true */
  bool isCoffee() {return true;}
  /** Checks to see if object is a Bluescreen object
   *@return false */
  bool isBluescreen() {return false;}
  /** Checks to see if object is a Bug object
   *@return false */
  bool isBug() {return false;}
  /** Checks to see if object is a Debugger object
   *@return false */
  bool isDebugger() {return false;}

};

#endif // COFFEE_H
