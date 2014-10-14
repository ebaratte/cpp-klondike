
#ifndef __Game_H_
#define __Game_H_

#include <vector>
#include <set>
#include "Deck.h"
#include "Stack.h"
#include "Foundation.h"

#define STACKS 7

class Game {
private:
    Deck deck;

    std::vector<Stack> stacks;
    std::vector<Foundation> foundations;
    std::set<Card> lastMoved;

public:
    Game();

    void distribute();
    void print(bool showHidden = false) const;
    void loop();
    void play();
    bool won();
};


#endif //__Game_H_
