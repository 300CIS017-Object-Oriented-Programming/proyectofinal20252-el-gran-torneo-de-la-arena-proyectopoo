//
// Created by Richi on 11/20/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_CABALLALEGENDARIA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_CABALLALEGENDARIA_H


#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"

class CaballaLegendaria : public ObjetoMagico {
private:
    double probabilidadExito;
    Personaje* objetivoEnemigo;

    bool calcularExito( );

public:
    CaballaLegendaria( int stock );
    ~CaballaLegendaria( ) = default;

    void aplicarEfecto( Personaje* personaje ) override;
    void mostrarInformacion( ) override;

    void setObjetivoEnemigo( Personaje* enemigo );
    Personaje* getObjetivoEnemigo( );
    double getProbabilidadExito( );
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_CABALLALEGENDARIA_H