
#ifndef __Stack_H_
#define __Stack_H_

#include "Deck.h"

class Stack {
private:
    std::vector<Card> hidden;
    std::vector<Card> visible;
public:
    void pushHidden(const Card & c);
    void pushCard(const Card & c);
    void pushCards(const std::vector<Card> & cards);

    bool shouldTurnCard() const;
    void turnLastCard();
    bool canPushCard(const Card & c) const;

    int countHidden() const;
    int countVisible() const;
    const Card & cardAt(int index) const;
    Card firstVisible();
    Card lastVisible();

    Card popLastVisible();
    std::vector<Card> popAllVisible();
};

#endif //__Stack_H_
