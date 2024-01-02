#include <iostream>
#include <string>

class Atomkern
{
private:
    std::string symbol_;
    int massenzahl_;
    int ordnungszahl_;

public:
    Atomkern(const std::string &symbol, int massenzahl, int ordnungszahl);

    // Getter-Funktionen
    int ordnungszahl() const;
    int massenzahl() const;
    std::string symbol() const;

    // Operatoren überladen
    Atomkern operator+(const Atomkern &other) const;
    Atomkern &operator+=(const Atomkern &other);
    Atomkern operator-(const Atomkern &other) const;
    Atomkern &operator-=(const Atomkern &other);
    Atomkern operator*(int scalar) const;
    bool operator==(const Atomkern &other) const;

    // Ausgabeoperator überladen
    friend std::ostream &operator<<(std::ostream &os, const Atomkern &atomkern);

    // Statische, konstante Klassenelemente für Protonen und Neutronen
    static const Atomkern PROTON;
    static const Atomkern NEUTRON;
};