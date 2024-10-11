#include <iostream>
#include <string>
#include <vector>
#include <cmath>  // für round()

using namespace std;

class Schulfach {
private:
    string name;
    int Schulaufgabe_1,
        Schulaufgabe_2,
        Kurzarbeit,
        Zeugnisnote; 

public:
    // Konstruktor
    Schulfach(string n) : name(n), Schulaufgabe_1(0), Schulaufgabe_2(0), Kurzarbeit(0), Zeugnisnote(0) {}

    // Eingabemethoden für Noten
    void setzeNoten() {
        cout << "\n--------------------------------------------\n";
        cout << "Gebe deine 1. SA-Note im Fach " << name << " ein: ";
        cin >> Schulaufgabe_1;
        cout << "Gebe deine 2. SA-Note im Fach " << name << " ein: ";
        cin >> Schulaufgabe_2;
        cout << "Gebe deine KA-Note im Fach " << name << " ein: ";
        cin >> Kurzarbeit;

        Zeugnisnote = berechneZeugnisnote();
    }

    // Methode zur Berechnung der Gesamtnote
    double berechneGesamtnote() const {
        int GesamtAnzahl_SA = (Schulaufgabe_1 > 0 ? 1 : 0) + (Schulaufgabe_2 > 0 ? 1 : 0);
        int GesamtAnzahl_KA = (Kurzarbeit > 0 ? 1 : 0);

        if (GesamtAnzahl_SA > 0) {
            return ((Schulaufgabe_1 + Schulaufgabe_2) * 2 + Kurzarbeit) / (GesamtAnzahl_SA * 2.0 + GesamtAnzahl_KA);
        }
        return 0.0;
    }

    // Methode zur Berechnung der Zeugnisnote
    int berechneZeugnisnote() const {
        return round(berechneGesamtnote());
    }

    // Ausgabe der Noten und Berechnungen
    void ausgabeNoten() const {
        cout << "\n--------------------------------------------" << endl;
        cout << "Schulfach: " << name << endl;
        cout << "Schulaufgabe 1: " << Schulaufgabe_1 << ", Schulaufgabe 2: " << Schulaufgabe_2 << " | Kurzarbeit: " << Kurzarbeit << endl;
        cout << "Gesamtnote: " << berechneGesamtnote() << " | Zeugnisnote: " << Zeugnisnote << endl;
    }

    // Methode, um die gespeicherte Zeugnisnote zu erhalten
    int getZeugnisnote() const {
        return Zeugnisnote;
    }
};

// Funktion zur Berechnung des Gesamtdurchschnitts
float berechneGesamtdurchschnitt(const vector<Schulfach>& faecher) {
    int summeZeugnisnoten = 0;
    for (const auto& fach : faecher) {
        summeZeugnisnoten += fach.getZeugnisnote();
    }
    return static_cast<float>(summeZeugnisnoten) / faecher.size();
}

int main() {
    // Liste der Fächer
    vector<Schulfach> faecher = {
        Schulfach("IT"), Schulfach("ET"), Schulfach("EL-A"), Schulfach("EL-D"),
        Schulfach("MT"), Schulfach("M1"), Schulfach("D"), Schulfach("E"),
        Schulfach("PuG"), Schulfach("CW")
    };

    // Schleife über die Fächer
    for (Schulfach& fach : faecher) {
        fach.setzeNoten();
        fach.ausgabeNoten();
    }

    // Berechnung des Gesamtdurchschnitts
    float gesamtdurchschnitt = berechneGesamtdurchschnitt(faecher);
    cout << "\n--------------------------------------------" << endl;
    cout << "Gesamtdurchschnitt aller Fächer: " << gesamtdurchschnitt << endl;

    return 0;
}
