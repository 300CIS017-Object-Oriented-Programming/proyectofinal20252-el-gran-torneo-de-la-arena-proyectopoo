//
// Created by Richi on 11/18/2025.
//


#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_OBJETOSASIGNADOS_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_OBJETOSASIGNADOS_H

// Librerías:
#include <iostream>
#include <string>

// Declaraciones adelantadas para evitar dependencias circulares.
class ObjetoMagico;
class Personaje;

// Usings para hacer la codificación más fluida.
using std::string;
using std::cout;
using std::endl;

class ObjetoAsignado {

    private:
        // Tipo de objeto mágico que representa (poción, amuleto, escudo, etc.).
        ObjetoMagico* tipoObjeto;

        // Indica si el objeto ya fue utilizado en el combate.
        bool usado;

    public:
        // Constructores y destructores:
        ObjetoAsignado( ObjetoMagico* tipo );
        virtual ~ObjetoAsignado( );

        // Aplica el efecto del objeto sobre el personaje (si no está usado).
        void aplicarEfecto( Personaje* personaje );

        // Marca el objeto como usado (una vez gastado en combate).
        void marcarUsado( );

        // Consulta si ya fue usado.
        bool estaUsado( );

        // Devuelve el puntero al tipo de objeto mágico.
        ObjetoMagico* getTipoObjeto( );

        // Devuelve el nombre del objeto (delegado a ObjetoMagico).
        string getNombre( );
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_OBJETOSASIGNADOS_H
