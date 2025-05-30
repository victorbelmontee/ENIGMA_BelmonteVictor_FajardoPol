#include "menu.h"
#include "rotor.h"
#include <iostream>   // Para std::cout, std::cin
#include <string>     // Para std::string

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
        std::cout << "Opció: ";
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
        }

    } while (opcion != 4);

    std::cout << "Sortint del programa...\n";
}
