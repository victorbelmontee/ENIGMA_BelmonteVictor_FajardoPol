#pragma once
#include "const.h"

// Cargar un rotor desde un archivo y obtener wiring y notch
// Devuelve false si hay un error al abrir o validar
bool cargarRotor(const std::string& nombreArchivo, std::string& wiring, char& notch, std::string& mensajeError);

// Validar que el wiring tenga 26 letras únicas entre A y Z
// Comprueba longitud y que no haya letras repetidas
bool validarPermutacion(const std::string& wiring);
