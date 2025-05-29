#pragma once

#include "const.h"
#include <string>

// Carga y valida la permutación del rotor 'id' desde su fichero.
// Devuelve false y rellena errMsg en caso de error.
bool loadRotor(int id, std::string& wiring, char& notch, std::string& errMsg);

// Avanza la posición del rotor (y notch si aplica).
void advanceRotor(std::string& wiring, char& notch);

