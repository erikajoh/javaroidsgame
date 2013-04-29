#ifndef CODER_H
#define CODER_H
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>
#include <vector>
#include "object.h"

using namespace std;

/** Coder class inherits from Object class */
class Coder : public Object {
public:
  /** Coder constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  Coder(QPixmap *pm, int nx, int ny);
  /** Coder's move function */
  void move();
  /** Rotates Coder image according to direction of movement
   *@param dir direction of movement */
  void rotateMe(int dir);
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
   *@return false */
  bool isBug() {return false;}
  /** Checks to see if object is a Debugger object
   *@return false */
  bool isDebugger() {return false;}

 private:
  /** Keeps track of direction Coder image is facing */
  int facing; //0 is left, 1 is up, 2 is right, 3 is down

};

#endif // CODER_H
