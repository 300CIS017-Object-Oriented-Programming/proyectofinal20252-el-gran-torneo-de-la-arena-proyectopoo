#include "Inventario.h"
#include "../Personajes/Personaje.h"
#include "../Objetos/ObjetoMagico.h"
#include "ObjetoAsignado.h"

using std::pair;

Inventario::Inventario( ) {

}

void Inventario::cargarObjetosIniciales( ) {

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
