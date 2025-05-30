#include "rotor.h"

// Validar que wiring tenga exactamente 26 letras únicas de A a Z
// Primero comprueba la longitud y luego verifica que todas sean letras mayúsculas sin repetición
bool validarPermutacion(const std::string& wiring) {
    // Comprobar longitud exacta de 26 caracteres
    if (wiring.length() != 26) {
        return false;
    }

    // Array para contar apariciones de cada letra
    int contador[26] = { 0 };

    // Comprobar que todos sean letras mayúsculas y contar apariciones
    for (int i = 0; i < 26; i++) {
        char c = wiring[i];
        if (c < 'A' || c > 'Z') {
            return false;
        }
        contador[c - 'A']++;
    }

    // Verificar que cada letra aparezca exactamente una vez
    for (int i = 0; i < 26; i++) {
        if (contador[i] != 1) {
            return false;
        }
    }

    return true;
}

// Cargar wiring y notch desde archivo
// El archivo debe contener el wiring en la primera línea y opcionalmente el notch en la segunda
bool cargarRotor(const std::string& nombreArchivo, std::string& wiring, char& notch, std::string& mensajeError) {
    // Intentar abrir el archivo
    std::ifstream archivo(nombreArchivo);

    // Comprobar si se pudo abrir el archivo
    if (!archivo.is_open()) {
        mensajeError = "[ERROR] No s'ha pogut obrir " + nombreArchivo;
        return false;
    }

    // Leer primera línea (wiring)
    std::string linea;
    std::getline(archivo, linea);
    wiring = linea;

    // Validar que el wiring sea correcto
    if (!validarPermutacion(wiring)) {
        mensajeError = "[ERROR] " + nombreArchivo + ": permutacio incorrecta — calen 26 lletres uniques A–Z";
        return false;
    }

    // Leer segunda línea (notch) o usar Z por defecto
    std::getline(archivo, linea);
    if (linea.empty()) {
        notch = 'Z';
    }
    else {
        notch = linea[0];
    }

    return true;
}
