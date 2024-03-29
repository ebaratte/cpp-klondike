A quick implementation of the classical [Klondike](http://en.wikipedia.org/wiki/Klondike_(solitaire)) game, in which the computer plays alone. 

- Cards may be piled by alternate colors, from King to Ace
- Cards from the deck are played one by one (some variants make them play 3 by 3).

Game AI
-------

The IA is clearly not optimal, as it does not try and compare possible moves for each step. Instead, it just plays a move as soon as it detects it is possible. Moves are tried in the following order:
- try to reveal hidden cards
- try to move piles of cards on the [tableau](http://en.wikipedia.org/wiki/Solitaire_terminology)
- try to insert a card from the deck
- try to add a card from the tableau to the [foundation](http://en.wikipedia.org/wiki/Solitaire_terminology)
- try to insert a card from the deck to the foundation

When no move is possible, the game is lost; hidden cards are revealed.


Build & Run
-----------

Built and tested on Linux and Mac OSX (with clang). Other platforms may or may not work.
```
cd build/ 
cmake
make
./klondike
```

Note: your terminal must support UTF-8, and ANSI color codes; otherwise the output will look garbled.
