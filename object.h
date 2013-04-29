#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>

/** Object class defines the object for the "things" to inherit from*/
class Object : public QGraphicsPixmapItem {
 public:
  /** Object constructor
   *@param *pm QPixmap to set image of object
   *@param nx desired x position of object
   *@param ny desired y position of object */
  Object(QPixmap *pm, int nx, int ny);
  /** Virtual move function for each "thing" to implement */
  virtual void move() = 0;
  /** Gets x position of object
   *@return x position */
  int getX();
  /** Gets y position of object
   *@return y position */
  int getY();
  /** Gets width of object
   *@return width */
  int width();
  /** Gets height of object
   *@return height */
  int height();
  /** Sets direction for object's movement
   *@param dir desired direction */
  void setDir(int dir);
  /** Gets direction of object's movement
   *@return direction */
  int getDir();
  /** Virtual check function to see if object is a Code object
   *@return true if object is Code, else false */
  virtual bool isCode() = 0;
  /** Virtual check function to see if object is a Coffee object
   *@return true if object is Coffee, else false */
  virtual bool isCoffee() = 0;
  /** Virtual check function to see if object is a Bluescreen object
   *@return true if object is Bluescreen, else false */
  virtual bool isBluescreen() = 0;
  /** Virtual check function to see if object is a Bug object
   *@return true if object is Bug, else false */
  virtual bool isBug() = 0;
  /** Virtual check function to see if object is a Debugger object
   *@return true if object is Debugger, else false */
  virtual bool isDebugger() = 0;

 protected:
  /** Stores x position of object */
  int x_;
  /** Stores y position of object */
  int y_;
  /** Stores image of object */
  QPixmap *pixMap_;
  /** Stores direction of object's movement */
  int dir_;
};

#endif // OBJECT_H
