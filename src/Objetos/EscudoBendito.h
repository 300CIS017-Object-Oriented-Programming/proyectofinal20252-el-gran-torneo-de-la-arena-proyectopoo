#ifndef ESCUDO_BENDITO_H
#define ESCUDO_BENDITO_H

#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"
#include <iostream>

using std::endl;

class EscudoBendito : public ObjetoMagico {
    private:
        int aumentoDefensaMin;
        int aumentoDefensaMax;
        int turnos;

        int calcularEfecto( );

    public:

        EscudoBendito( int stock );
        virtual ~EscudoBendito( ) = default;
        void aplicarEfecto( Personaje* usuario, vector <Personaje*> aliados, vector
        <Personaje*> enemigos, ObjetoAsignado* instancia ) override;
        void mostrarInformacion( ) override;

        //Metodos para efectos temporales:
        void revertirEfecto( Personaje * personaje,
        ObjetoAsignado* instancia) override;


        /* Getters y Setters */
        int getAumentoDefensaMin( );
        int getAumentoDefensaMax( );
        int getTurnos( );

        //Get para efectos Temporales:
        int getTurnosEfecto() override;

        //Sets:
        void setDefensaMin( int valor );
        void setDefensaMax( int valor );
        void setTurnos( int turnos );
};

#endif
