#pragma once

#include "const.h"
#include <string>

// Convierte input: pasa a mayúsculas, filtra solo A–Z.
std::string normalizeText(const std::string& input);

// Cifra el contenido de inputPath y escribe en OUTPUT_ENCRYPT_FILE.
// Devuelve false y rellena errMsg en caso de fallo.
bool encryptMessage(const std::string& inputPath, std::string& errMsg);

// Descifra desde OUTPUT_ENCRYPT_FILE y escribe en OUTPUT_DECRYPT_FILE.
// Devuelve false y rellena errMsg en caso de fallo.
bool decryptMessage(std::string& errMsg);