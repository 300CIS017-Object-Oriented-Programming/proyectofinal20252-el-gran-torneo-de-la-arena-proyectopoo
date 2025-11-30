#ifndef AMULETO_FURIA
#define AMULETO_FURIA

#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"

class AmuletoFuria : public ObjetoMagico {
    private:
        int aumentoAtaqueMin;
        int aumentoAtaqueMax;
        int turnos;
        /* Metodo Auxiliar para calcular el efecto aleatorio de la Furia */
        int calcularEfecto( );
    public:
        AmuletoFuria( int stock );
        virtual ~AmuletoFuria( ) = default;
        void aplicarEfecto( Personaje* usuario, vector <Personaje*> aliados, vector <Personaje*> enemigos ) override;
        void mostrarInformacion( ) override;

        /* Getters y Setters */
        int getAumentoAtaqueMin( );
        int getAumentoAtaqueMax( );
        int getTurnos( );

        void setAumentoAtaqueMin( int valor );
        void setAumentoAtaqueMax( int valor );
        void setTurnos( int turnos );
};

#endif