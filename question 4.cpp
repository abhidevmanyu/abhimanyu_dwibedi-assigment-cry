#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <openssl/md5.h>

// Function to compute the MD5 hash of a given string
std::string computeHash(const std::string& str) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)str.c_str(), str.length(), digest);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return ss.str();
}

// Function to add a salt to a given password
std::string addSalt(const std::string& password, const std::string& salt) {
    return salt + password;
}

int main() {
    // Step 1: Create a password file
    std::ofstream passwordFile("passwords.txt");
    std::vector<std::string> passwords = {"password1", "123456", "qwerty", "letmein", "hello123",
                                          "abc123", "pass1234", "password123", "admin", "welcome"};

    if (!passwordFile) {
        std::cerr << "Error: Failed to create the password file." << std::endl;
        return 1;
    }

    for (const auto& password : passwords) {
        passwordFile << password << std::endl;
    }
    passwordFile.close();

    std::cout << "Password file created successfully." << std::endl;

    // Step 2: Modify the file to store the hash values of passwords
    std::ifstream passwordFileToHash("passwords.txt");
    std::ofstream hashedPasswordFile("hashed_passwords.txt");

    if (!passwordFileToHash || !hashedPasswordFile) {
        std::cerr << "Error: Failed to open the password files." << std::endl;
        return 1;
    }

    std::string salt = "somesalt"; // Optional: Salt value
    std::string password;

    while (std::getline(passwordFileToHash, password)) {
        std::string saltedPassword = addSalt(password, salt);
        std::string hashedPassword = computeHash(saltedPassword);
        hashedPasswordFile << hashedPassword << std::endl;
    }

    passwordFileToHash.close();
    hashedPasswordFile.close();

    std::cout << "Hashed password file created successfully." << std::endl;

    // Step 3: Optional - Create a salt file
    std::ofstream saltFile("salt.txt");

    if (!saltFile) {
        std::cerr << "Error: Failed to create the salt file." << std::endl;
        return 1;
    }

    saltFile << salt << std::endl;
    saltFile.close();

    std::cout << "Salt file created successfully." << std::endl;

    return 0;
}
