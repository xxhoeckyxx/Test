#include <iostream>
#include <string>
#include <vector>
#include <cmath>  // für round()

using namespace std;

int main() {
    // Liste der Fächer
    vector<string> Schulfach = { "IT", "ET", "EL-A", "EL-D", "MT", "M1", "D", "E", "PuG", "CW" };

    // Schleife über die Fächer
    for (int i = 0; i < 10; i++) {
        cout << "Eingabe für das Fach: " << Schulfach[i] << endl;

        // Eingabe der Noten
        int SA1, SA2, KA;
        cout << "Gebe deine 1. SA-Note im Fach ein: ";
        cin >> SA1;
        cout << "Feedback SA1: " << SA1 << "!" << endl;

        cout << "Gebe deine 2. SA-Note im Fach ein: ";
        cin >> SA2;
        cout << "Feedback SA2: " << SA2 << "!" << endl;

        cout << "Gebe deine 1. KA-Note im Fach ein: ";
        cin >> KA;
        cout << "Feedback KA1: " << KA << "!" << endl;

        // Variableninitialisierung
        int GesamtAnzahl_SA = 0;
        int GesamtAnzahl_KA = 0;
        double Gesamtnote = 0;
        int Zeugnisnote = 0;
        int SA1_RAM = 0, SA2_RAM = 0, KA_RAM = 0;

        // Berechnung der GesamtAnzahl_SA:
        if (SA1 > 0) SA1_RAM = 1;
        if (SA2 > 0) SA2_RAM = 1;
        if (KA > 0) KA_RAM = 1;

        GesamtAnzahl_SA = SA1_RAM + SA2_RAM;
        GesamtAnzahl_KA = KA_RAM;

        // Berechnung der Gesamtnote im jeweiligen Fach:
        if (GesamtAnzahl_SA > 0) {
            Gesamtnote = ((SA1 + SA2) * 2 + KA) / (GesamtAnzahl_SA * 2.0 + GesamtAnzahl_KA);
        }

        // Berechnung der Zeugnisnote im jeweiligen Fach:
        Zeugnisnote = round(Gesamtnote);

        // Ausgabe der Berechnung:
        cout << "Schulfach: " << Schulfach[i] << endl;
        cout << "--------------------------------------------" << endl;
        cout << "SA: " << SA1 << ", " << SA2 << " | KA: " << KA << endl;
        cout << "Gesamtnote: " << Gesamtnote << " | Zeugnisnote: " << Zeugnisnote << endl;
    }

    return 0;
}