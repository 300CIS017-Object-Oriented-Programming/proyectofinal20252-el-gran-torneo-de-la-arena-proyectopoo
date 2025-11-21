#ifndef REVIVIR_H
#define REVIVIR_H

#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"

/* Este objeto revivira a un compañero aliado siempre y cuando el compañero este muerto,
   adicional lo hara solo con un 50% de su vida maxima. */
class Revivir : public ObjetoMagico {
    private:    
        Personaje* aliado;

    public:
        Revivir( int stock );
        virtual ~Revivir( ) = default;
        void aplicarEfecto( Personaje* personaje ) override;
        void mostrarInformacion( ) override;

        /* Getters y Setters */
        void setAliado( Personaje* aliado );
        Personaje* getAliado( );
};

#endif