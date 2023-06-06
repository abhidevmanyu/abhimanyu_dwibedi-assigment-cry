#include <iostream>
#include <cmath>

// Function to calculate the modular exponentiation (base^exp % modulus)
int modExp(int base, int exp, int modulus) {
    if (exp == 0)
        return 1;

    long long result = 1;
    long long currBase = base % modulus;

    while (exp > 0) {
        if (exp & 1)
            result = (result * currBase) % modulus;

        currBase = (currBase * currBase) % modulus;
        exp >>= 1;
    }

    return result;
}

// Function to generate a symmetric key using Diffie-Hellman
int generateSymmetricKey(int g, int p, int x, int y) {
    // Calculate public keys for Party A and Party B
    int public_key_a = modExp(g, x, p);
    int public_key_b = modExp(g, y, p);

    // Calculate the shared secret key for Party A and Party B
    int shared_secret_a = modExp(public_key_b, x, p);
    int shared_secret_b = modExp(public_key_a, y, p);

    // Verify that both shared secret keys are the same
    if (shared_secret_a != shared_secret_b) {
        std::cerr << "Error: Shared secret keys do not match." << std::endl;
        exit(1);
    }

    // Return the symmetric key (shared secret)
    return shared_secret_a;
}

int main() {
    // Parameters
    int g = 2;  // Generator
    int p = 23; // Prime number
    int x = 6;  // Private key for Party A
    int y = 15; // Private key for Party B

    // Generate symmetric key
    int symmetric_key = generateSymmetricKey(g, p, x, y);
    std::cout << "Symmetric Key: " << symmetric_key << std::endl;

    return 0;
}

