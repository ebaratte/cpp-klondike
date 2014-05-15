#ifndef __Deck_H_
#define __Deck_H_

#include <deque>
#include "Card.h"

#define SHUFFLES 2000

class Deck {
  private:
    std::deque<Card> cards;

  public:
    void init();
    void shuffle();
    void print() const;

    Card pop();
    void push(const Card & card);
    int count() const;

    Card last() const;
};

#endif //__Deck_H_
