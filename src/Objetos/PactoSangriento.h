//
// Created by Richi on 11/20/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_PACTOSANGRIENTO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_PACTOSANGRIENTO_H
#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"

class PactoSangriento : public ObjetoMagico {
private:
    int aumentoAtaqueMin;
    int aumentoAtaqueMax;
    int porcentajeVidaSacrificada;

    int calcularAumentoAtaque( );

public:
    PactoSangriento( int stock );
    ~PactoSangriento( ) = default;

    void aplicarEfecto( Personaje* usuario, vector<Personaje*> aliados, vector<Personaje*> enemigos ) override;
    void mostrarInformacion( ) override;

    int getAumentoAtaqueMin( );
    int getAumentoAtaqueMax( );
    int getPorcentajeVidaSacrificada( );

    void setAumentoAtaqueMin( int valor );
    void setAumentoAtaqueMax( int valor );
    void setPorcentajeVidaSacrificada( int porcentaje );
};
#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_PACTOSANGRIENTO_H