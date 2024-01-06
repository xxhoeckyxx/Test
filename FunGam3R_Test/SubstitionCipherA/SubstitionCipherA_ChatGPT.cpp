#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class SubstitutionCipherA
{
private:
    // Häufige deutsche Wörter, die als Kriterium für die Sinnhaftigkeit verwendet werden können
    static const unordered_set<string> commonGermanWords;

public:
    // Funktion zum Entschlüsseln der Chiffre mit einem gegebenen Versatz
    static string decrypt(const string &cipher, int offset)
    {
        string decryptedText;
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
    static int calculateScore(const string &text)
    {
        // Hier können weitere Kriterien hinzugefügt werden, um die Sinnhaftigkeit zu bewerten
        int score = 0;
        for (const string &word : commonGermanWords)
        {
            if (text.find(word) != string::npos)
            {
                score++;
            }
        }
        return score;
    }

    // Funktion zum Zusammenstellen der besten Vermutungen basierend auf den höchsten Punktzahlen
    static string getBestGuess(const vector<pair<int, string>> &results, int count, const vector<pair<int, string>> &offset_map)
    {
        string bestGuess;
        for (int i = 0; i < count && i < results.size(); ++i)
        {
            bestGuess += "Offset " + to_string(offset_map[i].first) + ": " + results[i].second + "\n";
        }
        return bestGuess;
    }

    bool comparePairs(const pair<int, string> &a, const pair<int, string> &b, const vector<pair<int, string>> &results)
    {
        const auto &aResult = find(results.begin(), results.end(), a);
        const auto &bResult = find(results.begin(), results.end(), b);

        return aResult > bResult;
    }

    // Funktion für die Brute-Force-Entschlüsselung der Chiffre
    static void bruteForce(const string &cipher, int bestGuessCount)
    {
        vector<pair<int, string>> results;
        vector<pair<int, string>> offset_map;

        // Durchlaufe alle möglichen Versatzwerte
        for (int offset = 0; offset < 26; ++offset)
        {
            // Entschlüssle die Chiffre mit dem aktuellen Versatz
            string decryptedText = decrypt(cipher, offset);
            // Bewertung der Sinnhaftigkeit des entschlüsselten Textes
            int score = calculateScore(decryptedText);
            // Speichere Ergebnisse (Punktzahl und entschlüsselter Text)
            results.push_back(make_pair(score, decryptedText));
            offset_map.push_back(make_pair(offset, decryptedText));
        }

        // Sortiere die Ergebnisse nach absteigender Punktzahl
        sort(results.rbegin(), results.rend());

        // Sortiere die offset_map basierend auf der Sortierung von results
        sort(offset_map.begin(), offset_map.end(), [results](const pair<int, string> &a, const pair<int, string> &b)
             { return a > b; });

        // Gib die Ergebnisse auf der Konsole aus
        cout << "Brute Force Decryption Results:" << endl;
        for (const auto &result : results)
        {
            cout << "Score " << result.first << ": " << result.second << endl;
        }

        // Holen Sie sich die besten Vermutungen basierend auf den höchsten Punktzahlen und dem Versatz
        string bestGuesses = getBestGuess(results, bestGuessCount, offset_map);
        cout << "\nTop " << bestGuessCount << " Guesses:" << endl;
        cout << bestGuesses;
    }
};

// Definiere häufige deutsche Wörter (zusätzlich anpassbar)
const unordered_set<string> SubstitutionCipherA::commonGermanWords = {
    "der", "die", "das", "doch", "und", "in", "den", "von", "zu", "mit", "sich", "auf", "für", "ist", "im", "dem", "nicht", "ein", "eine", "als", "auch", "es", "an", "werden", "aus", "er", "hat", "am", "wer", "hat", "werden", "noch", "nicht", "bei", "uns"};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: ./SubstitutionCipherA <cipher>" << endl;
        return 1;
    }

    string cipher(argv[1]);
    int bestGuessCount = 3; // Anzahl der besten Vermutungen, anpassbar
    SubstitutionCipherA::bruteForce(cipher, bestGuessCount);
    cout << "\n";

    return 0;
}
