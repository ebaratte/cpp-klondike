#include <assert.h>
#include <vector>
#include "Stack.h"

void Stack::pushHidden(const Card &c) {
    hidden.push_back(c);
}

bool Stack::shouldTurnCard() const {
    return visible.empty() && !hidden.empty();
}

void Stack::turnLastCard() {
    assert(shouldTurnCard());
    Card c = hidden.back();
    hidden.pop_back();
    visible.insert(visible.begin(), c);
}

bool Stack::canPushCard(const Card &c) const {
    if (visible.empty()) {
        return (hidden.empty() && c.getVal() == KING);
    }

    const Card & last = visible.back();

    return (c.getVal() == last.getVal() - 1) &&
            Card::pileableColors(c.getColor(), last.getColor());
}

void Stack::pushCard(const Card &c) {
    assert(canPushCard(c));
    visible.push_back(c);
}
int Stack::countVisible() const {
    return visible.size();
}

int Stack::countHidden() const {
    return hidden.size();
}

const Card & Stack::cardAt(int index) const {
    if (index < countHidden()) {
        return hidden[index];
    }
    return visible[index - countHidden()];
}


Card Stack::firstVisible() {
    if (visible.empty())
        return Card::noSuchCard();
    return visible[0];
}

Card Stack::lastVisible() {
    if (visible.empty())
        return Card::noSuchCard();
    return visible.back();
}

Card Stack::popLastVisible() {
    Card last = visible.back();
    visible.pop_back();
    return last;
}

void Stack::pushCards(const std::vector<Card> &cards) {
    assert(cards.size() > 0);
    assert(canPushCard(cards[0]));

    std::copy(cards.begin(), cards.end(), std::back_inserter(visible));
//    std::for_each(cards.begin(), cards.end(), [&](const Card & c) {
//        visible.push_back(c);
//    });
}

std::vector<Card> Stack::popAllVisible() {
    std::vector<Card> res(visible);
    visible.clear();
    return res;
}
