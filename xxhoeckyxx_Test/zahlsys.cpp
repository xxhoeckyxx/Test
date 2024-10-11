#include <iostream>
#include <cstdlib>
#include <cctype>

// Funktion zur Anzeige der Programmnutzung
bool showUsage(const char *programName)
{
    std::cout << "usage: " << programName << " [--boh] zahl\n";
    return false;
}

// Funktion zum Analysieren von Zeichenoptionen
bool parseCharacter(const char *option, bool &binary, bool &octal, bool &hex)
{
    for (int j = 2; option[j] != '\0'; j++)
    {
        switch (option[j])
        {
        case 'b':
            binary = true;
            break;
        case 'o':
            octal = true;
            break;
        case 'h':
            hex = true;
            break;
        default:
            std::cerr << "....... Unerlaubte Option " << option << "\n\n";
            return false;
        }
    }

    return true;
}

// Funktion zum Analysieren von Dezimalzahlen
bool parseNumber(const char *option, int &decimal)
{
    int decimalSet = 0;
    while (decimalSet == 0)
    {
        if (option[0] == '-' && isdigit(option[1]))
        {
            if (sscanf(option, "%d", &decimal) != 1)
            {
                std::cerr << "Fehler: Ungültiger Dezimalwert '" << option << "'\n";
                return false;
            }
            else
            {
                decimalSet = 1;
            }
        }
        else if (isdigit(option[0]))
        {
            if (sscanf(option, "%d", &decimal) != 1)
            {
                std::cerr << "Fehler: Ungültiger Dezimalwert '" << option << "'\n";
                return false;
            }
            else
            {
                decimalSet = 1;
            }
        }
        else
        {
            std::cerr << "Fehler: Unerwartetes '-' im Dezimalwert '" << option << "'\n";
            return false;
        }
    }

    return true;
}

// Hauptfunktion zum Analysieren der Befehlszeilenoptionen
bool parseOptions(int argc, char *argv[], bool &binary, bool &octal, bool &hex, int &decimal)
{
    int numberCount = 0;
    int detectFail = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == '-')
        {
            // Verarbeitung von Optionen, die mit '--' beginnen
            if (!parseCharacter(argv[i], binary, octal, hex))
            {
                showUsage(argv[0]);
                detectFail++;
            }
        }
        else if (numberCount != 0)
        {
            std::cerr << "....... Es muss genau eine Zahl angegeben sein\n";
            detectFail++;
        }
        else
        {
            // Verarbeitung der Dezimalzahl, die nicht mit '-' beginnt
            if (!parseNumber(argv[i], decimal))
            {
                showUsage(argv[0]);
                detectFail++;
            }
            numberCount++;
        }
    }

    if (detectFail > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Funktion zur Anzeige der Ergebnisse je nach gewählter Basis
void printResults(bool binary, bool octal, bool hex, int decimal)
{
    std::cout << "           Dezimal: " << decimal << "\n\n";

    if (binary)
    {
        // Konvertierung und Anzeige der Binärzahl
        int bin_list[32] = {0};
        for (int i = 31; i >= 0; i--)
        {
            bin_list[31 - i] = (decimal >> i) & 1;
        }
        std::cout << "              Dual: ";
        for (int i = 0; i < 32; i++)
        {
            if (i % 8 == 0 && i > 0)
            {
                std::cout << " ";
            }
            std::cout << bin_list[i];
        }
        std::cout << "\n";
    }
    if (octal)
    {
        // Anzeige der Oktalzahl
        std::cout << "\n             Octal: " << std::oct << decimal << "\n";
    }
    if (hex)
    {
        // Anzeige der Hexadezimalzahl
        std::cout << "       Hexadezimal: " << std::hex << decimal << "\n";
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // Anzeige der Programmnutzung, wenn nicht genügend Argumente vorhanden sind
        return showUsage(argv[0]);
    }

    // Initialisierung von Flags und Dezimalzahl
    bool binary = false;
    bool octal = false;
    bool hex = false;
    int decimal = 0;

    // Debugging für argc und argv
    // std::cout << "Argument Count: " << argc << "\n";
    // for (int i = 0; i < argc; i++)
    // {
    //     std::cout << "Argument " << i << ": " << argv[i] << "\n";
    //     std::cout << "SizeOf Argument " << i << ": " << sizeof(argv[i]) << "\n";
    //     for (size_t j = 0; j < sizeof(argv[i]); j++)
    //     {
    //         std::cout << "Character " << j << ": " << argv[i][j] << "\n";
    //         std::cout << "SizeOf Character " << j << ": " << sizeof(argv[i][j]) << "\n";
    //     }
    // }

    // Analyse der Befehlszeilenoptionen
    if (!parseOptions(argc, argv, binary, octal, hex, decimal))
    {
        return 1; // Beende das Programm mit Fehlercode 1 bei einem Analysefehler
    }

    // Falls keine Basisoptionen angegeben sind, verwenden Sie alle drei
    if (!binary && !octal && !hex)
    {
        binary = octal = hex = true;
    }

    // std::cout << "Dual: " << binary << "\nOctal: " << octal << "\nHex: " << hex << "\n";

    // Anzeige der Ergebnisse
    printResults(binary, octal, hex, decimal);

    return 0; // Beende das Programm ohne Fehler
}
