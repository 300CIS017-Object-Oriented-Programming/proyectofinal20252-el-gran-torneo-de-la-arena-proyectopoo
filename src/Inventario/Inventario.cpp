#include "Inventario.h"
/*#include "../Personajes/Personaje.h"
#include "../Objetos/ObjetoMagico.h"
Nota (Pipe): en este caso no son necesarios, ya que no hay dependencia circular. Me corrigen.*/
#include "ObjetoAsignado.h"

using std::pair;

Inventario::Inventario() {
    cout << "===== INVENTARIO DEL TORNEO CREADO =====" << endl;
    // El unordered_map se inicializa automáticamente vacío
}

Inventario::~Inventario() {
    //Nota: Imlemente el destructor de Inventario (Pipe).
    cout << endl << "========================================" << endl;
    cout << "Destruyendo Inventario...."  << endl;
    cout << "Liberando " << this -> catalogoObjetos.size( ) << " objetos magicos..." << endl;

    for (pair<string, ObjetoMagico*> par: this->catalogoObjetos) {

        cout << "Liberadon memoria de: " << par.first << endl;//first es la clave (y en este caso el nombre).
        delete par.second;// par.second es el puntero a Objeto Magico.
    }

    this->catalogoObjetos.clear(); //Limpio el mapa.
    cout<< "Inventario Destruido" << endl;
    cout << "========================================" << endl;


}

/* Falta Implementar la carga de Objetos Iniciales, nose que objetos quieren que se carguen inicialmente
 * Nota (Pipe): Dos de cada tipo estaria bien, no se que piense Richi.
 */
void Inventario::cargarObjetosIniciales( ) {

    //Cargar los objetos iniciales del torneo con su stock predeterminado:

    cout << endl << "========================================" << endl;
    cout << "   CARGANDO INVENTARIO DEL TORNEO" << endl;
    cout << "========================================" << endl;

   //Pociones de Vida - Mas comunes:
    crearObjeto( new PocionVida(0), 5);


    //Amuletos de Furia - moderadamente comunes:
    crearObjeto( new AmuletoFuria(0), 3);

    //Escudo Benditos - moderadamente comunes:
    crearObjeto( new EscudoBendito(0), 3);

    //Pactos Sangrientos - raros:
    crearObjeto(new PactoSangriento(0), 2);

    //Caballas Legendarias - muy raras:
    crearObjeto( new CaballaLegendaria(0), 1);

    //Pociones de Resurreccion - rara:
    crearObjeto( new Revivir(0), 2 );

    cout << endl << "Inventario cargado exitosamente !!!!" << endl;
    cout << endl << "Total de tipos de objetos: " <<  this->catalogoObjetos.size() << endl;
    cout << "========================================" << endl;



}

void Inventario::crearObjeto( ObjetoMagico* objeto, int stockInicial ) {
    cout << "Se esta creando el objeto " << objeto -> getNombre( ) << "..." << endl;
    objeto -> setStock( stockInicial );
    this -> catalogoObjetos[ objeto -> getNombre( ) ] = objeto;
    cout << "Se han creado " << stockInicial << " " << objeto -> getNombre( ) << endl;
}

void Inventario::listarObjetos( ) {
    cout << "===== LISTA DE OBJETOS EN INVENTARIO =====" << endl;
    for( pair<string, ObjetoMagico*> par : this -> catalogoObjetos ) {
        cout << par.first << " x" << par.second -> getStock( ) << endl;
    }
    cout << "==========================================" << endl;
}

void Inventario::consultarObjeto( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        iter -> second -> mostrarInformacion( );
    } else {
        cout << "El objeto consultado no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::actualizarStock( string objeto, int nuevoStock ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        iter -> second -> setStock( nuevoStock );
        cout << "El stock del objeto " << iter -> first << " se ha actualizado, ahora dispone de " 
             << nuevoStock << " unidades!" << endl;
    } else {
        cout << "El objeto no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::eliminarObjeto( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        this -> catalogoObjetos.erase( objeto );
        cout << "El objeto " << objeto << " se ha eliminado del Inventario!" << endl;
    } else {
        cout << "El objeto no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::asignarObjetoAPersonaje( string objeto, Personaje* personaje ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        ObjetoAsignado* asignar = new ObjetoAsignado( iter -> second );
        personaje -> equiparObjeto( asignar );
        cout << personaje -> getNombre( ) << " ha equipado [ " << objeto << " ]" << endl; 
    } else {
        cout << "El objeto no se encuentra en el Inventario!" << endl;
    }
}

void Inventario::retirarObjetoDePersonaje( Personaje* personaje, int indice ) {
    ObjetoAsignado* objeto = personaje -> getObjetoEquipado( indice );

    //Validacion:
    if ( objeto == nullptr ) {
        cout << "No hay ningun objeto equipado en ese slot." << endl;
        return;
    }

    //Si el objeto no fue usado, devolver el stock al inventario
    if (!objeto->estaUsado()) {
        string nombreObjeto = objeto->getNombre();
        ObjetoMagico * tipoObjeto = buscarObjeto(nombreObjeto);

        //Otra validacion:
        if (tipoObjeto != nullptr) {
            tipoObjeto->incrementarStock();
            cout << "Stock de '" << nombreObjeto <<"' devuelto al inventario." << endl;
        }
    }
    else {
        // El objeto ya fue usado, no devolver stock
        cout << "EL objeto ya fue usado y no puede devolverse al Stock. " << endl;
    }

        //Retirarn el objeto del persoaje (este usado o no).
        personaje->retirarObjeto(indice);
        cout << "Objeto retirado exitosamente del personaje." << endl;

}

ObjetoMagico* Inventario::buscarObjeto( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        return iter -> second;
    }

    return nullptr;
}

int Inventario::getStock( string objeto ) {
    unordered_map<string, ObjetoMagico*>::iterator iter = this -> catalogoObjetos.find( objeto );
    if( iter != this -> catalogoObjetos.end( ) ) {
        return iter -> second -> getStock( );
    }

    return NULL;
}

int Inventario::getStockTotal( ) {
    int total = 0;
    for( pair<string, ObjetoMagico*> par : this -> catalogoObjetos ) {
        total += par.second -> getStock( );
    }

    return total;
}
