#include "Deck.h"
#include <vector>

void Deck::shuffle() {
    srand((unsigned) time(NULL));
    for (int i = 0; i < SHUFFLES; ++i) {
        int x = rand() % 52;
        int y = rand() % 52;
        std::swap(cards[x], cards[y]);
    }
}

void Deck::init() {
    for (int i = 0; i < MAX_CARD_VALUE; ++i) {
        cards.push_back(Card(CLUBS, i));
        cards.push_back(Card(DIAMONDS, i));
        cards.push_back(Card(HEARTS, i));
        cards.push_back(Card(SPADES, i));
    }
}

void Deck::print() const {
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        std::cout << i->printable() << " ";
    }
    std::cout << std::endl;
}

Card Deck::pop() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}
void Deck::push(const Card & card) {
    cards.push_front(card);
}

int Deck::count() const {
    return (int) cards.size();
}

Card Deck::last() const {
    if (cards.empty())
        return Card::noSuchCard();
    return cards.back();
}
