#include "enigma.h"
#include "rotor.h"

// Convierte el texto: pasa a mayúsculas y elimina todo lo que no sea A–Z
std::string normalizeText(const std::string& input) {
    std::string output = "";

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        // Convertir a mayúsculas si es minúscula
        if (c >= 'a' && c <= 'z') {
            c = c - 32;
        }

        // Conservar solo letras A–Z
        if (c >= 'A' && c <= 'Z') {
            output += c;
        }
    }

    return output;
}

// Avanza un rotor una posición hacia la izquierda
void avançarRotor(std::string& rotor) {
    char primero = rotor[0];

    for (int i = 0; i < 25; i++) {
        rotor[i] = rotor[i + 1];
    }

    rotor[25] = primero;
}

// Cifra una letra pasando por los 3 rotors
char xifrarLletra(char letra, std::string rotor1, std::string rotor2, std::string rotor3) {
    int pos1 = letra - 'A';
    char paso1 = rotor1[pos1];

    int pos2 = paso1 - 'A';
    char paso2 = rotor2[pos2];

    int pos3 = paso2 - 'A';
    char paso3 = rotor3[pos3];

    return paso3;
}

// Función principal que cifra el mensaje
bool encryptMessage(const std::string& inputPath, std::string& errMsg) {
    std::ifstream archivo(inputPath);

    if (!archivo.is_open()) {
        errMsg = "[ERROR] No s'ha pogut obrir " + inputPath;
        return false;
    }

    std::string textoOriginal = "";
    std::string linea;

    while (std::getline(archivo, linea)) {
        textoOriginal += linea;
    }

    archivo.close();

    std::string limpio = normalizeText(textoOriginal);

    // Cargar los rotors
    std::string rotor1, rotor2, rotor3;
    char notch1 = 'Z';
    char notch2 = 'Z';
    char notch3 = 'Z';

    if (!cargarRotor("Rotor1.txt", rotor1, notch1, errMsg)) return false;
    if (!cargarRotor("Rotor2.txt", rotor2, notch2, errMsg)) return false;
    if (!cargarRotor("Rotor3.txt", rotor3, notch3, errMsg)) return false;

    // Pedir posición inicial
    char f1, f2, f3;
    std::cout << "Introdueix la posició inicial (ex: A B C): ";
    std::cin >> f1 >> f2 >> f3;

    while (rotor1[0] != f1) avançarRotor(rotor1);
    while (rotor2[0] != f2) avançarRotor(rotor2);
    while (rotor3[0] != f3) avançarRotor(rotor3);

    std::string resultado = "";
    int total = 0;

    for (int i = 0; i < limpio.length(); i++) {
        // Avanzar rotor1 siempre
        avançarRotor(rotor1);

        // Avanzar rotor2 si rotor1 llega al notch1
        if (rotor1[0] == notch1) {
            avançarRotor(rotor2);

            // Avanzar rotor3 si rotor2 llega al notch2
            if (rotor2[0] == notch2) {
                avançarRotor(rotor3);
            }
        }

        char original = limpio[i];
        char cifrada = xifrarLletra(original, rotor1, rotor2, rotor3);

        resultado += cifrada;
        total++;
    }

    // Agrupar en bloques de 5 letras
    std::string resultadoFinal = "";

    for (int i = 0; i < resultado.length(); i++) {
        resultadoFinal += resultado[i];

        if ((i + 1) % 5 == 0 && i != resultado.length() - 1) {
            resultadoFinal += ' ';
        }
    }

    std::ofstream out("Xifrat.txt");

    if (!out.is_open()) {
        errMsg = "[ERROR] No s'ha pogut escriure a Xifrat.txt";
        return false;
    }

    out << resultadoFinal;
    out.close();

    int grups = (total + 4) / 5;

    std::cout << "[OK] Missatge xifrat a \"Xifrat.txt\" (" << total << " lletres, "
        << grups << " grups de 5)\n";

    return true;
}

// Función de desxifrat (se implementará en fase 3)
bool decryptMessage(std::string& errMsg) {
    errMsg = "[ERROR] Funció no implementada encara.";
    return false;
}