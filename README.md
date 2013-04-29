# Game - Programming Assignments Private Repository
### Student Information
  + Name: Erika Johnson
  + USC Email: erikajoh@usc.edu
  + USC ID: 3892385661

### Game Information
  + Game Name: Javaroids
  + Game Description: In gameplay, the player becomes 'the coder' and uses keyboard controls to move itself around the screen while trying to 'collect coffee' and 'debug code' by shooting 'debuggers' at the 'bug' objects shooting out of the 'code' objects moving around the screen.
  + [Game Design Doc](GameDesignDoc.md)
  + Note: errors printed in console are a problem with Qt. See #236 in the PA Issue Tracker.


### Compile & Run Instructions
The grader should use the following procedure to compile and run the code:
####Compile Instructions
```shell
sudo apt-get install libphonon-dev
qmake
make
```
####Doxygen Instructions
```shell
doxygen -g config.txt
doxygen config.txt
``` 

####Command to run
```shell
./game_erikajoh
```

### Screenshots
##### Main Menu
##### ![mainmenu](/images/mainmenu.png "Main Menu")
##### Gameplay
##### ![javaroids](/images/javaroids.png "Javaroids Gameplay")