#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

class SubstitutionCipherA
{
private:
    // Häufige deutsche Wörter, die als Kriterium für die Sinnhaftigkeit verwendet werden können
    static const std::unordered_set<std::string> commonGermanWords;

public:
    // Funktion zum Entschlüsseln der Chiffre mit einem gegebenen Versatz
    static std::string decrypt(const std::string &cipher, int offset)
    {
        std::string decryptedText;
        for (char c : cipher)
        {
            // Wenn es sich um einen Buchstaben handelt, verschiebe ihn entsprechend
            if (isalpha(c))
            {
                char base = islower(c) ? 'a' : 'A';                          // Basis des Alphabets (klein oder groß)
                char decryptedChar = ((c - base - offset + 26) % 26) + base; // Entschlüsselung
                decryptedText.push_back(decryptedChar);
            }
            else
            {
                // Behalte nicht-alphabetische Zeichen unverändert bei
                decryptedText.push_back(c);
            }
        }
        return decryptedText;
    }

    // Funktion zur Bewertung der Sinnhaftigkeit eines Textes anhand bestimmter Kriterien
    static int calculateScore(const std::string &text)
    {
        // Hier können weitere Kriterien hinzugefügt werden, um die Sinnhaftigkeit zu bewerten
        int score = 0;
        for (const std::string &word : commonGermanWords)
        {
            if (text.find(word) != std::string::npos)
            {
                score++;
            }
        }
        return score;
    }

    // Funktion zum Zusammenstellen der besten Vermutungen basierend auf den höchsten Punktzahlen
    static std::string getBestGuess(const std::vector<std::pair<int, std::string>> &results, int count)
    {
        std::string bestGuess;
        for (int i = 0; i < count && i < results.size(); ++i)
        {
            bestGuess += results[i].second + "\n";
        }
        return bestGuess;
    }

    // Funktion für die Brute-Force-Entschlüsselung der Chiffre
    static void bruteForce(const std::string &cipher, int bestGuessCount)
    {
        std::vector<std::pair<int, std::string>> results;

        // Durchlaufe alle möglichen Versatzwerte
        for (int offset = 0; offset < 26; ++offset)
        {
            // Entschlüssle die Chiffre mit dem aktuellen Versatz
            std::string decryptedText = decrypt(cipher, offset);
            // Bewertung der Sinnhaftigkeit des entschlüsselten Textes
            int score = calculateScore(decryptedText);
            // Speichere Ergebnisse (Punktzahl und entschlüsselter Text)
            results.push_back(std::make_pair(score, decryptedText));
        }

        // Sortiere die Ergebnisse nach absteigender Punktzahl
        std::sort(results.rbegin(), results.rend());

        // Gib die Ergebnisse auf der Konsole aus
        std::cout << "Brute Force Decryption Results:" << std::endl;
        for (const auto &result : results)
        {
            std::cout << "Score " << result.first << ": " << result.second << std::endl;
        }

        // Holen Sie sich die besten Vermutungen basierend auf den höchsten Punktzahlen
        std::string bestGuesses = getBestGuess(results, bestGuessCount);
        std::cout << "\nTop " << bestGuessCount << " Guesses:" << std::endl;
        std::cout << bestGuesses;
    }
};

// Definiere häufige deutsche Wörter (zusätzlich anpassbar)
const std::unordered_set<std::string> SubstitutionCipherA::commonGermanWords = {
    "der", "die", "das", "und", "in", "den", "von", "zu", "mit", "sich", "auf", "für", "ist", "im", "dem", "nicht", "ein", "eine", "als", "auch", "es", "an", "werden", "aus", "er", "hat", "das", "am", "wer", "hat", "werden", "noch", "nicht", "bei", "uns"};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./SubstitutionCipherA <cipher>" << std::endl;
        return 1;
    }

    std::string cipher(argv[1]);
    int bestGuessCount = 3; // Anzahl der besten Vermutungen, anpassbar
    SubstitutionCipherA::bruteForce(cipher, bestGuessCount);
    std::cout << "\n";

    return 0;
}
