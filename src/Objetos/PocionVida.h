#ifndef POCION_VIDA
#define POCION_VIDA

#include "../Personajes/Personaje.h" //<- Nota: Asi se tiene que implementar en las clases hijas.
#include "ObjetoMagico.h"

class PocionVida : public ObjetoMagico {
    private:
        int curacionMinima;
        int curacionMaxima;
        /* Metodo Auxiliar para calcular el efecto aleatorio de curacion */
        int calcularEfecto( );
    public:
        PocionVida( int stock );
        ~PocionVida( ) = default;
        void aplicarEfecto( Personaje* personaje ) override;
        void mostrarInformacion( ) override;
        int getCuracionMinima( );
        int getCuracionMaxima( );
        void setCuracionMinima( int valor );
        void setCuracionMaxima( int valor );
};

#endif