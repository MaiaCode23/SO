#include "Proceso.h"

// Constructor de la clase Proceso
Proceso::Proceso(std::string e, int tr, int tl, int c, int p)
    : etiqueta(e), tiempoRafaga(tr), tiempoLlegada(tl), cola(c), prioridad(p),
      tiempoEspera(0), tiempoFinalizacion(0), tiempoRespuesta(-1), tiempoRetorno(0),
      tiempoRestante(tr), iniciado(false) {
    // Inicialización de todos los atributos del proceso
}