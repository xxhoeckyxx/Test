import java.util.*;

public class SubstitutionCipherA_ChatGPT {
    // Häufige deutsche Wörter, die als Kriterium für die Sinnhaftigkeit verwendet werden können
    private static final Set<String> commonGermanWords = new HashSet<>(Arrays.asList(
            "der", "die", "das", "doch", "und", "in", "den", "von", "zu", "mit", "sich", "auf", "für", "ist", "im", "dem",
            "nicht", "ein", "eine", "als", "auch", "es", "an", "werden", "aus", "er", "hat", "am", "wer", "hat", "werden",
            "noch", "nicht", "bei", "uns"
    ));

    // Funktion zum Entschlüsseln der Chiffre mit einem gegebenen Versatz
    public static String decrypt(String cipher, int offset) {
        StringBuilder decryptedText = new StringBuilder();
        for (char c : cipher.toCharArray()) {
            // Wenn es sich um einen Buchstaben handelt, verschiebe ihn entsprechend
            if (Character.isAlphabetic(c)) {
                char base = Character.isLowerCase(c) ? 'a' : 'A'; // Basis des Alphabets (klein oder groß)
                char decryptedChar = (char) (((c - base - offset + 26) % 26) + base); // Entschlüsselung
                decryptedText.append(decryptedChar);
            } else {
                // Behalte nicht-alphabetische Zeichen unverändert bei
                decryptedText.append(c);
            }
        }
        return decryptedText.toString();
    }

    // Funktion zur Bewertung der Sinnhaftigkeit eines Textes anhand bestimmter Kriterien
    public static int calculateScore(String text) {
        // Hier können weitere Kriterien hinzugefügt werden, um die Sinnhaftigkeit zu bewerten
        int score = 0;
        for (String word : commonGermanWords) {
            if (text.contains(word)) {
                score++;
            }
        }
        return score;
    }

    // Funktion zum Zusammenstellen der besten Vermutungen basierend auf den höchsten Punktzahlen
    public static String getBestGuess(List<Map.Entry<Integer, String>> results, int count,
                                      List<Map.Entry<Integer, String>> offsetMap) {
        StringBuilder bestGuess = new StringBuilder();
        for (int i = 0; i < count && i < results.size(); ++i) {
            bestGuess.append("Offset ").append(offsetMap.get(i).getKey()).append(": ")
                    .append(results.get(i).getValue()).append("\n");
        }
        return bestGuess.toString();
    }

    // Funktion für die Brute-Force-Entschlüsselung der Chiffre
    public static void bruteForce(String cipher, int bestGuessCount) {
        List<Map.Entry<Integer, String>> results = new ArrayList<>();
        List<Map.Entry<Integer, String>> offsetMap = new ArrayList<>();

        // Durchlaufe alle möglichen Versatzwerte
        for (int offset = 0; offset < 26; ++offset) {
            // Entschlüssle die Chiffre mit dem aktuellen Versatz
            String decryptedText = decrypt(cipher, offset);
            // Bewertung der Sinnhaftigkeit des entschlüsselten Textes
            int score = calculateScore(decryptedText);
            // Speichere Ergebnisse (Punktzahl und entschlüsselter Text)
            results.add(new AbstractMap.SimpleEntry<>(score, decryptedText));
            offsetMap.add(new AbstractMap.SimpleEntry<>(offset, decryptedText));
        }

        // Sortiere die Ergebnisse nach absteigender Punktzahl
        results.sort((a, b) -> b.getKey().compareTo(a.getKey()));

        // Sortiere die offsetMap basierend auf der Sortierung von results
        offsetMap.sort((a, b) -> b.getKey().compareTo(a.getKey()));

        // Gib die Ergebnisse auf der Konsole aus
        System.out.println("Brute Force Decryption Results:");
        for (Map.Entry<Integer, String> result : results) {
            System.out.println("Score " + result.getKey() + ": " + result.getValue());
        }

        // Holen Sie sich die besten Vermutungen basierend auf den höchsten Punktzahlen und dem Versatz
        String bestGuesses = getBestGuess(results, bestGuessCount, offsetMap);
        System.out.println("\nTop " + bestGuessCount + " Guesses:");
        System.out.println(bestGuesses);
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java SubstitutionCipherA <cipher>");
            System.exit(1);
        }

        String cipher = args[0];
        int bestGuessCount = 3; // Anzahl der besten Vermutungen, anpassbar
        bruteForce(cipher, bestGuessCount);
    }
}
