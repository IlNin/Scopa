# Scopa
A fully playable version of Scopa (a popular italian card game) made in C++ and OpenCL. 
Ever since I worked on side projects such as Snake, Tetris and Battleship, I knew I wanted to bring 
a game as my final project for the bachelor's degree. I immediately thought of a card game that you
could play against a CPU, and I knew I could deliver on that thanks to the experience I gained while
developing the AI on these previous games. And since my project was linked to a subject that dealt with
object recognition, I also had to train some Cascade Trainers with OpenCV that could recognize my cards
by simply analyzing pictures in which they appeared. This last process was painful because you have limited
control (and resources) while training these Cascades, so you have to hope the algorithms do their work
correctly, while you're sitting there waiting. It's akin to a rally race: if in my previous programs I was
the driver, fully in control of what I was doing, now I was the co-pilot, telling the pilot what to do and 
hoping for the best, that he wasn't going to crash the car with both of us inside.
At the end, though, I managed to train a Cascade that could recognize correctly all the cards in 
120 different pictures, without false positives and negatives.
The work on the CPU was far less annoying thankfully: I had to show the program to my teacher with a live 
demo and watching him trying to guess the next move of the CPU, and then seeing the AI making that same 
move, was just priceless.
For more information, you can read my relation (written in Italian) that covers everything there's to
know about the creation of this program.

LIST OF FILES:
Carta.hpp
Carta.cpp
Mazzo.hpp
Mazzo.cpp
Giocatore.hpp
Giocatore.cpp
Utente.hpp
Utente.cpp
CPU.hpp
CPU.cpp
ScopaUtil.hpp
ScopaUtil.cpp
Scopa.cpp
CMakeLists.txt
CarteCascadeB.xml
CarteA (folder)
CarteB (folder)
CarteC (folder)
Target (folder)
Grafica (folder)

INSTALL INSTRUCTIONS:
Execute "cmake ." on the directory that contains CMakeLists.txt, then "make" and finally execute "./Scopa".
The program is compatible with Linux systems only.
NOTE: In order to train the Cascade, I used a version of OpenCV that came with the virtual machine used by the course
(https://www.marrtino.org/software). There may be compatible issues, or the Cascade may work incorrectly, if the program
is used with previous or later versions of OpenCV.

