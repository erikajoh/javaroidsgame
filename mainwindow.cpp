#include "mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QtGui>
#include <QRectF>

using namespace std;

MainWindow::MainWindow(char* filename)  {

    scene = new QGraphicsScene();
    screen = new QWidget;
    screen->setWindowTitle("JAVAROIDS");
    screen->setFixedSize(600, 650);
    gameLayout = NULL;
    menuLayout = NULL;
    scoresLayout = NULL;
    mediaObject = NULL;
    QTimer* audioTimer = new QTimer();
    audioTimer->setInterval(24000);
    connect(audioTimer, SIGNAL(timeout()), this, SLOT(playAudio()));
    audioTimer->start();
    playAudio();
    timer = NULL;
    srand(time(0));
    fn = filename;
    highScores = new PMMinList;
    readScores();
    showMenu();

}

void MainWindow::newGame() {

    if( (username->text()).length() > 20 || (username->text()).length() < 2 ) {
        QMessageBox box;
        box.setWindowTitle("Error");
        box.setText("Please enter a username with length 2-20 characters.");
        box.exec();
        return;
    }

    for (int i=0; i<(username->text()).length(); i++) {
        if ((username->text()).at(i) == ' ') {
            QMessageBox box;
            box.setWindowTitle("Error");
            box.setText("Please enter a username without spaces.");
            box.exec();
            return;
        }
    }

    grabKeyboard();

    name = new QLabel("/Coder's name:");
    name->setFont(QFont("courier", 10));
    name->setAlignment(Qt::AlignHCenter);
    name->setAlignment(Qt::AlignVCenter);

    nameTxt = new QString(username->text());
    user = qPrintable(username->text());
    nameDisp = new QLabel(*nameTxt);
    nameDisp->setFont(QFont("courier", 10));
    nameDisp->setAlignment(Qt::AlignHCenter);
    nameDisp->setAlignment(Qt::AlignVCenter);

    scoreCount = 0;
    livesCount = 5;
    levelCount = 1;

    paused = false;
    isInvincible = false;
    gameOver = false;

    view = new QGraphicsView(scene);
    gameLayout = new QVBoxLayout;
    delete coder;
    delete code;
    delete bug;
    delete debugger;
    delete blueScrn;
    delete coffee;
    delete superBug;
    delete coderGirl;
    delete icons;
    delete coderPic;
    delete coderTxt;
    delete codePic;
    delete codeTxt;
    delete bugPic;
    delete bugTxt;
    delete debuggerTxt;
    delete debuggerPic;
    delete blueScrnTxt;
    delete blueScrnPic;
    delete coffeePic;
    delete coffeeTxt;
    delete coderGirlPic;
    delete coderGirlTxt;
    delete superBugPic;
    delete superBugTxt;
    delete menuLayout;
    delete welcome;
    delete instructions;
    delete start;
    delete exit;
    delete highScoresButton;
    delete prompt;
    delete username;

    screen->setLayout(gameLayout);

    topBar = new QHBoxLayout;

    status = new QHBoxLayout;

    restart = new QPushButton("re&start");
    connect(restart, SIGNAL(clicked()), this, SLOT(restartGame()));
    restart->setFont(QFont("courier", 10));

    end = new QPushButton("&end");
    connect(end, SIGNAL(clicked()), this, SLOT(endGame()));
    end->setFont(QFont("courier", 10));

    invincible = new QPushButton("&invincible");
    connect(invincible, SIGNAL(clicked()), this, SLOT(setInvincible()));
    invincible->setFont(QFont("courier", 10));

    pause = new QPushButton("&pause");
    connect(pause, SIGNAL(clicked()), this, SLOT(setPaused()));
    pause->setFont(QFont("courier", 10));

    score = new QLabel("/Score:");
    score->setFont(QFont("courier", 10));
    score->setAlignment(Qt::AlignRight);
    score->setAlignment(Qt::AlignVCenter);

    scoreDisp = new QLabel("0");
    scoreDisp->setFont(QFont("courier", 10));
    scoreDisp->setAlignment(Qt::AlignRight);
    scoreDisp->setAlignment(Qt::AlignVCenter);

    lives = new QLabel("/Lives:");
    lives->setFont(QFont("courier", 10));
    lives->setAlignment(Qt::AlignRight);
    lives->setAlignment(Qt::AlignVCenter);

    livesDisp = new QLabel("5");
    livesDisp->setFont(QFont("courier", 10));
    livesDisp->setAlignment(Qt::AlignRight);
    livesDisp->setAlignment(Qt::AlignVCenter);

    level = new QLabel("/Level:");
    level->setFont(QFont("courier",10));
    level->setAlignment(Qt::AlignRight);
    level->setAlignment(Qt::AlignVCenter);

    levelDisp = new QLabel("1");
    levelDisp->setFont(QFont("courier", 10));
    levelDisp->setAlignment(Qt::AlignRight);
    levelDisp->setAlignment(Qt::AlignVCenter);

    tips = new QLabel("Coffee +life  /  CoderGirl +100pts  /  Bugs -10pts  /  Code -life  /  Kill bugs +10pts\nUse arrow keys to move / spacebar to fire debuggers / hit by blue screen = GAME OVER!!!");
    tips->setFont(QFont("courier", 8));
    tips->setAlignment(Qt::AlignHCenter);
    tips->setAlignment(Qt::AlignVCenter);

    topBar->addWidget(name);
    topBar->addWidget(nameDisp);
    topBar->addWidget(score);
    topBar->addWidget(scoreDisp);
    topBar->addWidget(lives);
    topBar->addWidget(livesDisp);
    topBar->addWidget(level);
    topBar->addWidget(levelDisp);
    status->addWidget(invincible);
    status->addWidget(pause);
    status->addWidget(restart);
    status->addWidget(end);

    gameLayout->addLayout(topBar);
    gameLayout->addWidget(tips);
    gameLayout->addWidget(view);
    gameLayout->addLayout(status);

    bgImg = new QPixmap("images/bg.jpg");
    bg = new QGraphicsPixmapItem(*bgImg);
    scene->addItem(bg);

    coderImg = new QPixmap("images/coderIcon.gif");
    coderObj = new Coder(coderImg, bgImg->width()/2, bgImg->height()/2);
    coderObj->setDir(0);
    coderObj->setZValue(1);
    scene->addItem(coderObj);

    codeImg = new QPixmap("images/codeIcon.png");
    coffeeImg = new QPixmap("images/coffeeIcon.png");
    bluescreenImg = new QPixmap("images/crashIcon.gif");
    bugImg = new QPixmap("images/bugIcon.gif");
    coderGirlImg = new QPixmap("images/coderGirlIcon.png");
    superBugImg = new QPixmap("images/superBugIcon.gif");
    debuggerImgLeft = new QPixmap("images/debuggerIconLeft.gif");
    debuggerImgUp = new QPixmap("images/debuggerIconUp.gif");
    debuggerImgRight = new QPixmap("images/debuggerIconRight.gif");
    debuggerImgDown = new QPixmap("images/debuggerIconDown.gif");

    timer = new QTimer(this);
    interval = 60;
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
    timer->start();
    timerCount = 0;

    objectList = new vector<Object*>;
    debuggerList = new vector<Debugger*>;

}

void MainWindow::showMenu() {

    scoreCount = -1;

    releaseKeyboard();

    welcome = new QLabel("Welcome to\nJAVAROIDS\n(A world of java)");
    welcome->setFont(QFont("courier", 36, QFont::Bold));
    welcome->setAlignment(Qt::AlignHCenter);

    instructions = new QLabel("You are the coder.\nLeveling up is GOOD. (+50 pts)\nCoffee is GOOD. (+1 life)\nCode is BAD. Don't get hit! (-1 life)\nBugs and superbugs are BAD. Don't get hit! (-10 pts)\nYou can kill bugs and superbugs with debuggers. (+10 pts)\nThe codergirl is AWESOME. (+100 pts)\n\nIf you get hit by the blue screen of death...game over.\nUse the arrow keys to move and spacebar to fire debuggers.\nGood luck!\n:)\n");
    instructions->setFont(QFont("courier", 10));
    instructions->setAlignment(Qt::AlignHCenter);

    start = new QPushButton("&start");
    start->setFont(QFont("courier", 14));
    connect(start, SIGNAL(clicked()), this, SLOT(newGame()));
    highScoresButton = new QPushButton("&high scores");
    highScoresButton->setFont(QFont("courier", 14));
    connect(highScoresButton, SIGNAL(clicked()), this, SLOT(displayScores()));
    exit = new QPushButton("&exit");
    exit->setFont(QFont("courier", 14));
    connect(exit, SIGNAL(clicked()), qApp, SLOT(quit()));

    coder = new QVBoxLayout;
    coderPic = new QLabel;
    coderPic->setPixmap(QPixmap("images/coder.gif"));
    coderPic->setAlignment(Qt::AlignHCenter);
    coderTxt = new QLabel("you!");
    coderTxt->setAlignment(Qt::AlignHCenter);
    coderTxt->setFont(QFont("courier", 12));
    coder->addWidget(coderPic);
    coder->addWidget(coderTxt);

    code = new QVBoxLayout;
    codePic = new QLabel;
    codePic->setPixmap(QPixmap("images/code.png"));
    codePic->setAlignment(Qt::AlignHCenter);
    codeTxt = new QLabel("code");
    codeTxt->setAlignment(Qt::AlignHCenter);
    codeTxt->setFont(QFont("courier", 12));
    code->addWidget(codePic);
    code->addWidget(codeTxt);

    coffee = new QVBoxLayout;
    coffeePic = new QLabel;
    coffeePic->setPixmap(QPixmap("images/coffee.png"));
    coffeePic->setAlignment(Qt::AlignHCenter);
    coffeeTxt = new QLabel("coffee");
    coffeeTxt->setAlignment(Qt::AlignHCenter);
    coffeeTxt->setFont(QFont("courier", 12));
    coffee->addWidget(coffeePic);
    coffee->addWidget(coffeeTxt);

    bug = new QVBoxLayout;
    bugPic = new QLabel;
    bugPic->setPixmap(QPixmap("images/bug.gif"));
    bugPic->setAlignment(Qt::AlignHCenter);
    bugTxt = new QLabel("bug");
    bugTxt->setAlignment(Qt::AlignHCenter);
    bugTxt->setFont(QFont("courier", 12));
    bug->addWidget(bugPic);
    bug->addWidget(bugTxt);

    debugger = new QVBoxLayout;
    debuggerPic = new QLabel;
    debuggerPic->setPixmap(QPixmap("images/debugger.gif"));
    debuggerPic->setAlignment(Qt::AlignHCenter);
    debuggerTxt = new QLabel("debugger");
    debuggerTxt->setAlignment(Qt::AlignHCenter);
    debuggerTxt->setFont(QFont("courier", 12));
    debugger->addWidget(debuggerPic);
    debugger->addWidget(debuggerTxt);

    blueScrn = new QVBoxLayout;
    blueScrnPic = new QLabel;
    blueScrnPic->setPixmap(QPixmap("images/crash.gif"));
    blueScrnPic->setAlignment(Qt::AlignHCenter);
    blueScrnTxt = new QLabel("bluescrn");
    blueScrnTxt->setAlignment(Qt::AlignHCenter);
    blueScrnTxt->setFont(QFont("courier", 12));
    blueScrn->addWidget(blueScrnPic);
    blueScrn->addWidget(blueScrnTxt);

    coderGirl = new QVBoxLayout;
    coderGirlPic = new QLabel;
    coderGirlPic->setPixmap(QPixmap("images/coderGirl.png"));
    coderGirlPic->setAlignment(Qt::AlignHCenter);
    coderGirlTxt = new QLabel("codergirl");
    coderGirlTxt->setAlignment(Qt::AlignHCenter);
    coderGirlTxt->setFont(QFont("courier",12));
    coderGirl->addWidget(coderGirlPic);
    coderGirl->addWidget(coderGirlTxt);

    superBug = new QVBoxLayout;
    superBugPic = new QLabel;
    superBugPic->setPixmap(QPixmap("images/superBug.gif"));
    superBugPic->setAlignment(Qt::AlignHCenter);
    superBugTxt = new QLabel("superbug");
    superBugTxt->setFont(QFont("courier",12));
    superBug->addWidget(superBugPic);
    superBug->addWidget(superBugTxt);

    menuLayout = new QVBoxLayout;
    icons = new QHBoxLayout;
    icons->addLayout(coder);
    icons->addLayout(coderGirl);
    icons->addLayout(debugger);
    icons->addLayout(coffee);
    icons->addLayout(bug);
    icons->addLayout(superBug);
    icons->addLayout(code);
    icons->addLayout(blueScrn);

    username = new QLineEdit("");
    prompt = new QLabel("Enter a username to start debugging: ");
    prompt->setAlignment(Qt::AlignHCenter);
    username->setFont(QFont("courier", 14, QFont::Bold));
    username->setAlignment(Qt::AlignHCenter);
    prompt->setFont(QFont("courier", 14, QFont::Bold));

    if(scoresLayout) {
        delete scoresLayout;
        delete highScoreDisp;
        delete model;
        delete back;
    }

    scoresLayout = NULL;

    screen->setLayout(menuLayout);
    menuLayout->addWidget(welcome);
    menuLayout->addWidget(instructions);
    menuLayout->addLayout(icons);
    menuLayout->addWidget(prompt);
    menuLayout->addWidget(username);
    menuLayout->addWidget(start);
    menuLayout->addWidget(highScoresButton);
    menuLayout->addWidget(exit);

}

void MainWindow::show() {
    //This is how we get our view displayed.
    screen->show();
}

void MainWindow::handleTimer() {

    if(!livesCount) {
        tips->setText("SORRY, GAME OVER");
        tips->setFont(QFont("courier",16));
        tips->setAlignment(Qt::AlignHCenter);
        gameOver = true;
        return;
    }

    if(paused) {
        return;
    }

    if ( ( timerCount == 500 && levelCount == 1 ) || ( levelCount == 2 && timerCount == 1500 ) ) {
        levelCount++;
        scoreCount += 50;
        QString scoreText;
        scoreText.setNum(scoreCount);
        scoreDisp->setText(scoreText);
        interval /= 2;
        QString levelText;
        levelText.setNum(levelCount);
        levelDisp->setText(levelText);
        if (levelCount == 2) {
            delete bgImg;
            delete bg;
            bgImg = new QPixmap("images/bg2.jpg");
            bg = new QGraphicsPixmapItem(*bgImg);
            scene->addItem(bg);
            for (int i=objectList->size()-1; i>=0; i--) {
                objectList->at(i)->setZValue(1);
            }
        }
        if (levelCount == 3) {
            delete bgImg;
            delete bg;
            bgImg = new QPixmap("images/bg3.jpg");
            bg = new QGraphicsPixmapItem(*bgImg);
            scene->addItem(bg);
            for (int i=objectList->size()-1; i>=0; i--) {
                objectList->at(i)->setZValue(1);
            }
        }
        timer->setInterval(interval);
    }

    int caseNum = rand()%4;
    int moveDir = rand()%3;

    if (timerCount%70 == 0) {
        if (caseNum == 0) { //enter from left
            codeObj = new Code(codeImg, 2, rand()%508 + 2);
            if (moveDir == 0) codeObj->setDir(2);
            else if (moveDir == 1) codeObj->setDir(4);
            else if (moveDir == 2) codeObj->setDir(6);
        } else if (caseNum == 1) { //enter from top
            codeObj = new Code(codeImg, rand()%543 + 2, 2);
            if (moveDir == 0) codeObj->setDir(3);
            else if (moveDir == 1) codeObj->setDir(6);
            else if (moveDir == 2) codeObj->setDir(7);
        } else if (caseNum == 2) { //enter from right
            codeObj = new Code(codeImg, 543, rand()%508 + 2);
            if (moveDir == 0) codeObj->setDir(0);
            else if (moveDir == 1) codeObj->setDir(5);
            else if (moveDir == 2) codeObj->setDir(7);
        } else if (caseNum == 3) { //enter from bottom
            codeObj = new Code(codeImg, rand()%543 + 2, 508);
            if (moveDir == 0) codeObj->setDir(1);
            else if (moveDir == 1) codeObj->setDir(4);
            else if (moveDir == 2) codeObj->setDir(5);
        }
        bugObj = new Bug(bugImg, codeObj->getX(), codeObj->getY());
        bugObj->setDir(codeObj->getDir());
        superBugObj = new SuperBug(superBugImg, codeObj->getX(), codeObj->getY());
        if(superBugObj->getX() == coderObj->getX()) {
            if(superBugObj->getY() < coderObj->getY()) superBugObj->setDir(3);
            if(superBugObj->getY() > coderObj->getY()) superBugObj->setDir(1);
        } else if(superBugObj->getX() < coderObj->getX()) {
            if(superBugObj->getY() < coderObj->getY()) superBugObj->setDir(6);
            if(superBugObj->getY() == coderObj->getY()) superBugObj->setDir(2);
            if(superBugObj->getY() > coderObj->getY()) superBugObj->setDir(4);
        } else if(superBugObj->getX() > coderObj->getX()) {
            if(superBugObj->getY() < coderObj->getY()) superBugObj->setDir(7);
            if(superBugObj->getY() == coderObj->getY()) superBugObj->setDir(0);
            if(superBugObj->getY() > coderObj->getY()) superBugObj->setDir(5);
        }
        scene->addItem(bugObj);
        scene->addItem(superBugObj);
        scene->addItem(codeObj);
        objectList->push_back(codeObj);
        objectList->push_back(superBugObj);
        objectList->push_back(bugObj);
    }
    if (timerCount%65 == 0) {
        coffeeObj = new Coffee(coffeeImg,rand()%543 + 2,rand()%508 + 2);
        scene->addItem(coffeeObj);
        objectList->push_back(coffeeObj);
    }
    if (timerCount%190 == 0) {
        if (caseNum == 0) { //enter from left
            coderGirlObj = new CoderGirl(coderGirlImg, 2, rand()%508 + 2);
	    if (moveDir == 0) coderGirlObj->setDir(2);
            else if (moveDir == 1) coderGirlObj->setDir(4);
            else if (moveDir == 2) coderGirlObj->setDir(6);
        } else if (caseNum == 1) { //enter from top
            coderGirlObj = new CoderGirl(coderGirlImg, rand()%543 + 2, 2);
            if (moveDir == 0) coderGirlObj->setDir(3);
            else if (moveDir == 1) coderGirlObj->setDir(6);
            else if (moveDir == 2) coderGirlObj->setDir(7);
        } else if (caseNum == 2) { //enter from right
            coderGirlObj = new CoderGirl(coderGirlImg, 543, rand()%508 + 2);
	    if (moveDir == 0) coderGirlObj->setDir(0);
            else if (moveDir == 1) coderGirlObj->setDir(5);
            else if (moveDir == 2) coderGirlObj->setDir(7);
        } else if (caseNum == 3) { //enter from bottom
            coderGirlObj = new CoderGirl(coderGirlImg, rand()%543 + 2, 508);
            if (moveDir == 0) coderGirlObj->setDir(1);
            else if (moveDir == 1) coderGirlObj->setDir(4);
            else if (moveDir == 2) coderGirlObj->setDir(5);
        }
        scene->addItem(coderGirlObj);
        objectList->push_back(coderGirlObj);
    }
    if (timerCount && timerCount%300 == 0) {
        bluescreenObj = new Bluescreen(bluescreenImg,bgImg->width()/2,bgImg->height()/2);
        scene->addItem(bluescreenObj);
        objectList->push_back(bluescreenObj);
        bluescreenObj->setDir(rand()%4);
    }

    for (int i=debuggerList->size()-1; i>=0; i--) {
        for (int j=objectList->size()-1; j>=0; j--) {
            if (debuggerList->at(i)->collidesWithItem(objectList->at(j)) && objectList->at(j)->isVisible() && !(objectList->at(j)->isCoffee()) && !(objectList->at(j)->isBluescreen()) && !(objectList->at(j)->isCode()) && !(objectList->at(j)->isCoderGirl())) {
                scoreCount += 10;
                QString scoreText;
                scoreText.setNum(scoreCount);
                scoreDisp->setText(scoreText);
                debuggerList->at(i)->setZValue(0);
                debuggerList->at(i)->hide();
                debuggerList->at(i)->setZValue(0);
                objectList->at(j)->hide();
            }
        }
        if (debuggerList->at(i)->getX() + debuggerList->at(i)->width() >= bgImg->width()-9 || debuggerList->at(i)->getX() <= 9 || debuggerList->at(i)->getY() + debuggerList->at(i)->height() >= bgImg->height()-9 || debuggerList->at(i)->getY() <= 9) {
            debuggerList->at(i)->setZValue(0);
            debuggerList->at(i)->hide();
            debuggerList->erase(debuggerList->begin()+i);
        } else debuggerList->at(i)->move();
    }

    for (int i=objectList->size()-1; i>=0; i--) {
      if ( objectList->at(i)->isCoderGirl() && ( abs(objectList->at(i)->getX() - coderObj->getX()) <= 60 && abs(objectList->at(i)->getY() - coderObj->getY()) <= 60 ) ){
	objectList->at(i)->setDir(coderObj->getDir());
	for (int k=0; k<2; k++){
	  if (!(objectList->at(i)->getX() + objectList->at(i)->width() >= bgImg->width()-1 || objectList->at(i)->getX() <= 1 || objectList->at(i)->getY() + objectList->at(i)->height() >= bgImg->height()-1 || objectList->at(i)->getY() <= 1)) objectList->at(i)->move();
	}
      }
      if (coderObj->collidesWithItem(objectList->at(i)) && objectList->at(i)->isVisible()) {
	if ( (objectList->at(i)->isBug() || objectList->at(i)->isSuperBug()) && !isInvincible ) {
	  if (scoreCount) scoreCount -= 10;
	  else if (livesCount) livesCount--;
	  else break;
	}
	if (objectList->at(i)->isCode() && !isInvincible) livesCount--;
	if (objectList->at(i)->isCoderGirl()) scoreCount += 100;
	if (objectList->at(i)->isCoffee()) livesCount++;
	if ( objectList->at(i)->isBluescreen() && !isInvincible ) livesCount = 0;
	QString scoreText, livesText;
	scoreText.setNum(scoreCount);
	livesText.setNum(livesCount);
	scoreDisp->setText(scoreText);
	livesDisp->setText(livesText);
	if ((!(objectList->at(i)->isDebugger()) && !isInvincible && !(objectList->at(i)->isBluescreen())) || objectList->at(i)->isCoffee() || objectList->at(i)->isCoderGirl()) {
	  objectList->at(i)->setZValue(0);
	  objectList->at(i)->hide();
	  objectList->erase(objectList->begin()+i);
	} else {
	  if (objectList->at(i)->isSuperBug()) {
	    if(abs(objectList->at(i)->getX() - coderObj->getX()) <= 5) {
	      if(objectList->at(i)->getY() < coderObj->getY() - 5) objectList->at(i)->setDir(3);
	      else if(objectList->at(i)->getY() > coderObj->getY() + 5) objectList->at(i)->setDir(1);
	    } else if(objectList->at(i)->getX() < coderObj->getX() - 5) {
	      if(objectList->at(i)->getY() < coderObj->getY() - 5) objectList->at(i)->setDir(6);
	      else if(abs(objectList->at(i)->getY() - coderObj->getY()) <= 5) objectList->at(i)->setDir(2);
	      else if(objectList->at(i)->getY() > coderObj->getY() + 5) objectList->at(i)->setDir(4);
	    } else if(objectList->at(i)->getX() > coderObj->getX() + 5) {
	      if(objectList->at(i)->getY() < coderObj->getY() - 5) objectList->at(i)->setDir(7);
	      else if(abs(objectList->at(i)->getY() - coderObj->getY()) <= 5) objectList->at(i)->setDir(0);
	      else if(objectList->at(i)->getY() > coderObj->getY() + 5) objectList->at(i)->setDir(5);
	    }
	  }    
	  if (!(objectList->at(i)->getX() + objectList->at(i)->width() >= bgImg->width()-1 || objectList->at(i)->getX() <= 1 || objectList->at(i)->getY() + objectList->at(i)->height() >= bgImg->height()-1 || objectList->at(i)->getY() <= 1)) objectList->at(i)->move();
	}
      } else if (objectList->at(i)->getX() + objectList->at(i)->width() >= bgImg->width()-1 || objectList->at(i)->getX() <= 1 || objectList->at(i)->getY() + objectList->at(i)->height() >= bgImg->height()-1 || objectList->at(i)->getY() <= 1) {
	objectList->at(i)->setZValue(0);
	objectList->at(i)->hide();
	objectList->erase(objectList->begin()+i);
      } else if (objectList->at(i)->isCoffee()) {
	if (rand()%200 == 0) {
	  objectList->at(i)->setZValue(0);
	  objectList->at(i)->hide();
	  objectList->erase(objectList->begin()+i);
	}
      } else {
	if (objectList->at(i)->isSuperBug()) {
	    if(abs(objectList->at(i)->getX() - coderObj->getX()) <= 5) {
	      if(objectList->at(i)->getY() < coderObj->getY() - 5) objectList->at(i)->setDir(3);
	      else if(objectList->at(i)->getY() > coderObj->getY() + 5) objectList->at(i)->setDir(1);
	    } else if(objectList->at(i)->getX() < coderObj->getX() - 5) {
	      if(objectList->at(i)->getY() < coderObj->getY() - 5) objectList->at(i)->setDir(6);
	      else if(abs(objectList->at(i)->getY() - coderObj->getY()) <= 5) objectList->at(i)->setDir(2);
	      else if(objectList->at(i)->getY() > coderObj->getY() + 5) objectList->at(i)->setDir(4);
	    } else if(objectList->at(i)->getX() > coderObj->getX() + 5) {
	      if(objectList->at(i)->getY() < coderObj->getY() - 5) objectList->at(i)->setDir(7);
	      else if(abs(objectList->at(i)->getY() - coderObj->getY()) <= 5) objectList->at(i)->setDir(0);
	      else if(objectList->at(i)->getY() > coderObj->getY() + 5) objectList->at(i)->setDir(5);
	    }
	}
	objectList->at(i)->move();
      }
    }
    
    for (int i=debuggerList->size()-1; i>0; i--) {
      if (!(debuggerList->at(i)->isVisible())) {
	debuggerList->at(i)->setZValue(0);
	debuggerList->erase(debuggerList->begin()+i);
      }
    }
    
    for (int i=objectList->size()-1; i>0; i--) {
      if (!(objectList->at(i)->isVisible())) {
	objectList->at(i)->setZValue(0);
	objectList->erase(objectList->begin()+i);
      }
    }
    
    timerCount++;
    
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    event = event;
    if(paused || gameOver) return;
    if(event->key() == Qt::Key_Left && ( (coderObj->getDir() == 0 && coderObj->getX() > 15) || coderObj->getX() > 45 ) ) {
        coderObj->setDir(0);
        coderObj->move();
    }
    if(event->key() == Qt::Key_Right && coderObj->getX() + 15 < bgImg->width()) {
        coderObj->setDir(2);
        coderObj->move();
    }
    if(event->key() == Qt::Key_Up && coderObj->getY() > 15) {
        coderObj->setDir(1);
        coderObj->move();
    }
    if(event->key() == Qt::Key_Down && ( (coderObj->getDir() == 3 && coderObj->getY() + 15 < bgImg->height()) || coderObj->getY() + 40 < bgImg->height() ) ) {
        coderObj->setDir(3);
        coderObj->move();
    }
    if(event->key() == Qt::Key_Space) {
        if (coderObj->getDir() == 0 && coderObj->getX() > 5 + debuggerImgLeft->width()) {
            debuggerObj = new Debugger(debuggerImgLeft,coderObj->getX()-debuggerImgLeft->width(),coderObj->getY());
            debuggerObj->setDir(coderObj->getDir());
            debuggerList->push_back(debuggerObj);
            scene->addItem(debuggerObj);
        } else if (coderObj->getDir() == 1 && coderObj->getY() > 5 + debuggerImgUp->height()) {
            debuggerObj = new Debugger(debuggerImgUp,coderObj->getX()-debuggerImgUp->width(),coderObj->getY()-debuggerImgUp->height());
            debuggerObj->setDir(coderObj->getDir());
            debuggerList->push_back(debuggerObj);
            scene->addItem(debuggerObj);
        } else if (coderObj->getDir() == 2 && coderObj->getX() + 5 < bgImg->width() - debuggerImgRight->width()) {
            debuggerObj = new Debugger(debuggerImgRight,coderObj->getX(),coderObj->getY());
            debuggerObj->setDir(coderObj->getDir());
            debuggerList->push_back(debuggerObj);
            scene->addItem(debuggerObj);
        } else if (coderObj->getDir() == 3 && coderObj->getY() + 5 < bgImg->height() - debuggerImgDown->height()) {
            debuggerObj = new Debugger(debuggerImgDown,coderObj->getX()-debuggerImgDown->width(),coderObj->getY());
            debuggerObj->setDir(coderObj->getDir());
            debuggerList->push_back(debuggerObj);
            scene->addItem(debuggerObj);
        }
    }
}

void MainWindow::setPaused() {
    if(paused) {
        paused = false;
        pause->setText("&pause");
    }
    else {
        paused = true;
        pause->setText("un&pause");
    }
}

void MainWindow::setInvincible() {
    if(isInvincible) {
        isInvincible = false;
        invincible->setText("&invincible");
    } else {
        isInvincible = true;
        invincible->setText("un&invincible");
    }
}

void MainWindow::endGame() {

    delete timer;

    Score* scoreObj = new Score(qPrintable(*nameTxt),scoreCount);
    if ( highScores->size() < 10 ) highScores->push(scoreObj);
    else if ( scoreObj->getScore() >= highScores->top()->getScore() ) {
        highScores->pop();
        highScores->push(scoreObj);
    }
    writeScores();

    for (int i=objectList->size()-1; i>=0; i--) {
        objectList->at(i)->setZValue(0);
    }
    coderObj->setZValue(0);
    delete gameLayout;
    delete view;
    delete end;
    delete pause;
    delete restart;
    delete invincible;
    delete score;
    delete scoreDisp;
    delete lives;
    delete livesDisp;
    delete level;
    delete levelDisp;
    delete name;
    delete nameDisp;
    delete nameTxt;
    delete tips;
    showMenu();

}

void MainWindow::restartGame() {

    Score* scoreObj = new Score(qPrintable(*nameTxt),scoreCount);
    if ( highScores->size() < 10 ) highScores->push(scoreObj);
    else if ( scoreObj->getScore() >= highScores->top()->getScore() ) {
        highScores->pop();
        highScores->push(scoreObj);
    }
    writeScores();

    tips->setText("Coffee +life  /  CoderGirl +100pts  /  Bugs -10pts  /  Code -life  /  Kill bugs +10pts\nUse arrow keys to move / spacebar to fire debuggers / hit by blue screen = GAME OVER!!!");
    tips->setFont(QFont("courier", 8));
    tips->setAlignment(Qt::AlignHCenter);
    tips->setAlignment(Qt::AlignVCenter);

    if(isInvincible) {
        isInvincible = false;
        invincible->setText("&invincible");
    }

    if(paused) {
        paused = false;
        pause->setText("&pause");
    }

    for (int unsigned i=0; i<objectList->size(); i++) {
        objectList->at(i)->setZValue(0);
        delete objectList->at(i);
    }

    for (int unsigned i=0; i<debuggerList->size(); i++) {
        debuggerList->at(i)->setZValue(0);
        delete debuggerList->at(i);
    }

    scoreCount = 0;
    livesCount = 5;
    levelCount = 1;

    paused = false;
    isInvincible = false;
    gameOver = false;

    scoreDisp->setText("0");
    livesDisp->setText("5");
    levelDisp->setText("1");

    coderObj->setZValue(0);
    delete coderObj;
    coderObj = new Coder(coderImg, bgImg->width()/2, bgImg->height()/2);
    coderObj->setDir(0);
    coderObj->setZValue(1);
    scene->addItem(coderObj);

    delete timer;
    timer = new QTimer(this);
    interval = 60;
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
    timer->start();
    timerCount = 0;

    delete objectList;
    objectList = new vector<Object*>;
    delete debuggerList;
    debuggerList = new vector<Debugger*>;

    delete bgImg;
    delete bg;
    bgImg = new QPixmap("images/bg.jpg");
    bg = new QGraphicsPixmapItem(*bgImg);
    scene->addItem(bg);

}

void MainWindow::playAudio() {
    if(mediaObject) mediaObject->stop();
    mediaObject = Phonon::createPlayer(Phonon::NoCategory,Phonon::MediaSource("images/cruiser.wav"));
    mediaObject->play();
}

MainWindow::~MainWindow()
{
}

void MainWindow::readScores() {
    string n;
    int s;
    ifstream myfile;
    myfile.open(fn);
    while (true) {
        if (myfile.fail()) break;
        myfile >> n;
        myfile >> s;
        if (myfile.eof()) {
            break;
        }
        Score* scoreObj = new Score(n,s);
        highScores->push(scoreObj);
    }
    while(highScores->size() > 10) highScores->pop();
    myfile.close();
}

void MainWindow::writeScores() {
    while(highScores->size() > 10) highScores->pop();
    ofstream myfile;
    myfile.open(fn);
    while(!(highScores->isEmpty())) {
        myfile << highScores->top()->getName() << " " << highScores->top()->getScore() << endl;
        highScores->pop();
    }
    myfile.close();
    readScores();
}

void MainWindow::displayScores() {
    scoresLayout = new QVBoxLayout;
    delete coder;
    delete code;
    delete bug;
    delete debugger;
    delete blueScrn;
    delete coffee;
    delete superBug;
    delete coderGirl;
    delete icons;
    delete coderPic;
    delete coderTxt;
    delete codePic;
    delete codeTxt;
    delete bugPic;
    delete bugTxt;
    delete debuggerTxt;
    delete debuggerPic;
    delete blueScrnTxt;
    delete blueScrnPic;
    delete coffeePic;
    delete coffeeTxt;
    delete coderGirlPic;
    delete coderGirlTxt;
    delete superBugPic;
    delete superBugTxt;
    delete menuLayout;
    delete welcome;
    delete instructions;
    delete start;
    delete exit;
    delete highScoresButton;
    delete prompt;
    delete username;
    screen->setLayout(scoresLayout);
    model = new QStandardItemModel();
    for (int i=10; i>=1; i--) {
        if(highScores->isEmpty()) break;
        QString str(highScores->top()->getName().c_str());
        QString tmp;
        tmp.setNum(highScores->top()->getScore());
        str = str + " " + tmp + '\n';
        item = new QStandardItem(str);
        item->setFont(QFont("courier", 17.5));
        item->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i,item);
        highScores->pop();
    }
    while(!(highScores->isEmpty())) highScores->pop();
    item = new QStandardItem(QString('\n'));
    item->setFont(QFont("courier", 10));
    model->setItem(0,item);
    readScores();
    highScoreDisp = new QListView;
    highScoreDisp->setModel(model);
    scoresLayout->addWidget(highScoreDisp);
    back = new QPushButton("&back");
    back->setFont(QFont("courier", 14));
    connect(back, SIGNAL(clicked()), this, SLOT(showMenu()));
    scoresLayout->addWidget(back);
}
