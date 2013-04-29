#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QLabel>
#include <QGraphicsLayout>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QTextEdit>
#include <QFormLayout>
#include <QKeyEvent>
#include <QWidget>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "object.h"
#include "coder.h"
#include "code.h"
#include "bug.h"
#include "coffee.h"
#include "debugger.h"
#include "bluescreen.h"

using namespace std;

/** MainWindow class defines and implements the window that is displayed on
 * the GUI screen for gameplay */
class MainWindow : public QWidget {
    Q_OBJECT
    
public:
  /** MainWindow constructor */
    explicit MainWindow();
  /** MainWindow deconstructor */
    ~MainWindow();

    /** Shows the window on the GUI screen */
    void show();

private:
    /** Pointer to QGraphicsScene for tile display */
    QGraphicsScene *scene;
    /** Pointer to QGraphicsView for tile display */
    QGraphicsView *view;
    /** Pointer to QTimer for tile animation */
    QTimer *timer;
    /** Pointer to layout of GUI screen */
    QVBoxLayout *menuLayout, *gameLayout, *coder, *code, *coffee, *bug, *debugger, *blueScrn;
    QHBoxLayout *icons, *status, *topBar;
    QPushButton *start, *exit, *end, *pause, *invincible, *restart;
    QLabel *welcome, *instructions, *score, *scoreDisp, *lives, *livesDisp, *level, *levelDisp, *prompt;
    QWidget *screen;
    QLabel *coderPic, *coderTxt, *codePic, *codeTxt, *coffeePic, *coffeeTxt, *bugPic, *bugTxt, *debuggerPic, *debuggerTxt, *blueScrnPic, *blueScrnTxt, *name, *nameDisp, *tips;
    QLineEdit *username;
    Coder *coderObj;
    Code *codeObj;
    Bug *bugObj;
    Debugger *debuggerObj;
    Coffee *coffeeObj;
    Bluescreen *bluescreenObj;
    QPixmap *coderImg, *codeImg, *coffeeImg, *bugImg, *bluescreenImg, *debuggerImgLeft, *debuggerImgUp, *debuggerImgRight, *debuggerImgDown, *bgImg;
    int dir, timerCount, interval;
    vector<Object*> *objectList;
    vector<Debugger*> *debuggerList;
    bool paused, isInvincible, gameOver;
    int scoreCount, livesCount, levelCount;

public slots:
    /** Starts a new game */
    void newGame();
    void showMenu();
    /** Handles timer */
    void handleTimer();
    void setPaused();
    void setInvincible();
    void restartGame();

 protected:
    void keyPressEvent(QKeyEvent* event);

};

#endif // MAINWINDOW_H
