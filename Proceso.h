#ifndef PROCESO_H
#define PROCESO_H

#include <string>

class Proceso {
public:
    std::string etiqueta;
    int tiempoRafaga;      // Burst Time
    int tiempoLlegada;     // Arrival Time
    int cola;              // Queue
    int prioridad;
    int tiempoEspera;      // Waiting Time
    int tiempoFinalizacion; // Completion Time
    int tiempoRespuesta;   // Response Time
    int tiempoRetorno;     // Turnaround Time
    int tiempoRestante;
    bool iniciado;

    // Constructor
    Proceso(std::string e, int tr, int tl, int c, int p);
};

#endif // PROCESO_H