#pragma once
#include "Atomkern.h"

class Reaktor
{
private:
    Atomkern inhalt_;

public:
    Reaktor();
    ~Reaktor();

    Reaktor &operator<(const Atomkern &kern);
    Reaktor &operator>(const Atomkern &kern);
    void operator~();
    bool operator==(const Atomkern &kern) const; // Hinzugefügt
};