#pragma once

#include "const.h"
#include <string>

// Convierte input y pasa a mayúscula
std::string normalizeText(const std::string& input);

// // Cifra el contenido de inputPath i escribe a Xifrat.txt, devuelve false i llena errMsg si hay error.
bool encryptMessage(const std::string& inputPath, std::string& errMsg);

// Descifra el contenido de Xifrat.txt i escribe a Desxifrat.txt y devuelve false i llena errMsg si hi ha error.
bool decryptMessage(std::string& errMsg);
