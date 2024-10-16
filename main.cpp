#include "MLQ.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Función para procesar un solo archivo
void procesarArchivo(const std::string& nombreArchivo) {
    MLQ planificador;
    std::ifstream archivoEntrada(nombreArchivo);

    if (!archivoEntrada) {
        std::cerr << "Error: No se pudo abrir el archivo de entrada '" << nombreArchivo << "'." << std::endl;
        return;
    }

    std::string linea;
    std::getline(archivoEntrada, linea); // Saltar la línea de encabezado

    while (std::getline(archivoEntrada, linea)) {
        std::istringstream iss(linea);
        std::string etiqueta;
        int tiempoRafaga, tiempoLlegada, cola, prioridad;
        char delimitador;

        if (std::getline(iss, etiqueta, ';') &&
            iss >> tiempoRafaga >> delimitador >> tiempoLlegada >> delimitador >> cola >> delimitador >> prioridad) {
            planificador.agregarProceso(Proceso(etiqueta, tiempoRafaga, tiempoLlegada, cola, prioridad));
        }
    }

    archivoEntrada.close();

    // Ejecutar el algoritmo MLQ
    planificador.ejecutar();

    // Generar nombre del archivo de salida
    std::string nombreArchivoSalida = "salida_" + nombreArchivo;
    planificador.imprimirResultados(nombreArchivoSalida);

    std::cout << "Procesamiento completado para '" << nombreArchivo << "'. Resultados guardados en '" << nombreArchivoSalida << "'." << std::endl;
}

int main() {
    // Lista de nombres de archivos de entrada
    std::vector<std::string> archivosEntrada = {
        "entrada1.txt",
        "entrada2.txt",
        "entrada3.txt"
    };

    // Procesar cada archivo de entrada
    for (const auto& archivo : archivosEntrada) {
        procesarArchivo(archivo);
    }

    return 0;
}