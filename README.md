# Scopa
A fully playable version of Scopa (a popular italian card game) made in C++ and OpenCV.


<b>Features:</b>
- Play Scopa against a CPU opponent that follows efficient tactics based on stategies that a real human player would follow.
- As a stepping stone for new platers, you can choose to play with an "open hand" mode, where all opponents cards are visible to you: it's also an easy way to prove that my CPU doesn't cheat! 
- All cards are extracted from real life pictures where they are laid on tables/surfaces and given the right value on the fly thanks to the object recognition tools offered by OpenCV. This means you can substitute my photos with your own if you have the same type of cards and test if they are correctly recognized thanks to the "test" option!


<b>Comments:</b><br/>
Ever since I worked on side projects such as Snake, Tetris and Battleship, I knew I wanted to bring a game as my final project for the bachelor's degree.<br/>
I immediately thought of a card game that you could play against a CPU, and I knew I could deliver on that thanks to the experience I gained while developing the AI on these previous games. And since my project was linked to a subject that dealt with object recognition, I also had to train some Cascade Trainers with OpenCV that could recognize my cards by simply analyzing pictures in which they appeared. This last process was painful because you have limited control (and resources) while training these Cascades, so you have to hope the algorithms do their work correctly, while you're sitting there waiting. It's akin to a rally race: if in my previous programs I was the driver, fully in control of what I was doing, now I was the co-pilot, telling the pilot what to do and hoping for the best, that he wasn't going to crash the car with both of us inside.<br/>
At the end, though, I managed to train a Cascade that could recognize correctly all the cards in 120 different pictures, without false positives and negatives. The work on the CPU was far less annoying thankfully: I had to show the program to my teacher with a live demo and watching him trying to guess the next move of the CPU, and then seeing the AI making that very same move right after, was just priceless.<br/>
For more information, you can read my relation (written in Italian) that covers everything there's to know about the creation of this program.


<b>Install Instructions:</b><br/>
Execute "cmake ." on the directory that contains CMakeLists.txt, then "make" and finally execute "./Scopa".
The program is compatible with Linux systems only and OpenCV is needed.

<b>NOTE:</b><br/> 
In order to train the Cascade, I used a version of OpenCV that came with the virtual machine used by the course (https://www.marrtino.org/software). There may be compatible issues, or the Cascade may work incorrectly, if the program is used with previous or later versions of OpenCV.

