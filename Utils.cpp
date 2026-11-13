#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cmath>
using namespace std;

// If the input stream is closed (Ctrl+D / end of file), stop the program
// instead of looping forever.
static void checkEndOfInput() {
    if (cin.eof()) {
        cout << "\nInput closed. Exiting.\n";
        exit(0);
    }
}

// Shows the prompt and reads one whole line.
// Exits if the input is closed or broken (avoids an endless loop).
static string readLine(const string& prompt) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) {
        checkEndOfInput();
        cout << "\nInput error. Exiting.\n";
        exit(1);
    }
    return line;
}

// Returns a copy of the text without spaces/tabs at the start and end
static string trim(const string& text) {
    size_t start = 0;
    while (start < text.size() && (text[start] == ' ' || text[start] == '\t' || text[start] == '\r')) {
        start++;
    }
    size_t end = text.size();
    while (end > start && (text[end - 1] == ' ' || text[end - 1] == '\t' || text[end - 1] == '\r')) {
        end--;
    }
    return text.substr(start, end - start);
}

// True if text is: optional '+'/'-' followed by one or more digits.
// Rejects "3.7", "1x", "1e5", "" etc.
static bool isWholeNumber(const string& text) {
    size_t i = 0;
    if (i < text.size() && (text[i] == '+' || text[i] == '-')) i++;
    if (i == text.size()) return false;   // sign only, or empty
    for (; i < text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') return false;
    }
    return true;
}

// True if text is digits with at most one '.', and at least one digit.
// Accepts "12", "12.5", ".5", "12."; rejects "12.5.3", "5abc", "-5", "inf", "nan", "1e3".
static bool isDecimalNumber(const string& text) {
    int digits = 0;
    int dots = 0;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] >= '0' && text[i] <= '9') {
            digits++;
        } else if (text[i] == '.') {
            dots++;
            if (dots > 1) return false;
        } else {
            return false;
        }
    }
    return digits > 0;
}

// The whole line must be a whole number that fits in an int.
int readInt(const string& prompt) {
    while (true) {
        string text = trim(readLine(prompt));
        if (isWholeNumber(text)) {
            errno = 0;
            long value = strtol(text.c_str(), nullptr, 10);
            if (errno != ERANGE && value >= INT_MIN && value <= INT_MAX) {
                return static_cast<int>(value);
            }
        }
        cout << "Invalid input. Please enter a whole number.\n";
    }
}

// The whole line must be a decimal number greater than 0.
double readPrice(const string& prompt) {
    while (true) {
        string text = trim(readLine(prompt));
        if (isDecimalNumber(text)) {
            errno = 0;
            double value = strtod(text.c_str(), nullptr);
            if (errno != ERANGE && isfinite(value) && value > 0) {
                return value;
            }
        }
        cout << "Invalid price. Please enter a number greater than 0.\n";
    }
}

string readText(const string& prompt) {
    string text;
    while (true) {
        cout << prompt;
        if (!getline(cin, text)) checkEndOfInput();
        if (!text.empty()) return text;
        cout << "Input cannot be empty.\n";
    }
}
