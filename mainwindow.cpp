#include "mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QtGui>
#include <QRectF>

MainWindow::MainWindow()  {

    scene = new QGraphicsScene();
    screen = new QWidget;
    screen->setWindowTitle("JAVAROIDS");
    screen->setFixedSize(600, 650);
    gameLayout = NULL;
    menuLayout = NULL;
    mediaObject = NULL;
    QTimer* audioTimer = new QTimer();
    audioTimer->setInterval(24000);
    connect(audioTimer, SIGNAL(timeout()), this, SLOT(playAudio()));
    audioTimer->start();
    playAudio();
    timer = NULL;
    srand(time(0));
    showMenu();

}

void MainWindow::newGame(){

  if( (username->text()).length() > 20 || (username->text()).length() < 2 ){
    QMessageBox box;
    box.setWindowTitle("Error");
    box.setText("Please enter a name with length 2-20 characters.");
    box.exec();
    return;
  }

  grabKeyboard();

  name = new QLabel("/Coder's name:");
  name->setFont(QFont("courier", 10));
  name->setAlignment(Qt::AlignHCenter);
  name->setAlignment(Qt::AlignVCenter);

  QString nameTxt = username->text();
  nameDisp = new QLabel(nameTxt);
  nameDisp->setFont(QFont("courier", 10));
  nameDisp->setAlignment(Qt::AlignHCenter);
  nameDisp->setAlignment(Qt::AlignVCenter);

  scoreCount = 0;
  livesCount = 5;
  levelCount = 0;

  paused = false;
  isInvincible = false;
  gameOver = false;

  view = new QGraphicsView(scene);
  gameLayout = new QVBoxLayout;
  delete menuLayout;
  delete welcome;
  delete instructions;
  delete start;
  delete exit;
  delete prompt;
  delete username;

  screen->setLayout(gameLayout);

  topBar = new QHBoxLayout;

  status = new QHBoxLayout;

  restart = new QPushButton("re&start");
  connect(restart, SIGNAL(clicked()), this, SLOT(restartGame()));
  restart->setFont(QFont("courier", 10));

  end = new QPushButton("&end");
  connect(end, SIGNAL(clicked()), this, SLOT(showMenu()));
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

  tips = new QLabel("Kill bugs with debuggers (+10), collect coffee (+1), avoid bugs (-10), avoid code (-1)\nUse arrow keys to move; spacebar to fire debuggers; hit by blue screen = GAME OVER!!!"); 
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
  QGraphicsPixmapItem *bg = new QGraphicsPixmapItem(*bgImg);
  scene->addItem(bg);

  coderImg = new QPixmap("images/coderIcon.gif");
  coderObj = new Coder(coderImg, bgImg->width()/2, bgImg->height()/2);
  coderObj->setDir(0);
  scene->addItem(coderObj);

  codeImg = new QPixmap("images/codeIcon.png");
  coffeeImg = new QPixmap("images/coffeeIcon.png");
  bluescreenImg = new QPixmap("images/crashIcon.gif");
  bugImg = new QPixmap("images/bugIcon.gif");
  debuggerImgLeft = new QPixmap("images/debuggerIconLeft.gif");
  debuggerImgUp = new QPixmap("images/debuggerIconUp.gif");
  debuggerImgRight = new QPixmap("images/debuggerIconRight.gif");
  debuggerImgDown = new QPixmap("images/debuggerIconDown.gif");

  timer = new QTimer(this);
  interval = 120;
  timer->setInterval(interval);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  timer->start();
  timerCount = 0;

  objectList = new vector<Object*>;
  debuggerList = new vector<Debugger*>;

}

void MainWindow::showMenu(){

  if(timer) delete timer;

  releaseKeyboard();

  welcome = new QLabel("Welcome to\nJAVAROIDS\n(A world of java)");
  welcome->setFont(QFont("courier", 36, QFont::Bold));
  welcome->setAlignment(Qt::AlignHCenter);

  instructions = new QLabel("\nYou are the coder.\nKill bugs with debuggers. (+10 pts)\nCollect coffee. (+1 life)\nDon't get hit by bugs. (-10 pts)\nDon't get hit by code. (-1 life)\n\nIf you get hit by the blue screen of death...game over.\nUse the arrow keys to move and spacebar to fire debuggers.\nGood luck!\n:)\n");
  instructions->setFont(QFont("courier", 10));
  instructions->setAlignment(Qt::AlignHCenter);

  start = new QPushButton("&start");
  start->setFont(QFont("courier", 16));
  connect(start, SIGNAL(clicked()), this, SLOT(newGame()));
  exit = new QPushButton("&exit");
  exit->setFont(QFont("courier", 16));
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
  bugTxt = new QLabel("a bug");
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
  blueScrnTxt = new QLabel("bluescreen");
  blueScrnTxt->setAlignment(Qt::AlignHCenter);
  blueScrnTxt->setFont(QFont("courier", 12));
  blueScrn->addWidget(blueScrnPic);
  blueScrn->addWidget(blueScrnTxt);

  menuLayout = new QVBoxLayout;
  icons = new QHBoxLayout;
  icons->addLayout(coder);
  icons->addLayout(debugger);
  icons->addLayout(coffee);
  icons->addLayout(bug);
  icons->addLayout(code);
  icons->addLayout(blueScrn);

  username = new QLineEdit("");
  prompt = new QLabel("\n\nEnter yo name to start debuggin': ");
  prompt->setAlignment(Qt::AlignHCenter);
  username->setFont(QFont("courier", 14, QFont::Bold));
  username->setAlignment(Qt::AlignHCenter);
  prompt->setFont(QFont("courier", 14, QFont::Bold));

  if(gameLayout){
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
    delete tips;
  }

  screen->setLayout(menuLayout);
  menuLayout->addWidget(welcome);
  menuLayout->addWidget(instructions);
  menuLayout->addLayout(icons);
  menuLayout->addWidget(prompt);
  menuLayout->addWidget(username);
  menuLayout->addWidget(start);
  menuLayout->addWidget(exit);

}

void MainWindow::show() {
    //This is how we get our view displayed.
    screen->show();
}

void MainWindow::handleTimer(){

  if(!livesCount){
    tips->setText("SORRY, GAME OVER");
    tips->setFont(QFont("courier",16));
    tips->setAlignment(Qt::AlignHCenter);
    gameOver = true;
    return;
  }

  if(paused){
    return;
  }

  if (timerCount%500 == 0 && interval > 15){
    levelCount++;
    interval /= 2;
    QString levelText;
    levelText.setNum(levelCount);
    levelDisp->setText(levelText);
    timer->setInterval(interval);
   }

  int caseNum = rand()%4;
  int moveDir = rand()%3;

  if (timerCount%70 == 0){
    if (caseNum == 0){ //enter from left
      codeObj = new Code(codeImg, 2, rand()%508 + 2);
      if (moveDir == 0) codeObj->setDir(2);
      else if (moveDir == 1) codeObj->setDir(4);
      else if (moveDir == 2) codeObj->setDir(6);
    } else if (caseNum == 1){ //enter from top
      codeObj = new Code(codeImg, rand()%543 + 2, 2);
      if (moveDir == 0) codeObj->setDir(3);
      else if (moveDir == 1) codeObj->setDir(6);
      else if (moveDir == 2) codeObj->setDir(7);
    } else if (caseNum == 2){ //enter from right
      codeObj = new Code(codeImg, 543, rand()%508 + 2);
      if (moveDir == 0) codeObj->setDir(0);
      else if (moveDir == 1) codeObj->setDir(5);
      else if (moveDir == 2) codeObj->setDir(7);
    } else if (caseNum == 3){ //enter from bottom
      codeObj = new Code(codeImg, rand()%543 + 2, 508);
      if (moveDir == 0) codeObj->setDir(1);
      else if (moveDir == 1) codeObj->setDir(4);
      else if (moveDir == 2) codeObj->setDir(5);
    }
    bugObj = new Bug(bugImg, codeObj->getX(), codeObj->getY());
    bugObj->setDir(codeObj->getDir());
    scene->addItem(bugObj);
    scene->addItem(codeObj);
    objectList->push_back(codeObj);
    objectList->push_back(bugObj);
  }
  if (timerCount%65 == 0){
    coffeeObj = new Coffee(coffeeImg,rand()%543 + 2,rand()%508 + 2);
    scene->addItem(coffeeObj);
    objectList->push_back(coffeeObj);
  }
  if (timerCount && timerCount%300 == 0){
    bluescreenObj = new Bluescreen(bluescreenImg,bgImg->width()/2,bgImg->height()/2);
    scene->addItem(bluescreenObj);
    objectList->push_back(bluescreenObj);
    bluescreenObj->setDir(rand()%4);
  }

for (int i=debuggerList->size()-1; i>=0; i--){
    for (int j=objectList->size()-1; j>=0; j--){
      if (debuggerList->at(i)->collidesWithItem(objectList->at(j)) && !(objectList->at(j)->isCoffee()) && !(objectList->at(j)->isBluescreen()) && !(objectList->at(j)->isCode())){
	scoreCount += 10;
	QString scoreText;
	scoreText.setNum(scoreCount);
	scoreDisp->setText(scoreText);
	debuggerList->at(i)->hide();
	objectList->at(j)->hide();
      }
    }
    if (debuggerList->at(i)->getX() + debuggerList->at(i)->width() >= bgImg->width()-9 || debuggerList->at(i)->getX() <= 9 || debuggerList->at(i)->getY() + debuggerList->at(i)->height() >= bgImg->height()-9 || debuggerList->at(i)->getY() <= 9) {
      debuggerList->at(i)->hide();
      debuggerList->erase(debuggerList->begin()+i);
    } else debuggerList->at(i)->move();
  }

  for (int i=objectList->size()-1; i>=0; i--){
    if (coderObj->collidesWithItem(objectList->at(i))){
      if (objectList->at(i)->isBug() && !isInvincible){
	if (scoreCount) scoreCount -= 10;
	else livesCount--;
      }
      if (objectList->at(i)->isCode() && !isInvincible) livesCount--;
      if (objectList->at(i)->isCoffee()) livesCount++;
      if ( objectList->at(i)->isBluescreen() && !isInvincible ) livesCount = 0;
      QString scoreText, livesText;
      scoreText.setNum(scoreCount);
      livesText.setNum(livesCount);
      scoreDisp->setText(scoreText);
      livesDisp->setText(livesText);
      if ((!(objectList->at(i)->isDebugger()) && !isInvincible && !(objectList->at(i)->isBluescreen())) || objectList->at(i)->isCoffee() ){
	objectList->at(i)->hide();
	objectList->erase(objectList->begin()+i);
      } else {
	objectList->at(i)->move();
      }
    } else if (objectList->at(i)->getX() + objectList->at(i)->width() >= bgImg->width()-1 || objectList->at(i)->getX() <= 1 || objectList->at(i)->getY() + objectList->at(i)->height() >= bgImg->height()-1 || objectList->at(i)->getY() <= 1){
      objectList->at(i)->hide();
      objectList->erase(objectList->begin()+i);
    } else if (objectList->at(i)->isCoffee()){
      if (rand()%200 == 0){
	objectList->at(i)->hide();
	objectList->erase(objectList->begin()+i);
      }
    } else objectList->at(i)->move();
  }

  for (int i=debuggerList->size()-1; i>0; i--){
    if (!(debuggerList->at(i)->isVisible())) debuggerList->erase(debuggerList->begin()+i);
  }

  for (int i=objectList->size()-1; i>0; i--){
    if (!(objectList->at(i)->isVisible())) objectList->erase(objectList->begin()+i);
  }

  timerCount++;

}

void MainWindow::keyPressEvent(QKeyEvent* event){
  event = event;
  if(paused || gameOver) return;
  if(event->key() == Qt::Key_Left && ( (coderObj->getDir() == 0 && coderObj->getX() > 15) || coderObj->getX() > 45 ) ){
    coderObj->setDir(0);
    coderObj->move();
  } else if(event->key() == Qt::Key_Right && coderObj->getX() + 15 < bgImg->width()){
    coderObj->setDir(2);
    coderObj->move();
  } else if(event->key() == Qt::Key_Up && coderObj->getY() > 15){
    coderObj->setDir(1);
    coderObj->move();
  } else if(event->key() == Qt::Key_Down && ( (coderObj->getDir() == 3 && coderObj->getY() + 15 < bgImg->height()) || coderObj->getY() + 40 < bgImg->height() ) ){
    coderObj->setDir(3);
    coderObj->move();
  } else if(event->key() == Qt::Key_Space){
    if (coderObj->getDir() == 0 && coderObj->getX() > 5 + debuggerImgLeft->width()){
      debuggerObj = new Debugger(debuggerImgLeft,coderObj->getX()-debuggerImgLeft->width(),coderObj->getY());
      debuggerObj->setDir(coderObj->getDir());
      debuggerList->push_back(debuggerObj);
      scene->addItem(debuggerObj);
    } else if (coderObj->getDir() == 1 && coderObj->getY() > 5 + debuggerImgUp->height()){
      debuggerObj = new Debugger(debuggerImgUp,coderObj->getX()-debuggerImgUp->width(),coderObj->getY()-debuggerImgUp->height());
      debuggerObj->setDir(coderObj->getDir());
      debuggerList->push_back(debuggerObj);
      scene->addItem(debuggerObj);
    } else if (coderObj->getDir() == 2 && coderObj->getX() + 5 < bgImg->width() - debuggerImgRight->width()){
      debuggerObj = new Debugger(debuggerImgRight,coderObj->getX(),coderObj->getY());
      debuggerObj->setDir(coderObj->getDir());
      debuggerList->push_back(debuggerObj);
      scene->addItem(debuggerObj);
    } else if (coderObj->getDir() == 3 && coderObj->getY() + 5 < bgImg->height() - debuggerImgDown->height()){
      debuggerObj = new Debugger(debuggerImgDown,coderObj->getX()-debuggerImgDown->width(),coderObj->getY());
      debuggerObj->setDir(coderObj->getDir());
      debuggerList->push_back(debuggerObj);
      scene->addItem(debuggerObj);
    }
  }
}

void MainWindow::setPaused(){
  if(paused){
    paused = false;
    pause->setText("&pause");
  }
  else {
    paused = true;
    pause->setText("un&pause");
  }
}

void MainWindow::setInvincible(){
  if(isInvincible){
    isInvincible = false;
    invincible->setText("&invincible");
  } else {
    isInvincible = true;
    invincible->setText("un&invincible");
  }
}

void MainWindow::restartGame(){

  tips->setText("Kill bugs with debuggers (+10), collect coffee (+1), avoid bugs (-10), avoid code (-1)\nUse arrow keys to move; spacebar to fire debuggers; hit by blue screen = GAME OVER!!!"); 
  tips->setFont(QFont("courier", 8));
  tips->setAlignment(Qt::AlignHCenter);
  tips->setAlignment(Qt::AlignVCenter);

  if(isInvincible){
    isInvincible = false;
    invincible->setText("&invincible");
  }

  if(paused){
    paused = false;
    pause->setText("&pause");
  }

  for (int unsigned i=0; i<objectList->size(); i++){
    delete objectList->at(i);
  }

  for (int unsigned i=0; i<debuggerList->size(); i++){
    delete debuggerList->at(i);
  }

  scoreCount = 0;
  livesCount = 5;
  levelCount = 0;

  paused = false;
  isInvincible = false;
  gameOver = false;

  scoreDisp->setText("0");
  livesDisp->setText("5");
  levelDisp->setText("1");

  delete coderObj;
  coderObj = new Coder(coderImg, bgImg->width()/2, bgImg->height()/2);
  coderObj->setDir(0);
  scene->addItem(coderObj);

  delete timer;
  timer = new QTimer(this);
  interval = 120;
  timer->setInterval(interval);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  timer->start();
  timerCount = 0;

  delete objectList;
  objectList = new vector<Object*>;
  delete debuggerList;
  debuggerList = new vector<Debugger*>;
}

void MainWindow::playAudio(){
  if(mediaObject) mediaObject->stop();
  mediaObject = Phonon::createPlayer(Phonon::NoCategory,Phonon::MediaSource("images/cruiser.wav"));
  mediaObject->play();
}

MainWindow::~MainWindow()
{
}
