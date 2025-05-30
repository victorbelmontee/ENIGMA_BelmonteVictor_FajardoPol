#pragma once

#include "const.h"
#include <string>

// Convierte input y pasa a mayúscula
// Elimina caracteres que no sean letras
std::string normalizeText(const std::string& input);

// Cifra el contenido de inputPath y escribe a Xifrat.txt
// Devuelve false y llena errMsg si hay error.
bool encryptMessage(const std::string& inputPath, std::string& errMsg);

// Descifra el contenido de Xifrat.txt y escribe a Desxifrat.txt
// Devuelve false y llena errMsg si hay error.
bool decryptMessage(std::string& errMsg);
