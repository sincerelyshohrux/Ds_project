#include <string>

// Reads a whole number. Repeats until the input is valid.
int readInt(const std::string& prompt);

// Reads a price. Must be greater than 0.
double readPrice(const std::string& prompt);

// Reads a non-empty line of text.
std::string readText(const std::string& prompt);

