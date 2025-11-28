#ifndef ESCUDO_BENDITO_H
#define ESCUDO_BENDITO_H

#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"
#include <iostream>

class EscudoBendito : public ObjetoMagico {
    private:
        int aumentoDefensaMin;
        int aumentoDefensaMax;
        int turnos;

        int calcularEfecto( );
    public:
        EscudoBendito( int stock );
        virtual ~EscudoBendito( ) = default;
        void aplicarEfecto( Personaje* personaje ) override;
        void mostrarInformacion( ) override;

        /* Getters y Setters */
        int getAumentoDefensaMin( );
        int getAumentoDefensaMax( );
        int getTurnos( );
        void setDefensaMin( int valor );
        void setDefensaMax( int valor );
        void setTurnos( int turnos );
};

#endif
