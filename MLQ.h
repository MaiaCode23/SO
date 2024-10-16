#ifndef MLQ_H
#define MLQ_H

#include <vector>
#include <queue>
#include "Proceso.h"

class MLQ {
private:
    std::vector<std::queue<Proceso*>> colas;
    std::vector<int> quantums;
    std::vector<Proceso> procesos;
    int tiempoActual;

    void ordenarProcesos();

public:
    MLQ();
    void agregarProceso(const Proceso& p);
    void ejecutar();
    void imprimirResultados(const std::string& nombreArchivoSalida);
};

#endif // MLQ_H