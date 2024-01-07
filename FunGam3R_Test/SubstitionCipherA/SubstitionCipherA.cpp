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
            int add = random();
            if (isalpha(cipher[i]))
            { // Abfragen, ob der Platzhalter ein Buchstabe ist

                if (islower(cipher[i]))
                {
                    decryptChar = static_cast<char>((cipher[i] - 'a' + offset) % 26 + 'a');
                }
                else
                {
                    decryptChar = static_cast<char>((cipher[i] - 'A' + offset + add) % 26 + 'A');
                }

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
            // std::cout << "verschlüsselt mit: " << (26 - i) << " bzw. " << (-i) << std::endl;
            // std::cout << "entschlüsselt mit: " << i << std::endl;
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

    // std::string cipher = "Mgp kscqqcl ysq bcl Vcfjcpl ylbcpcp jcplcl; bcll ugp jczcl lgafr jylec eclse, sk yjjc Vcfjcp qcjzcp xs kyafcl.(Ujcylmp Hmmqctcjr)";
    // std::string cipher = "Lqxhu Lehju iydt dysxj yccuh isxeud.Hsxeudu Lehju iydt dysxj yccuh mqxh.(Aqepy)";
    // SubstitutionCipherA::bruteForce("Ll");

    return 0;
}
