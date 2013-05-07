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
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
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
#include "codergirl.h"
#include "superbug.h"
#include "pmminlist.h"
#include <fstream>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>

using namespace std;

/** MainWindow class defines and implements the window that is displayed on the GUI screen for gameplay */
class MainWindow : public QWidget {
    Q_OBJECT
    
public:
  /** MainWindow constructor */
    explicit MainWindow(char *filename);
  /** MainWindow deconstructor */
    ~MainWindow();

    /** Shows the window on the GUI screen */
    void show();
    /** Reads the high scores from file and populates list */
    void readScores();
    /** Writes the high scores to file */
    void writeScores();
    /** Returns current player's username */
    string getUsername() {return user;}
    /** Returns current player's score */
    int getScore() {return scoreCount;}
    /** Returns a pointer to list of high scores */
    PMMinList* getHighScores() {return highScores;}

private:
    /** Pointer to QGraphicsScene for display */
    QGraphicsScene *scene;
    /** Pointer to QGraphicsView for display */
    QGraphicsView *view;
    /** Pointer to QTimer for animation */
    QTimer *timer;
    /** Pointers to vertical layouts of GUI screen */
    QVBoxLayout *menuLayout, *gameLayout, *coder, *code, *coffee, *bug, *debugger, *blueScrn, *coderGirl, *superBug, *scoresLayout;
    /** Pointers to horizontal layouts of GUI screen */
    QHBoxLayout *icons, *status, *topBar;
    /** Pointers to buttons */
    QPushButton *start, *highScoresButton, *exit, *back, *end, *pause, *invincible, *restart;
    /** Pointers to labels */
    QLabel *welcome, *instructions, *score, *scoreDisp, *lives, *livesDisp, *level, *levelDisp, *prompt;
    /** Pointer to screen widget */
    QWidget *screen;
    /** Pointers to labels */
    QLabel *coderPic, *coderTxt, *codePic, *codeTxt, *coffeePic, *coffeeTxt, *bugPic, *bugTxt, *debuggerPic, *debuggerTxt, *blueScrnPic, *blueScrnTxt, *coderGirlPic, *coderGirlTxt, *superBugPic, *superBugTxt, *name, *nameDisp, *tips;
    /** Pointer to username input line edit */
    QLineEdit *username;
    /** Pointer to Coder object */
    Coder *coderObj;
    /** Pointer to Code object */
    Code *codeObj;
    /** Pointer to Bug object */
    Bug *bugObj;
    /** Pointer to Debugger object */
    Debugger *debuggerObj;
    /** Pointer to Coffee object */
    Coffee *coffeeObj;
    /** Pointer to Bluescreen object */
    Bluescreen *bluescreenObj;
    /** Pointer to CoderGirl object */
    CoderGirl *coderGirlObj;
    /** Pointer to SuperBug object */
    SuperBug *superBugObj;
    /** Pointers to QPixmaps for setting images of objects */
    QPixmap *coderImg, *codeImg, *coffeeImg, *bugImg, *bluescreenImg, *debuggerImgLeft, *debuggerImgUp, *debuggerImgRight, *debuggerImgDown, *coderGirlImg, *superBugImg, *bgImg;
    /** Pointer to QGraphicsPixmapItem to set background image */
    QGraphicsPixmapItem *bg;
    /** Keeps track of direction to move each object */
    int dir;
    /** Keeps track of time, i.e. number of times handleTimer() has been called */
    int timerCount;
    /** Keeps track of interval for timer */
    int interval;
    /** Vector of Object*s */
    vector<Object*> *objectList;
    /** Vector of Debugger*s */
    vector<Debugger*> *debuggerList;
    /** Bools to keep track of paused, invincibility, and game over status of game */
    bool paused, isInvincible, gameOver;
    /** Ints to keep track of score, lives, and level */
    int scoreCount, livesCount, levelCount;
    /** Phonon MediaObject to store audio clip */
    Phonon::MediaObject *mediaObject;
    /** PMMinList to keep track of high scores */
    PMMinList *highScores;
    /** Char array to store name of high scores file */
    char *fn;
    /** QString to store current player's username */
    QString *nameTxt;
    /** QListView to display high scores */
    QListView *highScoreDisp;
    /** QStandardItemModel to help display high scores */
    QStandardItemModel *model;
    /** QStandardItem to help display high scores */
    QStandardItem *item;
    /** String to store current player's username */
    string user;


public slots:
    /** Starts a new game */
    void newGame();
    /** Shows main menu */
    void showMenu();
    /** Handles timer, collisions, and movement of objects */
    void handleTimer();
    /** Changes paused state of game, i.e. if game is paused, unpause the game, and vice versa */
    void setPaused();
    /** Changes invincibility state of player, i.e. if player is invincible, remove invincibility, and vice versa */
    void setInvincible();
    /** Restarts the gameplay */
    void restartGame();
    /** Ends game and returns to main menu */
    void endGame();
    /** Plays audio clip */
    void playAudio();
    /** Displays high scores */
    void displayScores();

 protected:
    /** Handles key presses
     * @param event QKeyEvent* that Qt passes in when key press is detected */
    void keyPressEvent(QKeyEvent* event);

};

#endif // MAINWINDOW_H
