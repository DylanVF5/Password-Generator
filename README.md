# Password Generator
A C++ tool for generating secure passwords with customizable criteria.

## Features

- Custom password length
- Option to include uppercase letters, numbers, and symbols
- Single or multiple password generation
- Password strength evaluation

## Usage

```cpp
auto passwordGenerator = std::make_unique<PasswordGenerator>();

// Generate a single password
std::string password = passwordGenerator->GeneratePassword(12, true, true, true);

// Generate multiple passwords
std::vector<std::string> passwords = passwordGenerator->GenerateMultiplePasswords(5, 12, true, true, true);

// Check password strength
bool isStrong = passwordGenerator->IsPasswordStrong(password);
```

## Purpose

Designed to create strong, customizable passwords for enhanced digital security. Suitable for integration into security-focused applications or as a standalone utility for generating secure passwords.

## Note

This tool is for educational and personal use. Ensure you're following best practices for password management and storage when using generated passwords.
