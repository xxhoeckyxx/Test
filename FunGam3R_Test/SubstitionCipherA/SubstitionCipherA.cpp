#include <iostream>
#include <string>

class SubstitutionCipherA
{
public:
    static std::string decrypt(const std::string &cipher, int offset)
    {
        // Methode zum Entschlüsseln von Sätzen mit vorgegebenem Offset (Chiffrat)

        std::string decryptedString;
        for (size_t i = 0; i < cipher.length(); i++)
        { // Abarbeiten des eingegebenen Satzes Stück für Stück
            char decryptChar;
            int lower_offset = 26 + (-2 * offset) % 26;
            int upper_offset = 26 + (3 * offset) % 26;
            if (isalpha(cipher[i]))
            { // Abfragen, ob der Platzhalter ein Buchstabe ist

                if (islower(cipher[i]))
                {
                    decryptChar = static_cast<char>((cipher[i] - 'a' + lower_offset) % 26 + 'a');
                }
                else
                {
                    decryptChar = static_cast<char>((cipher[i] - 'A' + upper_offset) % 26 + 'A');
                }

                // std::cout << "Stelle: "<< static_cast<int>(cipher[i]) << "; Verschluesselt: " << cipher[i] << "            ";
                // std::cout << "Entschluesselt: " << decryptChar << "; Stelle: " << static_cast<int>(decryptChar) << std::endl;

                decryptedString += decryptChar;
            }
            else
            {
                decryptedString += cipher[i];
            }
        }
        return decryptedString; // Rückgabe des entschlüsselten Textes an die Methode
    }

    static void bruteForce(const std::string &cipher)
    {
        for (int i = 0; i <= 26; i++)
        {
            std::string decrypted = decrypt(cipher, i);
            std::cout << decrypted << std::endl;
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./SubstitutionCipherA <cipher>" << std::endl;
        return 1;
    }

    std::string cipher(argv[1]);
    SubstitutionCipherA::bruteForce(cipher);

    // std::string cipher = "abcd";
    // std::string cipher = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    // std::string cipher = "Mgp kscqqcl ysq bcl Vcfjcpl ylbcpcp jcplcl; bcll ugp jczcl lgafr jylec eclse, sk yjjc Vcfjcp qcjzcp xs kyafcl.(Ujcylmp Hmmqctcjr)";
    // std::string cipher = "Lqxhu Lehju iydt dysxj yccuh isxeud.Hsxeudu Lehju iydt dysxj yccuh mqxh.(Aqepy)";
    // SubstitutionCipherA::bruteForce(cipher);
    // SubstitutionCipherA::decrypt(cipher, -14);

    return 0;
}
