//
// Created by felip on 13/11/2025.
//

#include "Personaje.h"
#include "../Guild/Guild.h"
#include "../Inventario/ObjetoAsignado.h" // <- Para manejar la dependencia circular. (Pendiente hecho: por Angel).


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
    this-> isTieneEscudoProtector = false; //Por defecto no tiene escudo.
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
    this-> isTieneEscudoProtector = false; //Por defecto no tiene escudo.
}

Personaje::~Personaje( ) {
    //Desctructor: Se debe liberar memoria de los objetos equipados
    //Pendiente Realizado.
    for (int i = 0; i < this-> objetosEquipados.size(); i ++) {
        delete objetosEquipados[i];
    }
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

bool Personaje::getEscudoProtector() {
    return this->isTieneEscudoProtector;
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

void Personaje::setEstaVivo( bool estado ) {
    this -> isEstaVivo = estado;
}

void Personaje:: setEscudoProtector( bool estado) {
    this-> isTieneEscudoProtector = estado;
}


//Metodos auxiliares:

void Personaje::pausar(int milisegundos) {
    sleep_for( milliseconds( milisegundos ) );
}

Personaje* Personaje::seleccionarObjetivo( vector<Personaje*> objetivos, string mensaje) {
    /*Muestra una lista de objetivos vivos y permite seleccionar uno.
     * Retorna el puntero al personaje seleccionado, o nullptr si se cancela.
     * Dependiendo si es sanador o un rol atacante, cambiaria el vector que recibe en los arguementos,
     * ayuda con el encapsulamiento y hara mas facil agregarle mas heroes despues (sin importar el rol).
     *Primero lo implementare para que retorne el puntero a un objeto, despues veo como puedo hacerlo para que
     *retorne varios, pensando en el AOE del hechicero Oscuro. (Pipe)
     */

    cout << endl << mensaje << endl;
    cout << "----------------------------------------" << endl;
    int contador = 1;

    for (int i = 0; i < objetivos.size(); i++) {

        if ( objetivos[i]->getIsEstaVivo() ) {

            cout << " " << contador << ". " << objetivos[i]-> getNombre()
            << " (" << objetivos[ i ] -> getRol() << ") "
            << "-- Vida: " << objetivos[ i ]->getVida() << "/" << objetivos[ i ]->getVidaMaxima()
            << endl;
            contador++;
        }
    }

    if (contador == 1) {
        cout << "No hay objetivos disponibles." << endl;
        return nullptr;
    }

    cout << " 0. Cancelar." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Opcion: " ;

    int seleccion;
    cin >> seleccion;

    if (seleccion == 0) {
        return nullptr;
    }


    //Buscar al objetivo seleccionado:

    contador = 1;

    for (int i = 0; i < objetivos.size(); i++) {
        if ( objetivos[i]-> getIsEstaVivo() ) {
            if (contador == seleccion) {
                return objetivos[ i ];
            }
            contador ++;
        }
    }

    cout << "Seleccion invalida." << endl;
    return nullptr;
}

//Metodos para el combate:

void Personaje::recibirDanio( int danio ) {

   //Verificar que tenga el escudo protector:
    if (this->isTieneEscudoProtector) {
        cout << endl << "========================================" << endl;
        cout << "  ¡¡¡ESCUDO PROTECTOR ACTIVADO!!!" << endl;
        cout << "  " << this -> nombre << " bloquea completamente el ataque!" << endl;
        cout << "  El escudo se desvanece despues de absorber el golpe." << endl;
        cout << "========================================" << endl;
        this -> isTieneEscudoProtector = false; // El escudo se consume.
        return; // No recibe daño.
    }

    // Calcula el daño real considerando la defensa:
    int danioReal = danio - this -> defensa;

    //La defensa puede reducir el daño pero nunca puede hacerlo negativo
    if( danioReal < 0 ) {
        danioReal = 0;
    }

    //Aplica el daño:
    this -> vida -= danioReal;

    cout << this -> nombre << " recibe: " << danioReal << " puntos de daño >_<. Vida restante: " <<
            (this -> vida <= 0 ? 0 : this -> vida)<< endl;

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
        cout << this -> nombre << " ha equipado el objeto " << objeto -> getNombre( ) << endl;
    }
    else {
        cout << this  -> nombre << "no puede equipar mas objetos magicos (maximo de 2). " << endl;
    }
}

/* Implementacion del metodo retirarObjeto que no estaba */
void Personaje::retirarObjeto( int indice ) {
    if( indice >= 0 && indice < this -> objetosEquipados.size( ) ) {
        this -> objetosEquipados.erase( this -> objetosEquipados.begin( ) + indice );
    } else {
        cout << "Indice seleccionado no valido!" << endl;
    }
}

void Personaje::usarObjeto( int indice, vector<Personaje*> aliados, vector<Personaje*> enemigos ) {

    //Usa el objeto en la posicion indicada por el indice.

    if ( indice >= 0 && indice < this->objetosEquipados.size() ) {
        cout << this->nombre << " usa el objeto " << this-> objetosEquipados[ indice ] ->getNombre() << endl;
        this->objetosEquipados[ indice ] -> aplicarEfecto(this, aliados, enemigos);
        //El marcado como usado se hace dentro de aplicarEfecto de ObjetoAsignado.
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

/*Metodo para mostrar la informacion de los objetos equipados por el personaje: */

void Personaje::mostrarObjetosEquipados() {

    if (this->objetosEquipados.empty()) {
        cout << "[Ningun Objeto equipado]" << endl;
        return;
    }

    for (int i = 0; i < this-> objetosEquipados.size(); i++) {
        ObjetoAsignado * objeto = this->objetosEquipados[ i ];

        //Muestra el nombre y el estado del obejto:
        cout << "   [" << (i + 1) << "]  " << objeto->getNombre();

        if ( objeto-> estaUsado( ) ) {
            cout << "(Usado).";
        }
        else {
            cout << "(Disponible).";
        }

        cout << endl;
    }

}