#include <string>
#include <random>

std::string generateRandomString(size_t length) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyz"; // Character set
    std::string result;
    result.reserve(length); // Reserve space for efficiency

    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 generator(rd()); // Seed the generator
    std::uniform_int_distribution<> distribution(0, charset.size() - 1); // Define the range

    for (size_t i = 0; i < length; ++i) {
        result += charset[distribution(generator)]; // Append a random character
    }
    return result;
}
