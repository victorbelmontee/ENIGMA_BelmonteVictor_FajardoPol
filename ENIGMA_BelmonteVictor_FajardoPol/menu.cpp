#include "menu.h"
#include "enigma.h"
#include "rotor.h"
#include <iostream>
#include <string>

void runMenu() {
    int option = 0;
    std::string err;
    do {
        std::cout << "\n1. Cifrar mensaje\n"
            << "2. Descifrar mensaje\n"
            << "3. Editar rotor\n"
            << "4. Salir\n"
            << "Elige una opcion: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');
        switch (option) {
        case 1:
            if (!encryptMessage(INPUT_MESSAGE_FILE, err))
                std::cout << "ERROR" << err << "\n";
            break;
        case 2:
            if (!decryptMessage(err))
                std::cout << "ERROR" << err << "\n";
            break;
        case 3:

            break;
        case 4:
            std::cout << "¡Hasta luego!\n";
            break;
        default:
            std::cout << "Opción no válida.\n";
        }
    } while (option != 4);
}
