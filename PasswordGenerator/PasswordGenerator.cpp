#include <Windows.h>
#include <iostream>
#include <random>

class PasswordGenerator
{
public:
    std::string GeneratePassword(SIZE_T length, bool bUseUppercase, bool bUseSymbols, bool bUseNumbers)
    {
        std::string characterSet = lowercase;
        if (bUseUppercase) characterSet += uppercase;
        if (bUseSymbols) characterSet += symbols;
        if (bUseNumbers) characterSet += numbers;

        std::string resultPassword;
        resultPassword.reserve(length);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, characterSet.length() - 1);

        for (int i = 0; i < length; i++)
        {
            resultPassword += characterSet[dis(gen)];
        }

        return resultPassword;
    }

    std::vector<std::string> GenerateMultiplePasswords(SIZE_T amount, SIZE_T length, bool bUseUppercase, bool bUseSymbols, bool bUseNumbers)
    {
        std::vector<std::string> passwords;
        passwords.reserve(amount);

        for (int i = 0; i < amount; i++)
        {
            passwords.push_back(GeneratePassword(length, bUseUppercase, bUseSymbols, bUseNumbers));
        }

        return passwords;
    }

private:
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string symbols = "!@#$%^&*(){}:;<>/?,.";
    const std::string numbers = "0123456789";
};

int main()
{
    const auto passwordGenerator = std::make_unique<PasswordGenerator>();

    while (true)
    {
        int bGenerateMultiple = 0;
        SIZE_T length = 0, amount = 0;
        bool bUseUppercase = false, bUseSymbols = false, bUseNumbers = false;

        std::cout << "Generate multiple passwords? (1 for yes, 0 for no): ";
        std::cin >> bGenerateMultiple;

        std::cout << "Enter desired password length: ";
        std::cin >> length;

        std::cout << "Use numbers? (1 for yes, 0 for no): ";
        std::cin >> bUseNumbers;

        std::cout << "Use symbols? (1 for yes, 0 for no): ";
        std::cin >> bUseSymbols;

        std::cout << "Use uppercase letters? (1 for yes, 0 for no): ";
        std::cin >> bUseUppercase;

        if (bGenerateMultiple == 0)
        {
            std::cout << "Generated password: "
                << passwordGenerator->GeneratePassword(length, bUseUppercase, bUseSymbols, bUseNumbers)
                << std::endl;
        }
        else if (bGenerateMultiple == 1)
        {
            std::cout << "Enter the number of passwords to generate: ";
            std::cin >> amount;

            std::cout << "Generating passwords with specified criteria:\n";
            std::cout << "\n";
            auto passwords = passwordGenerator->GenerateMultiplePasswords(amount, length, bUseUppercase, bUseSymbols, bUseNumbers);

            for (const auto& password : passwords)
            {
                std::cout << "Password: " << password << "\n\n";
            }
        }
    }
}