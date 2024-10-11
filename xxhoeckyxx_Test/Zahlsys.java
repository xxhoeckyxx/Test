import java.util.Scanner;

public class Zahlsys {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Anzeige der Programmnutzung, wenn nicht genügend Argumente vorhanden sind
        if (args.length < 1) {
            showUsage(args[0]);
            System.exit(1);
        }

        // Initialisierung von Flags und Dezimalzahl
        boolean[] flags = new boolean[3];
        int[] decimal = new int[1];

        // Analyse der Befehlszeilenoptionen
        if (!parseOptions(args, flags, decimal, scanner)) {
            System.exit(1); // Beende das Programm mit Fehlercode 1 bei einem Analysefehler
        }

        // Falls keine Basisoptionen angegeben sind, verwenden Sie alle drei
        if (!flags[0] && !flags[1] && !flags[2]) {
            flags[0] = flags[1] = flags[2] = true;
        }

        // System.out.println("Dual: " + flags[0] + "\nOctal: " + flags[1] + "\nHex: " + flags[2]);

        // Anzeige der Ergebnisse
        printResults(flags[0], flags[1], flags[2], decimal[0]);
    }

    // Funktion zum Analysieren von Zeichenoptionen
    static boolean parseCharacter(String option, boolean[] flags) {
        for (int j = 2; j < option.length(); j++) {
            switch (option.charAt(j)) {
                case 'b':
                    flags[0] = true;
                    break;
                case 'o':
                    flags[1] = true;
                    break;
                case 'h':
                    flags[2] = true;
                    break;
                default:
                    System.err.println("....... Unerlaubte Option " + option + "\n\n");
                    return false;
            }
        }
        return true;
    }

    // Funktion zum Analysieren von Dezimalzahlen mit dem Scanner
    static boolean parseNumber(String option, int[] decimal, Scanner scanner) {
        try {
            decimal[0] = Integer.parseInt(option);
            return true;
        } catch (NumberFormatException e) {
            System.err.println("Fehler: Ungültiger Dezimalwert '" + option + "'\n");
            return false;
        }
    }

    // Hauptfunktion zum Analysieren der Befehlszeilenoptionen
    static boolean parseOptions(String[] args, boolean[] flags, int[] decimal, Scanner scanner) {
        int numberCount = 0;
        int detectFail = 0;

        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("--")) {
                // Verarbeitung von Optionen, die mit '--' beginnen
                if (!parseCharacter(args[i], flags)) {
                    showUsage(args[0]);
                    detectFail++;
                }
            } else if (numberCount != 0) {
                System.err.println("....... Es muss genau eine Zahl angegeben sein\n");
                detectFail++;
            } else {
                // Verarbeitung der Dezimalzahl, die nicht mit '-' beginnt
                if (!parseNumber(args[i], decimal, scanner)) {
                    showUsage(args[0]);
                    detectFail++;
                }
                numberCount++;
            }
        }

        return detectFail == 0;
    }

    // Funktion zur Anzeige der Ergebnisse je nach gewählter Basis
    static void printResults(boolean binary, boolean octal, boolean hex, int decimal) {
        System.out.println("           Dezimal: " + decimal + "\n");

        if (binary) {
            // Konvertierung und Anzeige der Binärzahl
            int[] binList = new int[32];
            for (int i = 31; i >= 0; i--) {
                binList[31 - i] = (decimal >> i) & 1;
            }
            System.out.print("              Dual: ");
            for (int i = 0; i < 32; i++) {
                if (i % 8 == 0 && i > 0) {
                    System.out.print(" ");
                }
                System.out.print(binList[i]);
            }
            System.out.println();
        }
        if (octal) {
            // Anzeige der Oktalzahl
            System.out.println("\n             Octal: " + Integer.toOctalString(decimal));
        }
        if (hex) {
            // Anzeige der Hexadezimalzahl
            System.out.println("       Hexadezimal: " + Integer.toHexString(decimal));
        }
    }

    // Funktion zur Anzeige der Programmnutzung
    static boolean showUsage(String programName) {
        System.out.println("usage: " + programName + " [--boh] zahl");
        return false;
    }
}
