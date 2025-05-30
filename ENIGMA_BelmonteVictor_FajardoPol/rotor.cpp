#include "rotor.h"

// Validar que wiring tenga exactamente 26 letras únicas de A a Z
bool validarPermutacion(const std::string& wiring) {
    if (wiring.length() != 26) {
        return false;
    }

    int contador[26] = { 0 };

    for (int i = 0; i < 26; i++) {
        char c = wiring[i];
        if (c < 'A' || c > 'Z') {
            return false;
        }
        contador[c - 'A']++;
    }

    for (int i = 0; i < 26; i++) {
        if (contador[i] != 1) {
            return false;
        }
    }

    return true;
}

// Cargar wiring y notch desde archivo
bool cargarRotor(const std::string& nombreArchivo, std::string& wiring, char& notch, std::string& mensajeError) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        mensajeError = "[ERROR] No s'ha pogut obrir " + nombreArchivo;
        return false;
    }

    std::string linea;
    std::getline(archivo, linea);
    wiring = linea;

    if (!validarPermutacion(wiring)) {
        mensajeError = "[ERROR] " + nombreArchivo + ": permutacio incorrecta — calen 26 lletres uniques A–Z";
        return false;
    }

    std::getline(archivo, linea);
    if (linea.empty()) {
        notch = 'Z';
    }
    else {
        notch = linea[0];
    }

    return true;
}
