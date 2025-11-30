//
// Created by felip on 17/11/2025.
//

#include "Sanador.h"

// Contructores y destructores:

Sanador::Sanador( ) : Personaje( ) { // Reutilizo el contructor de Personaje:
    //Contructor por defecto:
    
    this -> rol = "Sanador";
    this -> poderCuracion = 40; // Poder de curacion base.
    this -> efectividadCuracion = 0.8 ; // 80% de efectividad de base.
    // los sanadores tienen poca vida y no atacan.

    this -> vida = 90;
    this -> vidaMaxima = 90;
    this -> ataque = 0; //No hacen daño directo;
    this -> defensa = 10;
}

Sanador::Sanador( string nombre, string bando, int nivel, int vida, int defensa )
                : Personaje( nombre, "Sanador", bando, nivel, vida, 0, defensa ) {
//Uso el constructor con parametros de Personaje. Como es un sanador el ataque siempre es cero.
    this -> poderCuracion = 40;
    this -> efectividadCuracion = 0.8; // 80%
}

int Sanador::calcularCuracion( ) {
    //Curacion varia aleatoriamente segun efectividad .
    // Genera un valro entre 0% y 100% de efectividad

    double enfoqueMinimo = 0.0; // Tolerancia minima.
    double enfoqueMaximo = 1.0; // Tolerancia maxima.
    double curacionDouble; //Double para el calculo.
    int curacion; // El que se retorna.

    // Calcular un valor aleatorio entre el enfoque minimo y el maximo.
    double enfoque = enfoqueMinimo + ( (double) rand( ) / RAND_MAX ) * ( enfoqueMaximo - enfoqueMinimo );

    // Curacion = poder * efectividad del sanador * enfoque del momento.
    curacionDouble = this -> poderCuracion * this -> efectividadCuracion * enfoque;
    curacion = (int) curacionDouble;

    return curacion;
}

// Metodos sobreescritos del Personaje:

void Sanador::realizarAccion( Personaje* objetivo ) {

    // Verificamos que el sanador esta vivo:

    if( !this -> isEstaVivo ) {
        cout << this -> nombre << " esta derrotado y no puede curar." << endl;
        return;
    }

    // Verificamos que sea aliado el objetivo:
    if( this -> bando != objetivo -> getBando( ) ) {
        cout << "No puede curar enemigo. ¡¡¡¡¡¡Solo cura aliados!!!!!" << endl;
        return;
    }

    if( !objetivo -> getIsEstaVivo( ) ) {
        cout << objetivo -> getNombre( ) << " ya esta muerto y no puede ser curado." << endl;
        return;
    }

    // Calcula la curacion con efectividad variable:
    int curacion;
    curacion = calcularCuracion( );
    //Como la curacion varia entre 0 y 100% verificamos primero si es necesario correr toda
    // la logica de curacion.
    if( curacion > 0 ) {
        int efectividadPorcentaje;
        efectividadPorcentaje = (int) ( efectividadCuracion * 100 ); //Para obtener un porcentaje entero.
        cout << this -> nombre << " Canaliza energia curativa hacia " << objetivo -> getNombre( ) << "!!!!!!"
        << endl;
        cout << "Efectividad: " << efectividadPorcentaje << "%" << endl;

        pausar(1200); //Para que el usuario pueda leer el texto.

        //Obtengo la vida actual y maxima del objetivo:
        int vidaActual = objetivo -> getVida( );
        int vidaMaxima = objetivo -> getVidaMaxima( );
        int nuevaVida = vidaActual + curacion;

        // No puede exceder la vida maxiam:
        if( nuevaVida > vidaMaxima ) {
            nuevaVida = vidaMaxima;
            curacion = vidaMaxima - vidaActual; //Ajusta la curacion real.
        }

        // aplica la curacion:
        objetivo -> setVida( nuevaVida );
        cout << objetivo -> getNombre( ) << " recupera " << curacion
             << " puntos de vida. Vida actual: " << nuevaVida << "/" << vidaMaxima << endl;

        pausar(1200); //Para que el usuario pueda leer el texto.
    }

    //Si la curacion es 0% o menos (por si acaso):
    else {
        cout << this -> nombre << " intenta curar a " << objetivo -> getNombre( ) << " pero falla completamente (0%). " << endl;
        cout << "La energia curativa no se manifesto esta vez." << endl;
    }
}

void Sanador::realizarAccionIA( vector<Personaje *> aliados , vector<Personaje*> enemigos) {
    /* IA del Sanador: Cura al aliado mas herido.
     * Estrategia: Mantener vivo al equipo, nunca ataca.
     */

    if ( !this ->isEstaVivo) {
        return; //Los muertos no actuan.
    }

    cout << endl << ">> " << this-> nombre << " (Sanador) evalua el estado de sus aliados..." << endl;
    pausar(2000);  //  Pausa para crear tensión

    //Buscar al aliado mas herido (mayor diferencia entre vidaMaxima y vida actual):
    Personaje * objetivo = nullptr;
    int mayorDanio = 0;

    for ( int i = 0; i < aliados.size(); i++) {
        if ( aliados[i] -> getIsEstaVivo()) {
            int danioRecibido = aliados[i] -> getVidaMaxima() - aliados[i] ->getVida();

            if ( danioRecibido > mayorDanio) {
                mayorDanio = danioRecibido;
                objetivo = aliados[ i ];
            }
        }
    }

    if (objetivo != nullptr) {
        realizarAccion(objetivo); //Reutilizar la logica de curacion existente.
    }
    else {
        cout << this->nombre << " observa que sus aliados estan sanos." << endl;
        cout << "El sanador espera el momento adecuado para actuar." << endl;
    }

}


void Sanador::mostrarInformacion( ) {
    //Mostramos la informacion del sanador:
    cout << endl << "======== Informacion del Sanador ========" << endl;

    cout << "Nombre: " << this -> nombre << endl;
    cout << "Bando: " << this -> bando << endl;
    cout << "Nivel: " << this -> nivel << endl;
    cout << "Vida: " << this -> vida << endl;
    cout << "Poder de Curacion: " << this -> poderCuracion << endl;
    cout << "Defensa: " << this -> defensa << endl;
    cout << "Efectividad: " << ( this -> efectividadCuracion * 100 ) << "%" << endl;
    cout << "Estado: " << ( this -> isEstaVivo ? "Vivo" : "Derrotado (el sanador no se pudo sanar.)" );
    // Se coloca un condicional en el cout de arriba para que de el estado real del Mago.

    cout << "Objetos equipados: " << this -> objetosEquipados.size( ) << "/2" << endl;

    /*Pendiente realizado: Aplicamos el metodo para mostrar los objetos equipados. */
    mostrarObjetosEquipados();

    cout << "=========================================" << endl;
}