#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

struct MorseEntry
{
    const char *character;
    const char *code;
};

struct MorseDictionary
{
    MorseEntry entries[47];
};

void initializeDictionary(MorseDictionary *morseCode)
{
    const char *characters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
                                "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Ä", "Ö", "Ü", "0", "1",
                                "2", "3", "4", "5", "6", "7", "8", "9", ".", ",", ":", "-", "?", "\0"};
    const char *codes[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-",
                           ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-",
                           ".--", "-..-", "-.--", "--..", ".-.-", "---.", "..--", "-----", ".----",
                           "..---", "...--", "...._", ".....", "-....", "--...", "---..", "----.",
                           ".-.-.-", "--..--", "---...", "-...-", "..--..", "...-.-", ""};

    for (int i = 0; i < 46; i++) // Ändern Sie die Anzahl der Elemente auf 46
    {
        morseCode->entries[i].character = characters[i];
        morseCode->entries[i].code = codes[i];
    }
}

const char *getMorseCode(const MorseDictionary *morseCode, char character)
{
    for (int i = 0; morseCode->entries[i].character != nullptr; i++)
    {
        if (morseCode->entries[i].character[0] == character)
        {
            return morseCode->entries[i].code;
        }
    }
    return nullptr;
}

const char *getCharacter(const MorseDictionary *morseCode, const char *code)
{
    for (int i = 0; morseCode->entries[i].code != nullptr; i++)
    {
        if (strcmp(morseCode->entries[i].code, code) == 0)
        {
            return morseCode->entries[i].character;
        }
    }
    return nullptr;
}

char *translateTo(const MorseDictionary *morseCode, const char *input, int direction)
{
    size_t inputLength = strlen(input);
    char *output = (char *)malloc((inputLength * 5) + 1);

    if (!output)
    {
        exit(EXIT_FAILURE);
    }

    int outputIndex = 0;

    for (size_t i = 0; i < inputLength; i++)
    {
        char currentChar = input[i];

        if (direction == 1)
        {
            if (currentChar == ' ')
            {
                output[outputIndex++] = ' ';
            }
            else
            {
                const char *code = getMorseCode(morseCode, toupper(currentChar));
                if (code)
                {
                    strcpy(&output[outputIndex], code);
                    outputIndex += strlen(code);
                    output[outputIndex++] = ' ';
                }
            }
        }
        else if (direction == 0)
        {
            if (currentChar == ' ' || currentChar == '\0')
            {
                output[outputIndex++] = '\0';
            }
            else
            {
                const char *code = getMorseCode(morseCode, currentChar);
                if (code)
                {
                    const char *character = getCharacter(morseCode, code);
                    if (character)
                    {
                        output[outputIndex++] = *character;
                    }
                }
            }
        }
    }

    output[outputIndex++] = '\0';
    return output;
}

int determineDirection(const MorseDictionary *morseCode, const char *input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ' && input[i] != '.' && input[i] != '-')
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    MorseDictionary morseCode;
    initializeDictionary(&morseCode);

    std::cout << "Enter text: ";
    char input[1000];
    std::cin.getline(input, sizeof(input) / sizeof(input[0]));

    int direction = determineDirection(&morseCode, input);
    char *output = translateTo(&morseCode, input, 1);

    if (output != nullptr)
    {
        std::cout << "Transformed Text: " << output << std::endl;
        free(output);
    }
    else
    {
        std::cout << "Invalid direction." << std::endl;
    }

    return 0;
}
