import math

class Schulfach:
    def __init__(self, name):
        self.name = name
        self.Schulaufgabe_1 = 0
        self.Schulaufgabe_2 = 0
        self.Kurzarbeit = 0
        self.Zeugnisnote = 0

    # Eingabemethoden für Noten
    def setze_noten(self):
        print("\n--------------------------------------------")
        self.Schulaufgabe_1 = int(input(f"Gebe deine 1. SA-Note im Fach {self.name} ein: "))
        self.Schulaufgabe_2 = int(input(f"Gebe deine 2. SA-Note im Fach {self.name} ein: "))
        self.Kurzarbeit = int(input(f"Gebe deine KA-Note im Fach {self.name} ein: "))
        self.Zeugnisnote = self.berechne_zeugnisnote()

    # Methode zur Berechnung der Gesamtnote
    def berechne_gesamtnote(self):
        GesamtAnzahl_SA = (1 if self.Schulaufgabe_1 > 0 else 0) + (1 if self.Schulaufgabe_2 > 0 else 0)
        GesamtAnzahl_KA = 1 if self.Kurzarbeit > 0 else 0

        if GesamtAnzahl_SA > 0:
            return ((self.Schulaufgabe_1 + self.Schulaufgabe_2) * 2 + self.Kurzarbeit) / (GesamtAnzahl_SA * 2 + GesamtAnzahl_KA)
        return 0.0

    # Methode zur Berechnung der Zeugnisnote
    def berechne_zeugnisnote(self):
        return round(self.berechne_gesamtnote())

    # Ausgabe der Noten und Berechnungen
    def ausgabe_noten(self):
        print("\n--------------------------------------------")
        print(f"Schulfach: {self.name}")
        print(f"Schulaufgabe 1: {self.Schulaufgabe_1}, Schulaufgabe 2: {self.Schulaufgabe_2} | Kurzarbeit: {self.Kurzarbeit}")
        print(f"Gesamtnote: {self.berechne_gesamtnote()} | Zeugnisnote: {self.Zeugnisnote}")

    # Methode, um die gespeicherte Zeugnisnote zu erhalten
    def get_zeugnisnote(self):
        return self.Zeugnisnote

# Funktion zur Berechnung des Gesamtdurchschnitts
def berechne_gesamtdurchschnitt(faecher):
    summe_zeugnisnoten = sum(fach.get_zeugnisnote() for fach in faecher)
    return summe_zeugnisnoten / len(faecher)

def main():
    # Liste der Fächer
    faecher = [
        Schulfach("IT"), Schulfach("ET"), Schulfach("EL-A"), Schulfach("EL-D"),
    Schulfach("MT"), Schulfach("M1"), Schulfach("D"), Schulfach("E"),
    Schulfach("PuG"), Schulfach("CW")
    ]

    # Debugging-Ausgabe
    print(f"Fächerliste: {[fach.name for fach in faecher]}")  # Ausgabe der Fächer-Namen

    # Schleife über die Fächer
    for fach in faecher:
        print(f"Verarbeite Fach: {fach.name}")  # Debugging-Ausgabe
        fach.setze_noten()
        fach.ausgabe_noten()

    # Berechnung des Gesamtdurchschnitts
    gesamtdurchschnitt = berechne_gesamtdurchschnitt(faecher)
    print("\n--------------------------------------------")
    print(f"Gesamtdurchschnitt aller Fächer: {gesamtdurchschnitt}")

if __name__ == "__main__":
    main()
