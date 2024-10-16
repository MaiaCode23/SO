#include "MLQ.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <limits>

// Constructor de la clase MLQ
MLQ::MLQ() : colas(3), quantums({3, 5, std::numeric_limits<int>::max()}), tiempoActual(0) {
    // Inicialización de las colas y los quantums de tiempo
}

// Método para agregar un proceso a la lista de procesos
void MLQ::agregarProceso(const Proceso& p) {
    procesos.push_back(p);
}

// Método para ordenar los procesos por tiempo de llegada
void MLQ::ordenarProcesos() {
    std::sort(procesos.begin(), procesos.end(),
              [](const Proceso& a, const Proceso& b) {
                  return a.tiempoLlegada < b.tiempoLlegada;
              });
}

// Método principal para ejecutar el algoritmo MLQ
void MLQ::ejecutar() {
    ordenarProcesos();
    int procesosCompletados = 0;
    int totalProcesos = procesos.size();

    while (procesosCompletados < totalProcesos) {
        bool procesado = false;

        // Iterar sobre las colas de prioridad
        for (int i = 0; i < 3; ++i) {
            if (!colas[i].empty()) {
                Proceso* p = colas[i].front();
                colas[i].pop();

                // Calcular el tiempo de respuesta si es la primera vez que se ejecuta
                if (p->tiempoRespuesta == -1) {
                    p->tiempoRespuesta = tiempoActual - p->tiempoLlegada;
                }

                // Ejecutar el proceso por el quantum de tiempo o hasta que termine
                int tiempoEjecucion = std::min(p->tiempoRestante, quantums[i]);
                tiempoActual += tiempoEjecucion;
                p->tiempoRestante -= tiempoEjecucion;

                // Verificar si el proceso ha terminado
                if (p->tiempoRestante == 0) {
                    p->tiempoFinalizacion = tiempoActual;
                    p->tiempoRetorno = p->tiempoFinalizacion - p->tiempoLlegada;
                    p->tiempoEspera = p->tiempoRetorno - p->tiempoRafaga;
                    procesosCompletados++;
                } else {
                    // Si no ha terminado, volver a ponerlo en la cola
                    colas[i].push(p);
                }

                procesado = true;
                break;
            }
        }

        // Si no se procesó ningún proceso, avanzar el tiempo
        if (!procesado) {
            tiempoActual++;
        }

        // Verificar si hay nuevos procesos que llegaron
        for (auto& proceso : procesos) {
            if (proceso.tiempoLlegada <= tiempoActual && proceso.tiempoRestante > 0 && !proceso.iniciado) {
                colas[proceso.cola - 1].push(&proceso);
                proceso.iniciado = true;
            }
        }
    }
}

// Método para imprimir los resultados en un archivo
void MLQ::imprimirResultados(const std::string& nombreArchivoSalida) {
    std::ofstream archivoSalida(nombreArchivoSalida);
    archivoSalida << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

    double totalTE = 0, totalTF = 0, totalTR = 0, totalTRT = 0;

    for (const auto& p : procesos) {
        archivoSalida << p.etiqueta << ";" << p.tiempoRafaga << ";" << p.tiempoLlegada << ";" 
                      << p.cola << ";" << p.prioridad << ";" << p.tiempoEspera << ";" 
                      << p.tiempoFinalizacion << ";" << p.tiempoRespuesta << ";" << p.tiempoRetorno << "\n";

        totalTE += p.tiempoEspera;
        totalTF += p.tiempoFinalizacion;
        totalTR += p.tiempoRespuesta;
        totalTRT += p.tiempoRetorno;
    }

    int n = procesos.size();
    archivoSalida << std::fixed << std::setprecision(1);
    archivoSalida << "WT=" << (totalTE / n) << "; CT=" << (totalTF / n) << "; RT=" 
                  << (totalTR / n) << "; TAT=" << (totalTRT / n) << ";\n";

    archivoSalida.close();
}