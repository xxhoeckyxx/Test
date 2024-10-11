#include <iostream>
#include <fstream>
#include <string>

bool checkCommandLineArguments(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return false;
    }
    return true;
}

void displayFileContents(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 1;
    while (std::getline(file, line))
    {
        std::cout << lineNumber << ": " << line << std::endl;
        lineNumber++;
    }

    file.close();
}

int main(int argc, char *argv[])
{
    if (!checkCommandLineArguments(argc, argv))
    {
        return 1;
    }

    const std::string filename = argv[1];
    displayFileContents(filename);

    return 0;
}
