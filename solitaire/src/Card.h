#ifndef _Card_H_
#define _Card_H_

#include <iostream>
#include <stdexcept>

enum Color {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    INVALID_COLOR
};

// card values are indexed from 0 to 12, with
// 0 => ace, 1 => 2, ..., 12 => king

// for easier referencing
#define ACE 0
#define KING 12
#define QUEEN 11
#define JACK 10
#define TEN 9

#define MAX_CARD_VALUE 13


class Card {
private:
    // Just for fun, we _could_ cram it into a single int
    Color color;
    int value;

public:

    Card(): color(INVALID_COLOR),  value(-1) {};
    Card(Color c, int v);
    Card(const Card & c);
    Card &operator=(const Card & rhs);
    bool operator==(const Card & rhs) const;
    bool operator<(const Card & rhs) const;

    Color getColor() const { return color; };
    int getVal() const { return value; };

    std::string printable() const;

    static bool pileableColors(Color lhs, Color rhs);
    static Card noSuchCard();
    bool invalid() const;
};


#endif
