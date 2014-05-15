#include <assert.h>
#include "Foundation.h"

bool Foundation::canPushCard(const Card & c) {
    return c.getColor() == color && c.getVal() == val + 1;
}

void Foundation::pushCard(const Card & c) {
    assert(canPushCard(c));
    val++;
}

int Foundation::getVal() const { return val; }
