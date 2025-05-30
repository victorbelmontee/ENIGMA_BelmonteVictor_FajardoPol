#pragma once

#include <string>     // Para std::string

// Cargar un rotor desde un archivo
bool cargarRotor(const std::string& nombreArchivo, std::string& wiring, char& notch, std::string& mensajeError);

// Validar que el wiring tenga 26 letras únicas entre A y Z
bool validarPermutacion(const std::string& wiring);
