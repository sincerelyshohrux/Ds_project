#ifndef UTILS_H
#define UTILS_H

#include <string>

// Input functions: they repeat until the input is valid
int readInt(const std::string& prompt);

double readPrice(const std::string& prompt);

std::string readText(const std::string& prompt);

#endif
