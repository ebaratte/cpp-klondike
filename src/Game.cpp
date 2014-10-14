#include <sstream>
#include <algorithm>
#include "Game.h"

// Attempt for a portable msleep(int ms)
#ifdef _WIN32
#include <windows.h>
void msleep(int t) { Sleep(t); }
#else
#include <unistd.h>
void msleep(int t) { usleep(1000*t); }
#endif


#define RED_    "\033[1;31m"
#define _RED    "\033[0m"
#define BLUE_   "\033[1;34m"
#define _BLUE   "\033[0m"

Game::Game(): deck(), stacks(STACKS), foundations(), lastMoved() {

    foundations.push_back(Foundation(CLUBS));
    foundations.push_back(Foundation(DIAMONDS));
    foundations.push_back(Foundation(HEARTS));
    foundations.push_back(Foundation(SPADES));

    deck.init();
    deck.shuffle();
    distribute();
}

void Game::distribute() {
    for (int i = 0; i < STACKS; ++i) {
        for (int j = 0; j < (STACKS - i); ++j) {
            stacks[i].pushHidden(deck.pop());
        }
        stacks[i].turnLastCard();
    }

}

void Game::print(bool showHidden) const {
    std::cout << std::endl;
    std::cout << " {" << deck.count() << "} - " << (deck.count() ? deck.last().printable() : "   ") << "     ";

    // Display foundations
    for (int color = CLUBS; color <= SPADES; ++color) {
        if (foundations[color].getVal() >= 0) {
            Card fake((Color) color, foundations[color].getVal());
            if (lastMoved.end() != lastMoved.find(fake)) {
                std::cout << "[" << RED_ << fake.printable() << _RED << " ]  ";
            } else {
                std::cout << "[" << fake.printable() << " ]  ";
            }
        } else {
            std::cout << "[  X  ]  ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Draw stacks
    int row = 0;
    while(row < 19) {
        std::stringstream line("  ");
        for (const Stack & s: stacks) {
            if (row < s.countHidden() + s.countVisible()) {
                if (row < s.countHidden()) {
                    if (showHidden) {
                        line << BLUE_ << s.cardAt(row).printable() << _BLUE;
                    } else {
                        line << "[*]";
                    }
                } else {
                    if (lastMoved.end() != lastMoved.find(s.cardAt(row))) {
                        line << RED_ << s.cardAt(row).printable() << _RED;
                    } else {
                        line << s.cardAt(row).printable();
                    }
                }
            } else {
                line << "   ";
            }
            line << "  "; // spacing between columns
        }
        std::cout << line.str() << std::endl;
        row++;
    }
}

void Game::loop() {
    while(!won()) {
        bool doneSomething = false;
        print();
        msleep(100);

        lastMoved.clear();

        // Check if we can move a pile of visible cards
        for (Stack & s: stacks) {
            const Card & first = s.firstVisible();
            if (!first.invalid()) {

                // special cases: don't move Kings around
                // if they are already at the top of their stack
                if (first.getVal() == KING && s.countHidden() == 0)
                    continue;

                for (Stack & dest: stacks) {
                    if (&s != &dest) {
                        if (dest.canPushCard(first)) {
                            auto visible = s.popAllVisible();
                            for (const Card & c: visible) {
                                lastMoved.insert(c);
                            }
                            dest.pushCards(visible);
                            if (s.shouldTurnCard()) {
                                s.turnLastCard();
                            }
                            doneSomething = true;
                            break;
                        }
                    }
                }
            }
            if (doneSomething)
                continue;
        }

        // Try to push one card from the deck
        int count = deck.count();
        int turned = 0;
        bool pushed = false;
        while (turned < count && !pushed) {
            turned++;
            Card last = deck.last();
            deck.pop();
            for (Stack & dest: stacks) {
                if (dest.canPushCard(last)) {
                    dest.pushCard(last);
                    lastMoved.insert(last);
                    pushed = true;
                    doneSomething = true;
                    break;
                }
            }
            if (!pushed) {
                deck.push(last);
            }
        }

        if (doneSomething)
            continue;

        // We didn't move anything :(
        // Check if we can stack a card up there
        for (Stack& s: stacks) {
            const Card & last = s.lastVisible();
            if (!last.invalid()) {
                if (foundations[last.getColor()].canPushCard(last)) {
                    Card toPush = s.popLastVisible();
                    lastMoved.insert(last);
                    foundations[last.getColor()].pushCard(toPush);
                    if (s.shouldTurnCard()) {
                        s.turnLastCard();
                    }
                    doneSomething = true;
                }
            }
        }

        if (doneSomething)
            continue;

        // We are having a hard time...
        // At least, try to stack a card up there from the deck
        count = deck.count();
        turned = 0;
        while (turned < count) {
            turned++;
            Card last = deck.last();
            deck.pop();
            if (foundations[last.getColor()].canPushCard(last)) {
                lastMoved.insert(last);
                foundations[last.getColor()].pushCard(last);
                doneSomething = true;
                break;
            } else {
                deck.push(last);
            }
        }


        if (!doneSomething) {

            std::cout << "***********************************" << std::endl;
            std::cout << "*              STUCK              *" << std::endl;
            std::cout << "***********************************" << std::endl;
            std::cout << std::endl;
            std::cout << "Remaining in the deck:" << std::endl;
            deck.print();
            print(true);

            return;
        }
    }
    print();
    std::cout << "\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665" << std::endl;
    std::cout << "\u2666              YOU WON !          \u2665" << std::endl;
    std::cout << "\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665\u2660\u2663\u2666\u2665" << std::endl;

}

void Game::play() {
    loop();
}

bool Game::won() {
    return std::all_of(foundations.begin(), foundations.end(), [] (const Foundation & f) {
        return f.getVal() == KING;
    });
}
