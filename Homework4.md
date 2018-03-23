Joel Davidson
CSCI 3010 Ind. Project HW4

1.) Plan from previous HW:

I had planned on doing the 3 different levels of difficulty for the computer players. I am now planning on completing at least one more difficulty level and then moving on to the GUI. I think I could spend a lot of time on the different algorithms but I would benefit more from learning about GUI’s. If I get the GUI done, I will begin work on testing and then networking.

2.) What I accomplished:

I was able to get the game GUI mostly working. I took the code from the command line game and began integrating it into the GUI that I made on Qt. The game deals and displays the cards, takes bids and allows the user to play cards but it doesn't give the correct output for the winner of the hand and it only can play one round(13 turns). The GUI makes use of signals and slots, including resource files(card images), buttons, labels, taking input from user in line edit, and the Game class now inherits QObject so it can send signals to the MainWindow class. It took a lot of work to learn how to use Qt and I had to re-write a lot of the original game to make it fit. It is probably easier to begin with the GUI than to make a game in command line first and then try to incorporate that code into the GUI version of the game. 

3.)For next checkpoint:

I will complete the game functionality in the GUI version of the game, add comments, add at least one level of difficulty and then move on to testing. Features that will be added to the game will be the ability to select the winning score to play to and the ability to select the difficulty of the game. I will have a method of testing the game using one of the testing frameworks that we went over in class.