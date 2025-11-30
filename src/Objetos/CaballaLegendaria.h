//
// Created by Richi on 11/20/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_CABALLALEGENDARIA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_CABALLALEGENDARIA_H


#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"
#include <vector>

using::std::vector;

class CaballaLegendaria : public ObjetoMagico {
private:
    double probabilidadExito;


    //Metodo Auxiliar privado:
    bool calcularExito( );

public:
    CaballaLegendaria( int stock );
    virtual ~CaballaLegendaria( ) = default;

    void aplicarEfecto( Personaje* usuario, vector <Personaje*> aliados, vector<Personaje*> enemigos ) override;
    void mostrarInformacion( ) override;


    //Getters:

    double getProbabilidadExito( );
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_CABALLALEGENDARIA_H