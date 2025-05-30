#include "menu.h"
#include "rotor.h"
#include "enigma.h"

// Mostrar menú principal
void mostrarMenu() {
    int opcion = 0;

    // Strings de los 3 rotors y sus notch
    std::string rotor1, rotor2, rotor3;
    char notch1 = 'Z';
    char notch2 = 'Z';
    char notch3 = 'Z';
    std::string mensaje;

    do {
        std::cout << "\nENIGMA:\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Xifrar missatge\n";
        std::cout << "2. Desxifrar missatge\n";
        std::cout << "3. Editar rotors\n";
        std::cout << "4. Sortir\n";
        std::cout << "Opcio: ";
        std::cin >> opcion;

        if (opcion == 1 || opcion == 2) {
            std::cout << "\n[INFO] Carregant rotors...\n";

            bool ok1 = cargarRotor("Rotor1.txt", rotor1, notch1, mensaje);
            if (!ok1) {
                std::cout << mensaje << "\n";
                continue;
            }

            bool ok2 = cargarRotor("Rotor2.txt", rotor2, notch2, mensaje);
            if (!ok2) {
                std::cout << mensaje << "\n";
                continue;
            }

            bool ok3 = cargarRotor("Rotor3.txt", rotor3, notch3, mensaje);
            if (!ok3) {
                std::cout << mensaje << "\n";
                continue;
            }

            std::cout << "[OK] Rotors carregats correctament.\n";

            if (opcion == 1) {
                std::string error;
                bool correcto = encryptMessage("Missatge.txt", error);
                if (!correcto) {
                    std::cout << error << "\n";
                }
            }

            if (opcion == 2) {
                std::string error;
                bool correcto = decryptMessage(error);
                if (!correcto) {
                    std::cout << error << "\n";
                }
            }
        }

        if (opcion == 3) {
            int numero;
            std::cout << "Quin rotor vols editar? (1–3): ";
            std::cin >> numero;

            if (numero < 1 || numero > 3) {
                std::cout << "[ERROR] Numero de rotor no valid.\n";
                continue;
            }

            std::string wiring;
            std::cout << "Introdueix la nova permutacio (26 lletres A–Z sense repetir): ";
            std::cin >> wiring;

            if (wiring.length() != 26) {
                std::cout << "[ERROR] Permutacio invalida — ha de tenir exactament 26 lletres.\n";
                continue;
            }

            int contador[26] = { 0 };
            bool valid = true;

            for (int i = 0; i < 26; i++) {
                char c = wiring[i];
                if (c < 'A' || c > 'Z') {
                    valid = false;
                    break;
                }
                contador[c - 'A']++;
            }

            for (int i = 0; i < 26; i++) {
                if (contador[i] != 1) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                std::cout << "[ERROR] Permutacio invalida — calen 26 lletres uniques A–Z.\n";
                continue;
            }

            // Construir nom de fitxer sense std::to_string
            std::string nomFitxer = "Rotor";
            nomFitxer += char('0' + numero);
            nomFitxer += ".txt";

            std::ofstream out(nomFitxer);
            if (!out.is_open()) {
                std::cout << "[ERROR] No s'ha pogut escriure a " << nomFitxer << "\n";
                continue;
            }

            out << wiring << "\n";
            out.close();

            std::cout << "[OK] Rotor actualitzat correctament.\n";
        }

    } while (opcion != 4);

    std::cout << "Sortint del programa...\n";
}
