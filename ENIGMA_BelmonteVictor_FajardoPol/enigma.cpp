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

// Invertir un rotor para usarlo en el proceso de desxifrado
std::string invertirRotor(const std::string& rotor) {
    // Crear un string de 26 posiciones con 'A'
    std::string inverso = "";
    for (int i = 0; i < 26; i++) {
        inverso += 'A';
    }

    // Para cada índice i, el carácter rotor[i] = c
    // significa que en el inverso en la posición (c - 'A') va 'A'+i
    for (int i = 0; i < 26; i++) {
        char c = rotor[i];
        int pos = c - 'A';
        inverso[pos] = char('A' + i);
    }

    return inverso;
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
        avançarRotor(rotor1);

        if (rotor1[0] == notch1) {
            avançarRotor(rotor2);
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

    std::cout << "[OK] Missatge xifrat a \"Xifrat.txt\" ("
        << total << " lletres, " << grups << " grups de 5)\n";

    return true;
}

// Función para desxifrar un mensaje desde Xifrat.txt
bool decryptMessage(std::string& errMsg) {
    std::ifstream archivo("Xifrat.txt");

    if (!archivo.is_open()) {
        errMsg = "[ERROR] No s'ha pogut obrir Xifrat.txt";
        return false;
    }

    std::string textoCifrado = "";
    std::string linea;

    while (std::getline(archivo, linea)) {
        for (int i = 0; i < linea.length(); i++) {
            char c = linea[i];
            if (c >= 'A' && c <= 'Z') {
                textoCifrado += c;
            }
        }
    }

    archivo.close();

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

    for (int i = 0; i < textoCifrado.length(); i++) {
        avançarRotor(rotor1);

        if (rotor1[0] == notch1) {
            avançarRotor(rotor2);
            if (rotor2[0] == notch2) {
                avançarRotor(rotor3);
            }
        }

        std::string inv1 = invertirRotor(rotor1);
        std::string inv2 = invertirRotor(rotor2);
        std::string inv3 = invertirRotor(rotor3);

        char letra = textoCifrado[i];
        int pos1 = inv3[letra - 'A'] - 'A';
        char paso1 = inv2[pos1];
        int pos2 = paso1 - 'A';
        char paso2 = inv1[pos2];

        resultado += paso2;
    }

    std::ofstream out("Desxifrat.txt");

    if (!out.is_open()) {
        errMsg = "[ERROR] No s'ha pogut escriure a Desxifrat.txt";
        return false;
    }

    out << resultado;
    out.close();

    std::cout << "[OK] Missatge desxifrat a \"Desxifrat.txt\" ("
        << resultado.length() << " lletres)\n";

    return true;
}
