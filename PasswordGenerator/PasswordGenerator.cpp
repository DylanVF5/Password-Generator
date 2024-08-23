#include <Windows.h>
#include <iostream>
#include <random>
#include <regex>

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

    bool IsPasswordStrong(const std::string& password)
    {
        if (password.length() < 10) return false;

        std::regex lower_regex("[a-z]");
        std::regex upper_regex("[A-Z]");
        std::regex digit_regex("[0-9]");
        std::regex special_regex("[!@#$%^&*(){}:;<>/?,.\\-_=+]");

        return std::regex_search(password, lower_regex) &&
            std::regex_search(password, upper_regex) &&
            std::regex_search(password, digit_regex) &&
            std::regex_search(password, special_regex);
    }

private:
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string symbols = "!@#$%^&*(){}:;<>/?,.";
    const std::string numbers = "0123456789";
};

int main() {
    const auto passwordGenerator = std::make_unique<PasswordGenerator>();

    while (true) {
        int bGenerateMultiple = 0;
        SIZE_T length = 0, amount = 0;
        bool bUseUppercase = false, bUseSymbols = false, bUseNumbers = false;

        std::cout << "Generate multiple passwords? (1 for yes, 0 for no): ";
        std::cin >> bGenerateMultiple;

        std::cout << "Enter desired password length (minimum 8): ";
        std::cin >> length;

        if (length < 8) {
            std::cout << "Password length should be at least 8 characters. Setting to 8.\n";
            length = 8;
        }

        std::cout << "Use numbers? (1 for yes, 0 for no): ";
        std::cin >> bUseNumbers;

        std::cout << "Use symbols? (1 for yes, 0 for no): ";
        std::cin >> bUseSymbols;

        std::cout << "Use uppercase letters? (1 for yes, 0 for no): ";
        std::cin >> bUseUppercase;

        try {
            if (bGenerateMultiple == 0) {
                auto password = passwordGenerator->GeneratePassword(length, bUseUppercase, bUseSymbols, bUseNumbers);
                std::cout << "Generated password: " << password << std::endl;
                std::cout << "Password strength: " << (passwordGenerator->IsPasswordStrong(password) ? "Strong" : "Weak") << std::endl;
            }
            else if (bGenerateMultiple == 1) {
                std::cout << "Enter the number of passwords to generate: ";
                std::cin >> amount;
                std::cout << "Generating passwords with specified criteria:\n\n";
                auto passwords = passwordGenerator->GenerateMultiplePasswords(amount, length, bUseUppercase, bUseSymbols, bUseNumbers);
                for (const auto& password : passwords) {
                    std::cout << "Password: " << password << "\n";
                    std::cout << "Strength: " << (passwordGenerator->IsPasswordStrong(password) ? "Strong" : "Weak") << "\n\n";
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        char continueChoice;
        std::cout << "Generate more passwords? (y/n): ";
        std::cin >> continueChoice;
        if (tolower(continueChoice) != 'y') break;
    }

    return 0;
}