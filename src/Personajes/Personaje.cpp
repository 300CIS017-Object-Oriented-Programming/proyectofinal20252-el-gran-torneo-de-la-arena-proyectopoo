//
// Created by felip on 13/11/2025.
//

#include "Personaje.h"
//#include "ObjetoAsignado.h" // <- leer el comentario en Personaje.h, es posible que tengamos que dejar esto
// dado a que es posible a que haya una dependencia circular. incluir esto aqui nos permite tratar con ella, confirmar.
// Si se mete los objetos a un directorio dentro del prcyecto de Clion seria:
// "(nombre del directorio)/ObjetoAsignado.h" .


Personaje::Personaje( ) {
    // Cosntructor por defecto - Inicializa valores basicos:
    this -> nombre = "Sin nombre";
    this -> rol = "Desconocido";
    this -> bando = "Neutral";
    this -> nivel = 1;
    this -> vida = 100;
    this -> vidaMaxima = vida;
    this -> ataque = 10;
    this -> defensa = 5;
    this -> isEstaVivo = true;
}

Personaje::Personaje( string nombre, string rol, string bando, int nivel, int vida, int ataque, int defensa ) {
    //Constructor con parametros- Recibe todos los valores iniciales:
    this -> nombre = nombre;
    this -> rol = rol;
    this -> bando = bando;
    this -> nivel = nivel;
    this -> vida = vida;
    this -> vidaMaxima = vida; // La vida maxima es igual a la vida inicial.
    this -> ataque = ataque;
    this -> defensa = defensa;
    this -> isEstaVivo = true; // Todos los personaje inician vivos.
}

Personaje::~Personaje( ) {
    //Desctructor: Se debe liberar memoria de los objetos equipados
    //Pediente-> Cuando implementemos ObjetoAsignado, liberar cada objeto.
    //Por ahora solo limpiamos el vector

    this -> objetosEquipados.clear( );
}

//Gets:

string Personaje::getNombre( ) {
    return this -> nombre;
}

string Personaje::getRol( ) {
    return this -> rol;
}

string Personaje::getBando( ) {
    return this -> bando;
}

int Personaje::getVida( ) {
    return this -> vida;
}

int Personaje::getVidaMaxima( ) {
    return this -> vidaMaxima;
}

int Personaje::getAtaque( ) {
    return this -> ataque;
}

int Personaje::getDefensa( ) {
    return this -> defensa;
}

int Personaje::getNivel( ) {
    return this -> nivel;
}

bool Personaje::getIsEstaVivo( ) {
    return this -> isEstaVivo;
}

// Sets:

void Personaje::setVida( int vida ) {
    // En este set hacemos lo basico de modificar la vida, pero le metemos una logica adicional
    // Para que no se pueda exceder el maximo de vida inicial, o si es menor o igual a cero, que de una vez modifique el
    // isEstaVivo, la variable que nos dice si un personaje esta vivo o no.

    if( vida > this -> vidaMaxima ) {
        this -> vida = this -> vidaMaxima;
    } else {
        this -> vida = vida;
    }

    //Si la vida llega a 0 o menos, el personaje estira la pata.
    if( this -> vida <= 0 ) {
        this -> vida = 0;
        this -> isEstaVivo = false; // <- Yo en parciales.
    }
}

void Personaje::setAtaque( int ataque ) {
    //Modifica el ataque, util cuando se usan objetos magicos.
    this -> ataque = ataque;
}

void Personaje::setDefensa( int defensa ) {
    //Modifica la defensa, util cuando se usan objetos magicos.
    this -> defensa = defensa;
}

//Metodos para el combate:

void Personaje::recibirDanio( int danio ) {
    // Calcula el daño real considerando la defensa:
    int danioReal = danio - this -> defensa;

    //La defensa puede reducir el daño pero nunca puede hacerlo negativo
    if( danioReal < 0 ) {
        danioReal = 0;
    }

    //Aplica el daño:
    this -> vida -= danioReal;

    cout << this -> nombre << " recibe: " << danioReal << " puntos de daño >_<. Vida restante: " <<
            this -> vida << endl;

    // Verifica si el personaje murio:

    if( this -> vida <= 0 ) {
        this -> vida = 0;
        this -> isEstaVivo = false;
        cout << this -> nombre << " Ha sido derrotado !!!!!" << endl;
    }
}

bool Personaje::isPuedeEquiparObjeto( ) {
    // Cada heroe solo puede equipar un maximo de 2 objetos:
    return this -> objetosEquipados.size( ) < 2; // si se cumple devuelve un true y si no devuelve un false
}


void Personaje::equiparObjeto( ObjetoAsignado* objeto) {
    // Equipa el objeto si hay espacio disponible:

    if( isPuedeEquiparObjeto( ) ) {
        this -> objetosEquipados.push_back( objeto );
        cout << this -> nombre << " ha equipado un objeto." << endl;// <- Pendiente: cuando tengamos
        //implementado los objetos y objetos asignados hay que agregarle al cout que le de el nombre
    }
    else {
        cout << this  -> nombre << "no puede equipar mas objetos magicos (maximo de 2). " << endl;
    }
}

void Personaje::usarObjeto( int indice ) {
    // Usa el objeto en la posicion indica por el indice.
    //-> Pendiente: Implementar cuando tengamos ObjetoAsignado
    if( indice >= 0 && indice < this -> objetosEquipados.size( ) ) {
        // Aqui se llamara a objetosEquipados[indice]->aplicarEfecto(this);
        cout << this -> nombre << " usa un objeto." << endl; // Pendiente: Aqui tambien se le
        // debe agregar el nombre del objeto asignado;
        // Pendiente: Despues de usar el objeto se marca como usado o se elimana (el ObjetoAsignado no
        // el ObjetoMagico como tal).
    }
    else {
        cout << "Indice de objeto invalido." << endl;
    }

}


ObjetoAsignado* Personaje::getObjetoEquipado( int indice ) {
    // Retorna el objeto en la posicion indicada usando punteros.
    if( indice >=  0 && indice < this -> objetosEquipados.size( ) ) {
        return this -> objetosEquipados[ indice ];
    }
    return nullptr; // Retorna nulltpr si el indice es invalido.
}

