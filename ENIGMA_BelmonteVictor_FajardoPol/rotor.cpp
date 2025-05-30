#include "rotor.h"
#include <fstream>    // Para std::ifstream
#include <string>     // Para std::string

// Validar que wiring tenga exactamente 26 letras únicas de A a Z
bool validarPermutacion(const std::string& wiring) {
    if (wiring.length() != 26) {
        return false;
    }

    int contador[26] = { 0 }; // Contador de letras A-Z

    for (int i = 0; i < 26; i++) {
        char c = wiring[i];

        // Comprobar que sea una letra mayúscula válida
        if (c < 'A' || c > 'Z') {
            return false;
        }

        // Convertimos la letra en índice (A=0, Z=25)
        contador[c - 'A']++;
    }

    // Verificar que cada letra aparece solo una vez
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

    // Leer la primera línea: el wiring
    std::getline(archivo, wiring);

    // Validar que el wiring sea correcto
    if (!validarPermutacion(wiring)) {
        mensajeError = "[ERROR] " + nombreArchivo + ": permutació incorrecta — calen 26 lletres úniques A–Z";
        return false;
    }

    // Leer la segunda línea: el notch
    std::string notchLinea;
    std::getline(archivo, notchLinea);

    // Si no hay línea o está vacía, usar 'Z' como notch por defecto
    if (notchLinea.empty()) {
        notch = 'Z';
    }
    else {
        notch = notchLinea[0];
    }

    return true;
}
