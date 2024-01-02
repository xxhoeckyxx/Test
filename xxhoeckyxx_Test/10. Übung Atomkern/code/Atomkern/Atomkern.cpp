#include "Atomkern.h"

const Atomkern Atomkern::PROTON("H", 1, 1);
const Atomkern Atomkern::NEUTRON("h", 1, 0);

Atomkern::Atomkern(const std::string &symbol, int massenzahl, int ordnungszahl)
    : symbol_(symbol), massenzahl_(massenzahl), ordnungszahl_(ordnungszahl) {}

int Atomkern::ordnungszahl() const
{
    return ordnungszahl_;
}

int Atomkern::massenzahl() const
{
    return massenzahl_;
}

std::string Atomkern::symbol() const
{
    return symbol_;
}

Atomkern Atomkern::operator+(const Atomkern &other) const
{
    return Atomkern(symbol_, massenzahl_ + other.massenzahl_, ordnungszahl_ + other.ordnungszahl_);
}

Atomkern &Atomkern::operator+=(const Atomkern &other)
{
    ordnungszahl_ += other.ordnungszahl_;
    massenzahl_ += other.massenzahl_;
    return *this;
}

Atomkern Atomkern::operator-(const Atomkern &other) const
{
    return Atomkern(symbol_, massenzahl_ - other.massenzahl_, ordnungszahl_ - other.ordnungszahl_);
}

Atomkern &Atomkern::operator-=(const Atomkern &other)
{
    ordnungszahl_ -= other.ordnungszahl_;
    massenzahl_ -= other.massenzahl_;
    return *this;
}

Atomkern Atomkern::operator*(int scalar) const
{
    return Atomkern(symbol_, massenzahl_ * scalar, ordnungszahl_ * scalar);
}

bool Atomkern::operator==(const Atomkern &other) const
{
    return (ordnungszahl_ == other.ordnungszahl_) && (massenzahl_ == other.massenzahl_);
}

std::ostream &operator<<(std::ostream &os, const Atomkern &atomkern)
{
    os << atomkern.symbol() << "(" << atomkern.massenzahl() << "," << atomkern.ordnungszahl() << ")";
    return os;
}
