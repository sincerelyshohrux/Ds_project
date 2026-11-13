#include "Utils.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

// If the input stream is closed (Ctrl+D / end of file), stop the program
// instead of looping forever.
static void checkEndOfInput() {
    if (cin.eof()) {
        cout << "\nInput closed. Exiting.\n";
        exit(0);
    }
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        checkEndOfInput();
        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readPrice(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        checkEndOfInput();
        cout << "Invalid price. Please enter a number greater than 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
