//
// Created by felip on 17/11/2025.
//

#include "Mago.h"

//Constructores y destructores:

Mago::Mago( ) : Personaje( ) {// Reutilizo el constructor de Personaje

    // Constructor por defecto:
    this -> rol = "Mago";
    this -> poderMagico = 30;
    this -> factorIgnorarDefensa = 0.5 ; // Ignora el 50% de la defensa del enemigo.
    this -> vida = 80;
    this -> vidaMaxima = 80;
    this -> ataque = 80;
    this -> defensa =5; // Basicamente se podria decir que el mago es un cañon de cristal.
}

Mago::Mago( string nombre, string bando, int nivel, int vida, int ataque, int defensa )
          : Personaje( nombre, "Mago", bando, nivel, vida, ataque, defensa ) { // Reutilizo el
// constructor con parametros de Mago.
    this -> poderMagico = 30;
    this -> factorIgnorarDefensa = 0.5;
}

int Mago::calcularDanioMagico( ) {
    int variacion;
    int danio;

    // El daño magico tiene una variacion aleatoria entre -5 y 15.
    variacion = ( rand( ) % 21 ) - 5; //Rango: -5 a +15.

    //Calculo del daño:
    danio = this -> ataque + this -> poderMagico + variacion;

    // El daño no puede ser negativo :
    if( danio < 0 ) {
        danio = 0;
    }

    return danio; // Retorno el daño
}

void Mago::realizarAccion( Personaje * objetivo ) {
    // El mago lanza hechizos que ignoran parte de la defensa enemiga:

    if( !this -> isEstaVivo ) { // Los personajees derrotados no pueden realizar acciones
        cout << this -> nombre << " esta derrotado y no puede lanzar hechizos." << endl;
        return;
    }

    // Verificamos que sea enemigo el objetivo:
    if( this -> bando == objetivo -> getBando( ) ) {
        cout << "No puede atacar a un aliado. ¡¡¡¡¡¡Solo ataca Enemigos!!!!!" << endl;
        return;
    }

    if( !objetivo -> getIsEstaVivo( ) ) {// Si ya esta muerto que no ataque.
        cout << "El objetivo ya esta derrotado (Ya esta muerto, dejalo en paz)." << endl;
        return;
    }

    //Calcula el daño magico con variacion:
    int danioMagico = calcularDanioMagico( );

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║    ZOOLTRAAK                           ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " invoca el poder de la luz sagrada!" << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.

    // los ataque magicos ignoran parcialmente las defensas del objetivo.
    //Guardamos la defensa del objetivo de manera temporal:
    int defensaOriginal = objetivo -> getDefensa( );
    int defensaReducida = defensaOriginal * ( 1.0 - this -> factorIgnorarDefensa );

    // Temporalmente reducimos la defensa del objetivo :
    objetivo -> setDefensa( defensaReducida );
    cout << "El hechizo ignora " << ( this -> factorIgnorarDefensa * 100 ) <<
            "% de la defensa enemiga !!!!!" << endl;

    // Aplicamoes el daño:
    objetivo -> recibirDanio( danioMagico );

    // Restauramos la defensa original :
    objetivo -> setDefensa( defensaOriginal );

}

void Mago:: realizarAccionIA (vector <Personaje*> aliados, vector <Personaje*> enemigos) {
    /*IA del Mago: Ataca al enemigo con mayor defensa.
     *Estrategia: Aprovecha que ignora la defensa para eliminar tanques.
     */

    if ( !this->isEstaVivo) {
        return; //Los muertos no actuan.
    }

    cout << endl << ">> "  << this->nombre << " (Mago) canaliza energia arcana..." << endl;
    pausar(2000);  //  Pausa para crear tensión

    //Buscar al enemigo con mayor defensa:
    Personaje * objetivo = nullptr;
    int mayorDefensa = - 1;

    for ( int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] -> getIsEstaVivo() && enemigos[i]->getDefensa() > mayorDefensa) {
            mayorDefensa = enemigos[i] ->getDefensa();
            objetivo = enemigos[i];
        }
    }

    if (objetivo != nullptr) {
        realizarAccion(objetivo); //Reutilizamos el metodo para las acciones.
    }
    else {
        cout << this->nombre << " no encuentra objetivos vivos." << endl;
    }
}


bool Mago:: realizarAccionJugador(vector<Personaje*> aliados, vector<Personaje*> enemigos) {
    /*El Mago ataca enemigos. El jugador selecciona a cual. */

    if (!this->isEstaVivo) {
        cout << this-> nombre << " esta derrotado y no puede actuar. " << endl;
        return false;
    }

    Personaje * objetivo = seleccionarObjetivo( enemigos,
        "Seleccione un enemigo para lanzar un hechizo (Los demonios no tienen derechos): ");

    if (objetivo != nullptr) {
        realizarAccion(objetivo);
        return true;
    }

    return false;

}

void Mago::mostrarInformacion( ) { // Muestra los detalles del mago:
    cout << endl << "======== Informacion del Mago ========" << endl;

    cout << "Nombre: " << this -> nombre << endl;
    cout << "Bando: " << this -> bando << endl;
    cout << "Nivel: " << this -> nivel << endl;
    cout << "Vida: " << this -> vida << endl;
    cout << "Ataque: " << this -> ataque << endl;
    cout << "Poder Magico: " << this -> poderMagico << endl;
    cout << "Defensa: " << this -> defensa << endl;
    cout << "Ignorar Defensa: " << ( this -> factorIgnorarDefensa * 100 ) << "%" << endl;
    cout << "Estado: " << ( this -> isEstaVivo ? "Vivo (vivito y coleando)" : "Derrotado" ) << endl;
    // Se coloca un condicional en el cout de arriba para que de el estado real del Mago.

    /*Pendiente realizado: Aplicamos el metodo para mostrar los objetos equipados. */
    mostrarObjetosEquipados();

    cout << "=====================================" << endl;
}