#ifndef OBJETO_MAGICO
#define OBJETO_MAGICO

#include <string>

using std::string;

class ObjetoMagico {
    protected: 
        string nombre;
        string descripcion;
        int    stockDisponible;
    public:
        ObjetoMagico( );
        ObjetoMagico( string nombre, string descripcion, int stockDisponible ); 
        virtual void aplicarEfecto( Personaje* personaje );
        virtual void mostrarInformacion( );
        void decrementarStock( );
        void incrementarStock( );
        
        // Getters.
        string getNombre( );
        string getDescription( );
        int getStock( );

        // Destrcuctor.
        virtual ~ObjetoMagico( );
};

#endif