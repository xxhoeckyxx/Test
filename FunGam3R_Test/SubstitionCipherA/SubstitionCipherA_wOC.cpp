#include <iostream>
#include <string>

class SubstitutionCipherA {
public:
    static std::string decrypt(const std::string &cipher, int offset) {
        std::string decryptedString;
        for (size_t i = 0; i < cipher.length(); i++) {
            char decryptChar;
            int lower_offset = 26 + (-2 * offset) % 26;
            int upper_offset = 26 + (3 * offset) % 26;
            if (isalpha(cipher[i])) {
                decryptChar = (islower(cipher[i])) ? static_cast<char>((cipher[i] - 'a' + lower_offset) % 26 + 'a') : static_cast<char>((cipher[i] - 'A' + upper_offset) % 26 + 'A');
                decryptedString += decryptChar;
            } else {
                decryptedString += cipher[i];
            }
        }
        return decryptedString;
    }

    static void bruteForce(const std::string &cipher) {
        for (int i = 0; i <= 26; i++) {
            std::cout << decrypt(cipher, i) << std::endl;
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./SubstitutionCipherA <cipher>" << std::endl;
        return 1;
    }

    std::string cipher(argv[1]);
    SubstitutionCipherA::bruteForce(cipher);

    return 0;
}
