#include <iostream>
#include <string>

class SubstitutionCipherA
{
public:
    static std::string decrypt(const std::string &cipher, int offset)
    {
        
        return nullptr;
    }

    static void bruteForce(const std::string &cipher)
    {
        
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

    return 0;
}
