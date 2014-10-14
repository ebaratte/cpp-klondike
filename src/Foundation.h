#ifndef __Family_H_
#define __Family_H_

#include "Card.h"

class Foundation {
private:
    Color color;
    int val;
public:
    Foundation(Color c) : color(c), val(-1) {};

    bool canPushCard(const Card & c);
    void pushCard(const Card & c);
    int getVal() const;
};




#endif //__Family_H_
