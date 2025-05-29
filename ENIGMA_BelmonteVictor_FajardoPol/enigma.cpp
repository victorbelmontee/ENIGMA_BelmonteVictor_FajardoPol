#include "enigma.h"
#include "rotor.h"
#include <fstream>
#include <algorithm>
#include <cctype>

std::string normalizeText(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (char c : input) {
        if (std::isalpha(c)) {
            out += std::toupper(c);
        }
    }
    return out;
}

bool encryptMessage(const std::string& inputPath, std::string& errMsg) {

    return false;
}

bool decryptMessage(std::string& errMsg) {

    return false;
}
