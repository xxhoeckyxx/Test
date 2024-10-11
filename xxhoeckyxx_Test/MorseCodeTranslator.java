import java.util.Scanner;

public class MorseCodeTranslator {

    public static int getTranslationCount(String contextInput, int charCount, boolean isDecode, Dictionary morseCode) {
        int alphabeticCount = 0;
        for (int i = 0; i < 45; i++) {
            if (isDecode && contextInput.charAt(charCount) == morseCode.callbackDecoded(i).charAt(0)) {
                alphabeticCount = i;
                break;
            } else if (contextInput.charAt(charCount) == morseCode.callbackEncrypted(i).charAt(0)) {
                alphabeticCount = i;
                break;
            }
        }
        return alphabeticCount;
    }

    public static boolean directionalDecision(String contextInput) {
        // TODO: Implementieren der Entscheidungsfunktion 
        return false;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a number: ");
        int count = Integer.parseInt(scanner.nextLine());
        int count = 0; // Standardverhalten gesetzt, damit das Programm ausführbar ist
        int position = 0;
        boolean direction = true;

        Dictionary morseCode = new Dictionary();

        System.out.print("Enter Morse code: ");
        String input = scanner.nextLine(); 
        position = input.length();
        input = input.toUpperCase();
        for(int i = 0; i < position; i++)
        {
            count = getTranslationCount(input, position, direction, morseCode);
            System.out.println("Decoded: " + morseCode.callbackDecoded(count));
            System.out.println("Encrypted: " + morseCode.callbackEncrypted(count));
        }
        // TODO: Hier muss man weiter machen ... ich les zwar den String ein allerdings wird er noch nicht decodiert ..

    }
}
