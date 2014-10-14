#include <sstream>
#include "Card.h"


Card & Card::operator=(const Card &rhs) {
    if (this == &rhs)
        return *this;
    color = rhs.color;
    value = rhs.value;
    return *this;
}

bool Card::operator==(const Card &rhs) const {
    return color == rhs.color && value == rhs.value;
}

bool Card::operator<(const Card & rhs) const {
    if (color != rhs.color)
        return (int) color < (int) rhs.color;
    return value < rhs.value;
}

std::string Card::printable() const {
    std::stringstream out;
    if (value == JACK) {
        out << " J";
    } else if (value == QUEEN) {
        out << " Q";
    } else if (value == KING) {
        out << " K";
    } else if (value == ACE) {
        out << " A";
    } else if (value == TEN) { // special case for proper alignment
        out << "10";
    } else {
        out << " " << (value + 1);
    }

    switch (color) {
        case CLUBS:
            out << "\u2663";
            break;
        case DIAMONDS:
            out << "\u2666";
            break;
        case HEARTS:
            out << "\u2665";
            break;
        case SPADES:
            out << "\u2660";
            break;
        default:
            break;
    }
    return out.str();
};

bool Card::pileableColors(Color lhs, Color rhs) {
    switch (lhs) {
        case CLUBS:
        case SPADES:
            return rhs == HEARTS || rhs == DIAMONDS;
        case DIAMONDS:
        case HEARTS:
            return rhs == CLUBS || rhs == SPADES;
        default:
            return false;
    }
}

Card::Card(const Card &c): color(c.color), value(c.value) {}

Card::Card(Color c, int v): color(c), value(v) {
    if (value >= MAX_CARD_VALUE) {
        throw std::range_error("invalid card value");
    }
}

bool Card::invalid() const {
    return value == -1;
}

Card Card::noSuchCard() {
    return Card(INVALID_COLOR, -1);
}
