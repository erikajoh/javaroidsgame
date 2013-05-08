# Game Design Document
This is my game design document. Last updated by Erika Johnson 5/7/13. Keep reading to learn about Javaroids: a world of java.

----

## Overview of Javaroids
In gameplay, the player becomes 'the coder' and uses keyboard controls to move itself around the screen while trying to 'collect coffee', 'get the coder girl' and 'debug code' by shooting 'debuggers' at the 'bug' and 'superbug' objects shooting out of the 'code' objects moving around the screen.

### The 'Things' in Javaroids

#### Thing 1: the code kind of java
##### How it moves: automatically; enters from a random edge of screen and movesacross screen with constant velocity
##### ![code](/images/code.png)

#### Thing 2: bugs in your code
##### How it moves: relative to code; released from each instance of code and moves across screen in same direction as code but with 2x the velocity
##### ![bug](/images/bug.gif)

#### Thing 3: blue screen
##### How it moves: at random time intervals; spirals from the center outward
##### ![crash](/images/crash.gif)

#### Thing 4: debugger
##### How it moves: on user keyboard event; released from player's icon ('the coder') in the direction which the player icon is facing at the time of keyboard event
##### ![debugger](/images/debugger.gif)

#### Thing 5: the coffee kind of java
##### How it moves: at random time intervals; appears in random locations on screen for random amount of time
##### ![coffee](/images/coffee.png)

#### Thing 6: super bug
##### How it moves: just like the normal bugs, except...toward you! It knows.
##### ![superBug](/images/superBug.gif)

#### Thing 7: coder girl
##### How it moves: just like the code, but if you get too close, it'll run away!
##### ![coderGirl](/images/coderGirl.png)

## How to play Javaroids
##### Movement of 'the coder' (i.e. player's icon) is caused by player's keyboard input.
##### Key commands and what they do:
  + `up` moves player icon up on the screen
  + `down` moves player icon down on the screen
  + `left` moves player icon left on the screen
  + `right` moves player icon right on the screen
  + `space` fires debugger object from player icon

### How the score changes in Javaroids
Player starts with 0 points. +10 points each time a debugger fired by the coder collides with a bug or superbug object. -10 points each time a bug or superbug object hits the coder (or if player has 0 points, then -1 life, until 0 lives, then game over). +100 each time player catches a coder girl. +50 points per level up. Player gets unlimited debuggers.

### Life and death of the coder in Javaroids
The coder loses a life each time it collides with a code object. The coder gains a life each time it collides with a coffee object. The coder dies when (a) it runs out of lives, i.e. has 0 lives; or (b) immediately upon collision with a bluescreen object. There are 3 levels of increasing difficulty and the player may click the "invincible" button to become invincible, in which case the player can still collect coffee and fire debuggers to kill bugs, but the player is unaffected by collisions with code, bugs, or the blue screen. When the game is over, a "GAME OVER" message displays on the screen and gameplay stops.

### GUI layout of Javaroids
Upon execution of the program, a menu screen will be displayed with three buttons: `start`, `high scores` and `exit`. If the user presses `start`, the gameplay screen will appear and gameplay will begin. If the user presses `high scores`, the screen will display the high scores and a `back` button will appear to return to the main menu. If the user presses `exit`, the application will quit. The gameplay screen will display the user's name, score, lives, and level, as well as a "tips" section to remind the player of the rules. The gameplay screen will also display four buttons: `invincible`, `pause`, `restart`, and `end`. If the user presses `invincible`, he will become invincible (see "Life and Death of the coder in Javaroids"). Similarly, pressing the button once he is invincible returns the player to an uninvincible state. If the user presses `pause`, all gameplay pauses. Similarly, pressing the button once the game is paused resumes the gameplay. If the user presses `restart`, the game restarts without changing the user's name or returning to the menu screen. If at any time the user presses `end`, gameplay will end and the program will return to the menu screen. There is also a binary code background image on the gameplay screen, and throughout the entire application execution, the USC Campus Cruiser song plays.
##### Main Menu
##### ![mainmenu](/images/mainmenu.png "Main Menu")
##### Gameplay
##### ![javaroids](/images/javaroids.png "Javaroids Gameplay")

### Sources
##### code.png from [http://www.ngeeks.com/en/wp-content/uploads/2012/11/Hello-World.png](http://www.ngeeks.com/en/wp-content/uploads/2012/11/Hello-World.png)
##### debugger.gif from [http://images.lowes.com/product/converted/071549/071549017552lg.jpg](http://images.lowes.com/product/converted/071549/071549017552lg.jpg)
##### bug.gif from [http://us.123rf.com/400wm/400/400/mjp/mjp0606/mjp060600148/425205-big-flying-bug.jpg](http://us.123rf.com/400wm/400/400/mjp/mjp0606/mjp060600148/425205-big-flying-bug.jpg)
##### crash.gif from [http://www.mv.com/ipusers/ullr/BSOD.gif](http://www.mv.com/ipusers/ullr/BSOD.gif)
##### coffee.png from [http://corunco.com/wp-content/uploads/2013/03/CHM-Coffee-Mug1.png](http://corunco.com/wp-content/uploads/2013/03/CHM-Coffee-Mug1.png)
##### coder.gif from [http://supercoders.info/wp-content/uploads/2009/10/supercoder300x400-flip.jpg](http://supercoders.info/wp-content/uploads/2009/10/supercoder300x400-flip.jpg)
##### superBug.gif from [http://4.bp.blogspot.com/_qNCCS94bk8I/TGZ1IDNngTI/AAAAAAAABdc/4iJGHoCY9as/s1600/superbug.gif]
##### coderGirl.png from [http://codingcareer.inhealthcare.com/files/2010/02/supercoder-girl.jpg]
##### bgimg.jpg from [http://upload.wikimedia.org/wikipedia/commons/c/cf/Binary_Code.jpg](http://upload.wikimedia.org/wikipedia/commons/c/cf/Binary_Code.jpg)
##### cruiser.wav is an audio recording of the song playing while on hold with the USC Campus Cruiser phone line (on speakerphone)
##### mainmenu.png and javaroids.png are screenshots of game