# Game Design Document
This is my game design document. Keep reading to learn about Javaroids: a world of java.

----

## Overview of Javaroids
In gameplay, the player becomes 'the coder' and uses keyboard controls to move itself around the screen while trying to 'complete code' by shooting the 'hello, world' objects floating around the screen.

### The 'Things' in Javaroids

#### Thing 1: the code kind of java
##### How it moves: automatically; all over the screen at a constant speed
##### ![code](/images/code.png "http://www.ngeeks.com/en/wp-content/uploads/2012/11/Hello-World.png")

#### Thing 2: bugs in your code
##### How it moves: at random time intervals; released from each instance of thing 2 and in random directions
##### ![bug](/images/bug.jpg "http://us.123rf.com/400wm/400/400/mjp/mjp0606/mjp060600148/425205-big-flying-bug.jpg")

#### Thing 3: computer crash
##### How it moves: at random time intervals; spirals from the center outward
##### ![crash](/images/crash.gif "http://www.mv.com/ipusers/ullr/BSOD.gif")

#### Thing 4: debugger
##### How it moves: on user keyboard event; released from player's icon ('the coder') in the direction which the player icon is facing at the time of keyboard event
##### ![debugger](/images/debugger.jpg "http://www.iconshock.com/img_jpg/REALVISTA/development/jpg/128/debugger_icon.jpg")

#### Thing 5: the coffee kind of java
##### How it moves: at random time intervals; appears in random locations on screen for random amount of time
##### ![coffee](/images/coffee.png "http://corunco.com/wp-content/uploads/2013/03/CHM-Coffee-Mug1.png")

## How to play Javaroids
##### Movement of 'the coder' (i.e. player's icon) is caused by player's keyboard input.
##### Key commands and what they do:
  + `up` moves player icon forward (based on orientation)
  + `down` moves player icon backward (based on orientation)
  + `left` rotates player icon orientation 90 degrees counterclockwise
  + `right` rotates player icon orientation 90 degrees clockwise
  + `space` fires debugger object from player icon

### How the score changes in Javaroids
Player starts with 0 points. +10 points each time a debugger fired by the coder collides with a code object. -10 points each time a bug object hits the coder.

### Life and death of the coder in Javaroids
The coder loses a life each time it collides with a code object. The coder gains a life each time it collides with a coffee object. The coder dies when (a) it runs out of lives, or (b) immediately upon collision with a computer crash object.

### GUI layout of Javaroids
Upon execution of the program, a start screen will be displayed with one buttons: `start game`. If the user presses `start game`, the gameplay screen will appear and gameplay will begin. The gameplay screen will display one button: `end game`. If at any time the user presses `end game`, gameplay will end and the program will return to the start screen.
##### Main Menu
##### ![mainmenu](/images/mainmenu.png "Main Menu")
##### Gameplay
##### ![javaroids](/images/javaroids.png "Javaroids Gameplay")

### Sources
##### code.png from [http://www.ngeeks.com/en/wp-content/uploads/2012/11/Hello-World.png](http://www.ngeeks.com/en/wp-content/uploads/2012/11/Hello-World.png)
##### debugger.jpg from [http://www.iconshock.com/img_jpg/REALVISTA/development/jpg/128/debugger_icon.jpg](http://www.iconshock.com/img_jpg/REALVISTA/development/jpg/128/debugger_icon.jpg)
##### bug.jpg [http://us.123rf.com/400wm/400/400/mjp/mjp0606/mjp060600148/425205-big-flying-bug.jpg](http://us.123rf.com/400wm/400/400/mjp/mjp0606/mjp060600148/425205-big-flying-bug.jpg)
##### crash.gif [http://www.mv.com/ipusers/ullr/BSOD.gif](http://www.mv.com/ipusers/ullr/BSOD.gif)
##### coffee.png from [http://corunco.com/wp-content/uploads/2013/03/CHM-Coffee-Mug1.png](http://corunco.com/wp-content/uploads/2013/03/CHM-Coffee-Mug1.png)
##### coder.jpg from [http://supercoders.info/wp-content/uploads/2009/10/supercoder300x400-flip.jpg](http://supercoders.info/wp-content/uploads/2009/10/supercoder300x400-flip.jpg)
##### mainmenu.png and javaroids.png created in Paintbrush for Mac

