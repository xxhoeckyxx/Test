class SubstitutionCipherA:
    # Häufige deutsche Wörter, die als Kriterium für die Sinnhaftigkeit verwendet werden können
    common_german_words = {"der", "die", "das", "doch", "und", "in", "den", "von", "zu", "mit", "sich", "auf", "für",
                           "ist", "im", "dem", "nicht", "ein", "eine", "als", "auch", "es", "an", "werden", "aus", "er",
                           "hat", "am", "wer", "hat", "werden", "noch", "nicht", "bei", "uns"}

    @staticmethod
    def decrypt(cipher, offset):
        decrypted_text = ""
        for c in cipher:
            # Wenn es sich um einen Buchstaben handelt, verschiebe ihn entsprechend
            if c.isalpha():
                base = 'a' if c.islower() else 'A'  # Basis des Alphabets (klein oder groß)
                decrypted_char = chr(((ord(c) - ord(base) - offset + 26) % 26) + ord(base))  # Entschlüsselung
                decrypted_text += decrypted_char
            else:
                # Behalte nicht-alphabetische Zeichen unverändert bei
                decrypted_text += c
        return decrypted_text

    @staticmethod
    def calculate_score(text):
        # Hier können weitere Kriterien hinzugefügt werden, um die Sinnhaftigkeit zu bewerten
        score = sum(1 for word in SubstitutionCipherA.common_german_words if word in text)
        return score

    @staticmethod
    def get_best_guess(results, count, offset_map):
        best_guesses = []
        for i in range(min(count, len(results))):
            best_guesses.append((results[i][0], offset_map[i][0], results[i][1]))
        return best_guesses

    @staticmethod
    def brute_force(cipher, best_guess_count):
        results = []
        offset_map = []

        # Durchlaufe alle möglichen Versatzwerte
        for offset in range(26):
            # Entschlüssle die Chiffre mit dem aktuellen Versatz
            decrypted_text = SubstitutionCipherA.decrypt(cipher, offset)
            # Bewertung der Sinnhaftigkeit des entschlüsselten Textes
            score = SubstitutionCipherA.calculate_score(decrypted_text)
            # Speichere Ergebnisse (Punktzahl, entschlüsselter Text und Versatz)
            results.append((score, decrypted_text, offset))
            offset_map.append((offset, decrypted_text))

        # Sortiere die Ergebnisse nach absteigender Punktzahl
        results.sort(reverse=True)

        # Sortiere die offset_map basierend auf der Sortierung von results
        offset_map.sort(reverse=True, key=lambda x: x[0])

        # Gib die Ergebnisse auf der Konsole aus
        print("Brute Force Decryption Results:")
        for result in results:
            print(f"Offset {result[2]}: {result[1]} Score: {result[0]}")

        # Gib die Ergebnisse zurück
        return results, offset_map

if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        print("Usage: python SubstitutionCipherA.py <cipher>")
        sys.exit(1)

    cipher = sys.argv[1]
    best_guess_count = 3  # Anzahl der besten Vermutungen, anpassbar
    results, offset_map = SubstitutionCipherA.brute_force(cipher, best_guess_count)

    # Holen Sie sich die besten Vermutungen basierend auf den höchsten Punktzahlen und dem Versatz
    best_guesses = SubstitutionCipherA.get_best_guess(results, best_guess_count, offset_map)
    print("\nTop", best_guess_count, "Guesses:")
    for guess in best_guesses:
        print(f"Score: {guess[0]}, Offset {guess[1]}: {guess[2]}")
