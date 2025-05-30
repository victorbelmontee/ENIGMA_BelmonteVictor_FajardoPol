#include "menu.h"
#include "rotor.h"
#include "enigma.h"

// Mostrar menú principal
// Gestiona las diferentes opciones del programa Enigma
void mostrarMenu() {
    int opcion = 0;

    // Variables para almacenar la configuración de los rotors
    std::string rotor1, rotor2, rotor3;
    char notch1 = 'Z';
    char notch2 = 'Z';
    char notch3 = 'Z';
    std::string mensaje;

    // Bucle principal del menú
    do {
        // Mostrar las opciones disponibles
        std::cout << "\nENIGMA:\n";
        std::cout << "-------------------------------\n";
        std::cout << "1. Xifrar missatge\n";
        std::cout << "2. Desxifrar missatge\n";
        std::cout << "3. Editar rotors\n";
        std::cout << "4. Sortir\n";
        std::cout << "Opcio: ";
        std::cin >> opcion;

        // Opciones de cifrado o descifrado requieren cargar rotors primero
        if (opcion == 1 || opcion == 2) {
            std::cout << "\n[INFO] Carregant rotors...\n";

            // Cargar los tres rotors desde archivos
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

            // Opción 1: Cifrar mensaje desde archivo
            if (opcion == 1) {
                std::string error;
                bool correcto = encryptMessage("Missatge.txt", error);
                if (!correcto) {
                    std::cout << error << "\n";
                }
            }

            // Opción 2: Descifrar mensaje desde archivo
            if (opcion == 2) {
                std::string error;
                bool correcto = decryptMessage(error);
                if (!correcto) {
                    std::cout << error << "\n";
                }
            }
        }

        // Opción 3: Modificar configuración de rotors
        if (opcion == 3) {
            // Preguntar qué rotor editar (1-3)
            int numero;
            std::cout << "Quin rotor vols editar? (1–3): ";
            std::cin >> numero;

            if (numero < 1 || numero > 3) {
                std::cout << "[ERROR] Numero de rotor no valid.\n";
                continue;
            }

            // Pedir nueva permutación para el rotor
            std::string wiring;
            std::cout << "Introdueix la nova permutacio (26 lletres A-Z sense repetir): ";
            std::cin >> wiring;

            // Validar longitud
            if (wiring.length() != 26) {
                std::cout << "[ERROR] Permutacio invalida — ha de tenir exactament 26 lletres.\n";
                continue;
            }

            // Validar caracteres y unicidad
            int contador[26] = { 0 };
            bool valid = true;

            // Comprobar que son letras mayúsculas
            for (int i = 0; i < 26; i++) {
                char c = wiring[i];
                if (c < 'A' || c > 'Z') {
                    valid = false;
                    break;
                }
                contador[c - 'A']++;
            }

            // Comprobar que no hay repeticiones
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

            // Guardar el nuevo rotor en archivo
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
