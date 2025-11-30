#ifndef REVIVIR_H
#define REVIVIR_H

#include "../Personajes/Personaje.h"
#include "ObjetoMagico.h"
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

/* Este objeto revivira a un compañero aliado siempre y cuando el compañero este muerto,
   adicional lo hara solo con un 50% de su vida maxima. */
class Revivir : public ObjetoMagico {
    public:
        Revivir( int stock );
        virtual ~Revivir( ) = default;
        void aplicarEfecto( Personaje* usuario, vector <Personaje*> aliados, vector<Personaje*> enemigos ) override;
        void mostrarInformacion( ) override;


};

#endif