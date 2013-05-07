#ifndef CODERGIRL_H
#define CODERGIRL_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include "object.h"
#include <vector>

using namespace std;

/** CoderGirl class inherits from Object class */
class CoderGirl : public Object {
public:
  /** CoderGirl constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  CoderGirl(QPixmap *pm, int nx, int ny);
  /** CoderGirl's move function */
  void move();
  /** Checks to see if object is a CoderGirl object
   *@return true */
  bool isCoderGirl() {return true;}

};

#endif // CODERGIRL_H
