#include <iostream>

// Function to calculate the Greatest Common Divisor (GCD) of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to encrypt the message using the Affine cipher
std::string affineEncrypt(const std::string& plainText, int a, int b) {
    std::string encryptedText = "";
    for (char ch : plainText) {
        if (std::isalpha(ch)) {
            char encryptedChar = (a * (ch - 'A') + b) % 26 + 'A';
            encryptedText += encryptedChar;
        } else {
            encryptedText += ch;
        }
    }
    return encryptedText;
}

// Function to decrypt the message using the Affine cipher
std::string affineDecrypt(const std::string& cipherText, int a, int b) {
    std::string decryptedText = "";
    int aInverse = modInverse(a, 26);
    if (aInverse == -1) {
        return "Error: 'a' is not coprime with 26.";
    }
    for (char ch : cipherText) {
        if (std::isalpha(ch)) {
            char decryptedChar = (aInverse * (ch - 'A' - b + 26)) % 26 + 'A';
            decryptedText += decryptedChar;
        } else {
            decryptedText += ch;
        }
    }
    return decryptedText;
}

int main() {
    std::string plainText = "HELLO WORLD";
    int a = 5;
    int b = 8;

    std::string cipherText = affineEncrypt(plainText, a, b);
    std::cout << "Cipher Text: " << cipherText << std::endl;

    std::string decryptedText = affineDecrypt(cipherText, a, b);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}
