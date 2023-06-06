#include <iostream>
#include <iomanip>
#include <openssl/md5.h>
#include <sstream>

std::string computeHash(const std::string& message) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)message.c_str(), message.length(), digest);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return ss.str();
}

int main() {
    std::string original_message = "Hello, World!";

    // Compute hash of the original message
    std::string original_hash = computeHash(original_message);
    std::cout << "Original Message: " << original_message << std::endl;
    std::cout << "Original Hash: " << original_hash << std::endl;

    // Simulate the receiver computing the hash again and ensuring its integrity
    std::string received_message = original_message;
    std::string received_hash = computeHash(received_message);
    std::cout << "Received Message: " << received_message << std::endl;
    std::cout << "Received Hash: " << received_hash << std::endl;
    std::cout << "Integrity Check: " << (original_hash == received_hash ? "True" : "False") << std::endl;

    // Change the message slightly
    std::string changed_message = "Hello, World!!";
    std::string changed_hash = computeHash(changed_message);
    std::cout << "Changed Message: " << changed_message << std::endl;
    std::cout << "Changed Hash: " << changed_hash << std::endl;
    std::cout << "Integrity Check: " << (original_hash == changed_hash ? "True" : "False") << std::endl;

    return 0;
}
