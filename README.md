# Gomoku

## Description

Gomoku, also called Five in a Row, is an abstract strategy board game.
It is traditionally played with Go pieces (black and white stones) on a Go board, using 15×15 of the 19×19 grid intersections.
The winner is the first player to form an unbroken chain of five stones horizontally, vertically, or diagonally.

## Rules

In the context of this project, we will play with the following additional rules :

+ Capture (As in the Ninuki-renju or Pente variants) : You can remove a pair of your
opponent’s stones from the board by flanking them with your own stones (See the
appendix). This rule adds a win condition : If you manage to capture ten of your
opponent’s stones, you win the game.
+ Game-ending capture : A player that manages to align five stones only wins if the
opponent can not break this alignment by capturing a pair, or if he has already lost
four pairs and the opponent can capture one more, therefore winning by capture.
There is no need for the game to go on if there is no possibility of this happening.
+ No double-threes : It is forbidden to play a move that introduces two free-three
alignments, which would guarantee a win by alignment
