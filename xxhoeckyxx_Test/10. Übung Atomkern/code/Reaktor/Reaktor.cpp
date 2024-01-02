#include "Reaktor.h"

using namespace std;

Reaktor::Reaktor() : inhalt_(Atomkern(0, 0)) {}

Reaktor &Reaktor::operator<(const Atomkern &kern)
{
    inhalt_ += kern;
    return *this;
}

Reaktor &Reaktor::operator>(const Atomkern &kern)
{
    inhalt_ -= kern;
    return *this;
}

void Reaktor::operator~()
{
    inhalt_ = Atomkern(0, 0);
}

bool Reaktor::operator==(const Atomkern &kern) const
{
    return (inhalt_ == kern);
}