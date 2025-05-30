    #include "enigma.h"
    #include "rotor.h"

    // Función que normaliza el texto: pasa a mayúsculas y elimina cualquier carácter que no sea una letra (A-Z)
    std::string normalizeText(const std::string& input) {
        std::string output = "";

        // Recorrer cada carácter del texto de entrada
        for (int i = 0; i < input.length(); i++) {
            char c = input[i];
            // Si el carácter es una minúscula, lo convertimos a mayúscula restando 32 (valor ASCII)
            if (c >= 'a' && c <= 'z') {
                c = c - 32;
            }
            // Solo agregamos el carácter si está entre 'A' y 'Z'
            if (c >= 'A' && c <= 'Z') {
                output += c;
            }
        }

        return output;
    }

    // Función para avanzar un rotor: desplaza todos los caracteres una posición a la izquierda
    void avançarRotor(std::string& rotor) {
        // Guardar el primer carácter para colocarlo al final después del desplazamiento
        char primero = rotor[0];
        // Desplazar cada carácter a la izquierda
        for (int i = 0; i < 25; i++) {
            rotor[i] = rotor[i + 1];
        }
        // Colocar el primer carácter al final del rotor
        rotor[25] = primero;
    }

    // Función que cifra una letra pasando por 3 rotors secuencialmente
    char xifrarLletra(char letra, std::string rotor1, std::string rotor2, std::string rotor3) {
        // Calcular la posición en el alfabeto de la letra original
        int pos1 = letra - 'A';
        // Pasar la letra por el primer rotor
        char paso1 = rotor1[pos1];
        // Calcular la nueva posición basándose en la salida del primer rotor
        int pos2 = paso1 - 'A';
        // Pasar por el segundo rotor
        char paso2 = rotor2[pos2];
        // Calcular la posición para el tercer rotor
        int pos3 = paso2 - 'A';
        // Obtener la letra final tras pasar por el tercer rotor
        char paso3 = rotor3[pos3];
        return paso3;
    }

    // Función que invierte un rotor para el descifrado: genera la permutación inversa del rotor original
    std::string invertirRotor(const std::string& rotor) {
        std::string inverso = "";
        // Inicializar el string inverso con 26 caracteres 'A'
        for (int i = 0; i < 26; i++) {
            inverso += 'A';
        }
        // Para cada posición, determinar la posición inversa en el rotor
        for (int i = 0; i < 26; i++) {
            char c = rotor[i];
            int pos = c - 'A';
            // Se asigna la letra correspondiente al índice original en la posición inversa
            inverso[pos] = char('A' + i);
        }
        return inverso;
    }

    // Función que cifra el mensaje completo leyendo desde un archivo
    bool encryptMessage(const std::string& inputPath, std::string& errMsg) {
        // Abrir el archivo con el mensaje original
        std::ifstream archivo(inputPath);
        if (!archivo.is_open()) {
            errMsg = "[ERROR] No s'ha pogut obrir " + inputPath;
            return false;
        }

        // Leer el contenido del archivo línea por línea y concatenarlo
        std::string textoOriginal = "", linea;
        while (std::getline(archivo, linea)) {
            textoOriginal += linea;
        }
        archivo.close();

        // Normalizar el texto para asegurarnos que solo contenga letras mayúsculas
        std::string limpio = normalizeText(textoOriginal);

        // Cargar los tres rotores desde sus respectivos archivos
        std::string rotor1, rotor2, rotor3;
        char notch1 = 'Z', notch2 = 'Z', notch3 = 'Z';
        if (!cargarRotor("Rotor1.txt", rotor1, notch1, errMsg)) return false;
        if (!cargarRotor("Rotor2.txt", rotor2, notch2, errMsg)) return false;
        if (!cargarRotor("Rotor3.txt", rotor3, notch3, errMsg)) return false;

        // Solicitar al usuario la posición inicial para cada rotor
        char f1, f2, f3;
        std::cout << "Introdueix la posicio inicial (ex: A B C): ";
        std::cin >> f1 >> f2 >> f3;
        // Ajustar cada rotor a la posición inicial indicada por el usuario
        while (rotor1[0] != f1) avançarRotor(rotor1);
        while (rotor2[0] != f2) avançarRotor(rotor2);
        while (rotor3[0] != f3) avançarRotor(rotor3);

        std::string resultado = "";
        int total = 0;
        // Procesar cada letra del texto normalizado
        for (int i = 0; i < limpio.length(); i++) {
            // Avanzar el primer rotor en cada iteración
            avançarRotor(rotor1);
            // Si el primer rotor alcanza el notch, avanzar el segundo rotor
            if (rotor1[0] == notch1) {
                avançarRotor(rotor2);
                // Si el segundo rotor alcanza su notch, avanzar el tercer rotor
                if (rotor2[0] == notch2) {
                    avançarRotor(rotor3);
                }
            }
            // Obtener la letra original del texto limpio
            char original = limpio[i];
            // Cifrar la letra pasando por los tres rotores
            char cifrada = xifrarLletra(original, rotor1, rotor2, rotor3);
            // Añadir la letra cifrada al resultado
            resultado += cifrada;
            total++;
        }

        // Formatear el resultado agrupando las letras en bloques de 5 para mejorar legibilidad
        std::string resultadoFinal = "";
        for (int i = 0; i < resultado.length(); i++) {
            resultadoFinal += resultado[i];
            // Insertar un espacio cada 5 letras, excepto al final del mensaje
            if ((i + 1) % 5 == 0 && i != resultado.length() - 1) {
                resultadoFinal += ' ';
            }
        }

        // Escribir el mensaje cifrado en el archivo "Xifrat.txt"
        std::ofstream out("Xifrat.txt");
        if (!out.is_open()) {
            errMsg = "[ERROR] No s'ha pogut escriure a Xifrat.txt";
            return false;
        }
        out << resultadoFinal;
        out.close();

        // Calcular la cantidad total de caracteres y grupos de 5 para la salida informativa
        int grups = (total + 4) / 5;
        std::cout << "[OK] Missatge xifrat a \"Xifrat.txt\" ("
            << total << " lletres, " << grups << " grups de 5)\n";
        return true;
    }

    // Función que descifra el mensaje cifrado leyendo desde "Xifrat.txt"
    bool decryptMessage(std::string& errMsg) {
        // Abrir el archivo que contiene el mensaje cifrado
        std::ifstream archivo("Xifrat.txt");
        if (!archivo.is_open()) {
            errMsg = "[ERROR] No s'ha pogut obrir Xifrat.txt";
            return false;
        }

        // Leer todas las líneas del archivo y extraer solo las letras A-Z (omitir espacios)
        std::string textoCifrado = "", linea;
        while (std::getline(archivo, linea)) {
            for (int i = 0; i < linea.length(); i++) {
                char c = linea[i];
                if (c >= 'A' && c <= 'Z') {
                    textoCifrado += c;
                }
            }
        }
        archivo.close();

        // Cargar nuevamente los rotores para el proceso de descifrado
        std::string rotor1, rotor2, rotor3;
        char notch1 = 'Z', notch2 = 'Z', notch3 = 'Z';
        if (!cargarRotor("Rotor1.txt", rotor1, notch1, errMsg)) return false;
        if (!cargarRotor("Rotor2.txt", rotor2, notch2, errMsg)) return false;
        if (!cargarRotor("Rotor3.txt", rotor3, notch3, errMsg)) return false;

        // Solicitar la posición inicial de los rotores para el descifrado
        char f1, f2, f3;
        std::cout << "Introdueix la posicio inicial (ex: A B C): ";
        std::cin >> f1 >> f2 >> f3;
        // Ajustar cada rotor a la posición indicada
        while (rotor1[0] != f1) avançarRotor(rotor1);
        while (rotor2[0] != f2) avançarRotor(rotor2);
        while (rotor3[0] != f3) avançarRotor(rotor3);

        std::string resultado = "";
        // Procesar cada letra del mensaje cifrado
        for (int i = 0; i < textoCifrado.length(); i++) {
            // Avanzar el primer rotor
            avançarRotor(rotor1);
            // Verificar y avanzar los rotores secundarios si el rotor actual alcanza su notch
            if (rotor1[0] == notch1) {
                avançarRotor(rotor2);
                if (rotor2[0] == notch2) {
                    avançarRotor(rotor3);
                }
            }
            // Invertir cada rotor para preparar el descifrado (crear la permutación inversa)
            std::string inv1 = invertirRotor(rotor1);
            std::string inv2 = invertirRotor(rotor2);
            std::string inv3 = invertirRotor(rotor3);

            // Procesar la letra cifrada y descifrarla usando los rotores invertidos
            char letra = textoCifrado[i];
            int pos1 = inv3[letra - 'A'] - 'A';
            char paso1 = inv2[pos1];
            int pos2 = paso1 - 'A';
            char paso2 = inv1[pos2];

            // Agregar la letra descifrada al resultado final
            resultado += paso2;
        }

        // Escribir el mensaje descifrado en el archivo "Desxifrat.txt"
        std::ofstream out("Desxifrat.txt");
        if (!out.is_open()) {
            errMsg = "[ERROR] No s'ha pogut escriure a Desxifrat.txt";
            return false;
        }
        out << resultado;
        out.close();

        // Informar al usuario sobre la longitud del mensaje descifrado
        std::cout << "[OK] Missatge desxifrat a \"Desxifrat.txt\" ("
            << resultado.length() << " lletres)\n";
        return true;
    }