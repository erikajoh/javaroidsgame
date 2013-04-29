#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cstdlib>

class Object : public QGraphicsPixmapItem {
 public:
  Object(QPixmap *pm, int nx, int ny);
  virtual void move() = 0;
  int getX();
  int getY();
  int width();
  int height();
  void setDir(int dir);
  int getDir();
  virtual bool isCode() = 0;
  virtual bool isCoffee() = 0;
  virtual bool isBluescreen() = 0;
  virtual bool isBug() = 0;
  virtual bool isDebugger() = 0;

 protected:
  int x_;
  int y_;
  int xv_;
  int yv_;
  QPixmap *pixMap_;
  int dir_;
};

#endif // OBJECT_H
