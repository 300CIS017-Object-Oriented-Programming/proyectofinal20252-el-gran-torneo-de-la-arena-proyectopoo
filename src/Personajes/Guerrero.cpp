//
// Created by felip on 17/11/2025.
//

#include "Guerrero.h"

// Constructores y destrucotres:


Guerrero::Guerrero( ) : Personaje( ) { //Constructor por defecto, llama al constructor de Personaje.
    this -> rol = "Guerrero";
    this -> probabilidadCritico = 0.25; // 25% de probabilidad de critico.
    // Los guerreros tienen mas vida y defensa.
    this -> vida = 150;
    this -> vidaMaxima = 150;
    this -> defensa = 15;
}

Guerrero::Guerrero( string nombre, string bando, int nivel, int vida, int ataque, int defensa )
                  : Personaje( nombre, "Guerrero" , bando, nivel, vida, ataque, defensa ) { // Reutilizo el constructor
                                                                                            // parametrizado de Personaje.
    // inicializo con valores espcificos:
    this -> probabilidadCritico = 0.25; // 25% de probabilidad de hacer critico.

}

bool Guerrero::isEsCritico( ) {
    // Genera un numero aleatorio entre 0 y 1.0.
    // Si es menor a probabilidad Critico es un golpe critico.
    double random;

    random = ( double ) rand( ) / RAND_MAX;
    // RAND_MAX: constante (macro) de la librería estándar.
    // (double)rand():  convierte el resultado de rand() a double, ya que rand() devuelve un int.

    return random < this -> probabilidadCritico;
}

int Guerrero::calcularDanioCritico( int danioBase ) {
    // Los criticos hacen el doble de daño:
    return danioBase * 2;
}

// Metodos sobre escritos del Personaje:

void Guerrero::realizarAccion( Personaje* objetivo ) {
    // El Guerrero con posibilidad de critico


    if( !this -> isEstaVivo ) { // los muertos no atacan.
        cout << this -> nombre << " esta derrotado y no puede atacar." << endl;
        return;
    }

    // Verificamos que sea enemigo el objetivo:
    if( this -> bando == objetivo -> getBando( ) ) {
        cout << "No puede atacar a un aliado. ¡¡¡¡¡¡Solo ataca Enemigos!!!!!" << endl;
        return;
    }

    if( !objetivo -> getIsEstaVivo( ) ) {//Si no esta vivo para que ataca al chico.
        cout << "El objetivo ya esta derrotado." << endl;
        return;
    }

    // Cacular el daño base del guerrero:
    int danioBase = this -> ataque; // se declara aqui ya que si no pasa los condicionales de arriba
    // no hay necesidad de realizar ninguna declaracion.
    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║    ESTOCADA MORTAL                     ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " invoca todo su poder!!!!" << endl;
    // Verificamos si es un golpe critico

    pausar(1200); //Para que el usuario pueda leer el texto.

    if( isEsCritico( ) ) {
        int danioCritico = calcularDanioCritico( danioBase );
        cout << "¡¡¡¡GOLPE CRITICO!!!!" << endl;
        cout << this -> nombre << " ataca a " << objetivo -> getNombre( )
        << " con un golpe devastador!" << endl;
        objetivo -> recibirDanio( danioCritico );
    }
    else { // Si no lo es realizamos un ataque normal:
        cout << this -> nombre << " ataca a " << objetivo -> getNombre( ) << "!!!!!" <<endl;
        objetivo -> recibirDanio( danioBase );
    }
}

// Metodos sobre escritos del Personaje (para la IA del juego):

void Guerrero::realizarAccionIA( vector<Personaje*> aliados, vector <Personaje * >enemigos) {
    /*IA del Guerrero: ataca al enemigo con menos vida.
     * Estrategia: Eliminar objetivos debiles primero.
     */

    if ( !this-> isEstaVivo) {
        return; //Los muertos no atacan.
    }

    cout << endl << ">> " << this->nombre << " (Guerrero) analiza el campo de batalla..." << endl;
    pausar(2000);  //  Pausa para crear tensión

    //Buscar al enemigo con menos vida:

    Personaje * objetivo = nullptr;
    int menorVida = 9999;

    for ( int i = 0 ; i < enemigos.size(); i++) {

         if ( enemigos[i]->getIsEstaVivo() && enemigos[i] -> getVida() < menorVida) {
            menorVida = enemigos[i] -> getVida();
            objetivo = enemigos[ i ];
        } //Condicional especifico para que busque el enemigo con menor vida.

    }

    if (objetivo != nullptr) {
        realizarAccion(objetivo); //Reutilizamos la logica de la accion.
    }
    else {
        cout << this-> nombre << " no encuentra objetivos vivos." << endl;
    }

}



bool Guerrero::realizarAccionJugador(vector<Personaje*> aliados, vector<Personaje*> enemigos) {
    /*El Guerrero ataca enemigos. El jugador selecciona a cual. */

    if (!this -> isEstaVivo) {
        cout << this-> nombre << " esta derrotado y no puede actuar." << endl;
        return false;
    }

    Personaje * objetivo = seleccionarObjetivo( enemigos, "o-__-o Seleccione un enemigo para atacar : ");

    if (objetivo != nullptr) {
        realizarAccion(objetivo);
        return true;
    }
    return false;
}


void Guerrero::mostrarInformacion( ) {
    // Muestar informacion detallada del guerrero:
    cout << endl << "======== Informacion del Guerrero ========" << endl;

    cout << "Nombre: " << this -> nombre << endl;
    cout << "Bando: " << this -> bando << endl;
    cout << "Nivel: " << this -> nivel << endl;
    cout << "Vida: " << this -> vida << endl;
    cout << "Ataque: "<< this -> ataque << endl;
    cout << "Defensa: " << this -> defensa << endl;
    cout << "Probabilidad Critico: " << ( this -> probabilidadCritico * 100 ) << "%" << endl;
    cout << "Estado: " << ( this->isEstaVivo ? "Vivo" : "Derrotado (Con su creador)" ) << endl; //
    // Se coloca un condicional en el cout de arriba para que de el estado real del Guerrero.
    cout << "Objetos equipados: " << this -> objetosEquipados.size( ) << "/2" << endl;
    /*Pendiente realizado: Aplicamos el metodo para mostrar los objetos equipados. */
    mostrarObjetosEquipados();

    cout << "==========================================" << endl;
}