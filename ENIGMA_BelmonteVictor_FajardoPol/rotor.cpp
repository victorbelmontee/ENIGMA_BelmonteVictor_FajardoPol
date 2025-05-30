#include "rotor.h"
#include <fstream>    // Para std::ifstream
#include <string>     // Para std::string

// Validar que wiring tenga exactamente 26 letras �nicas de A a Z
bool validarPermutacion(const std::string& wiring) {
    if (wiring.length() != 26) {
        return false;
    }

    int contador[26] = { 0 }; // Contador de letras A-Z

    for (int i = 0; i < 26; i++) {
        char c = wiring[i];

        // Comprobar que sea una letra may�scula v�lida
        if (c < 'A' || c > 'Z') {
            return false;
        }

        // Convertimos la letra en �ndice (A=0, Z=25)
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

    // Leer la primera l�nea: el wiring
    std::getline(archivo, wiring);

    // Validar que el wiring sea correcto
    if (!validarPermutacion(wiring)) {
        mensajeError = "[ERROR] " + nombreArchivo + ": permutaci� incorrecta � calen 26 lletres �niques A�Z";
        return false;
    }

    // Leer la segunda l�nea: el notch
    std::string notchLinea;
    std::getline(archivo, notchLinea);

    // Si no hay l�nea o est� vac�a, usar 'Z' como notch por defecto
    if (notchLinea.empty()) {
        notch = 'Z';
    }
    else {
        notch = notchLinea[0];
    }

    return true;
}
