//
// Hechicero Oscuro - Implementación
// Especializado en magia oscura que daña tanto a enemigos como a aliados
//

#include "HechiceroOscuro.h"

// Constructores

HechiceroOscuro::HechiceroOscuro( ) : Personaje( ) {
    // Constructor por defecto
    this -> rol = "Hechicero Oscuro";
    this -> poderOscuro = 50;
    this -> porcentajeDanioAOE = 0.5;  // 50% del daño principal se aplica como AoE
    this -> radioAOE = 2;               // Afecta a 2 objetivos adicionales

    // Stats balanceados: mucho daño pero baja vida
    this -> vida = 70;
    this -> vidaMaxima = 70;
    this -> ataque = 50;
    this -> defensa = 20;  // Defensa elevada como compensación
}

HechiceroOscuro::HechiceroOscuro( string nombre, string bando, int nivel, int vida, int ataque, int defensa )
    : Personaje( nombre, "Hechicero Oscuro", bando, nivel, vida, ataque, defensa ) {
    // Constructor parametrizado
    this -> poderOscuro = 50;
    this -> porcentajeDanioAOE = 0.4;
    this -> radioAOE = 2;
}

// Métodos auxiliares privados

int HechiceroOscuro::calcularDanioOscuro( ) {
    // Calcula el daño oscuro con variación aleatoria
    int variacion = ( rand( ) % 31 ) - 10;  // Rango: -10 a +20
    int danio = this -> ataque + this -> poderOscuro + variacion;

    if( danio < 0 ) {
        danio = 0;
    }

    return danio;
}

int HechiceroOscuro::calcularDanioColateral( int danioBase ) {
    // Calcula el daño colateral (AoE) basado en el daño principal
    return ( int )( danioBase * this -> porcentajeDanioAOE );
}

// Métodos sobrescritos

void HechiceroOscuro::realizarAccion( Personaje* objetivo ) {
    // Ataque principal del Hechicero Oscuro

    if( !this -> isEstaVivo ) {
        cout << this -> nombre << " esta derrotado y no puede lanzar hechizos oscuros." << endl;
        return;
    }

    //Quitamos la validacion de Bando del hechicero Oscuro.

    if( !objetivo -> getIsEstaVivo( ) ) {
        cout << "El objetivo ya esta derrotado." << endl;
        return;
    }

    // Calcular daño oscuro
    int danioOscuro = calcularDanioOscuro( );

    //El costo de la magia Oscura, pierde 10% de su vida maxima

    int costoVida = this-> vidaMaxima/10 ; //10% de la vida maxima

    cout << endl << "============================================" << endl;
    cout << "          MAGIA OSCURA DESATADA" << endl;
    cout << "============================================" << endl;
    cout << this -> nombre << " Canaliza energia Oscura...." << endl;
    cout << "El poder corrompe su propia esencia!!!" << endl;
    cout << this->nombre << " Sacrifica " << costoVida << " Puntos de vida" << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.

    //Aplicar el costo de vida al hechicero:

    this->vida -= costoVida;
    cout << "Vida restante de " << this->nombre << ": " << (this->vida <= 0? 0: this->vida
        )<< "/" << this->vidaMaxima << endl;


    //Verificamos si el hechicero muere por su propio poder:
    if (this-> vida <=0 ) {
        this->vida = 0;
        this->isEstaVivo = false;
        cout << endl << "La Magia Oscura ha consumido a " << this->nombre <<"!!!!" << endl;
        cout << this->nombre << " Ha sido derrotado por su propio poder !!! " << endl;
        cout << "============================================" << endl;
        pausar(1200); //Para que el usuario pueda leer el texto.
        return; //Muere antes de atacar.
    }

    cout << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.
    //Advertencia si ataca aliado (pues si lo permite):
    if ( this-> bando == objetivo->getBando()) {
        cout << "ADVERTENCIA: La oscuridad no distingue amigos de enemigos!!!" << endl;
        cout << this->nombre << " ataca a su aliado " << objetivo->getNombre() << "!!!!!" << endl;
    }
    else {
        cout << this->nombre << " Lanza un HECHIZO OSCURO contra: " << objetivo->getNombre() << "!!!!" <<endl;
    }

    objetivo-> recibirDanio(danioOscuro);

    cout << "Danio oscuro infligido: " << danioOscuro << " puntos!!!" << endl;
    cout << "============================================" << endl;

}



void HechiceroOscuro::realizarAccionIA(vector <Personaje*> aliados, vector<Personaje*> enemigos) {
    /*IA del Hechicero Osuro:
     * - 40% de probabilidad de usar AOE si hay 2+ enemigos vivos.
     * - 60% de probablidad de ataque normal al enemigo mas fuerte.
     * - Si solo queda 1 enemigo siempre usa ataque normal.
     * Estrategia: Caos calculado, la oscuridad es impredecible (es un borracho).
     */

    if (!this->isEstaVivo) {
        return; // Los muertos no actuan.
    }

    cout << endl << ">> " << this->nombre << " (Hechicero Oscuro) canaliza energia oscura...." << endl;
    pausar(2000);

    //Contar enemigos vivos para decidir si el AOE vale la pena:
    int enemigosVivos = 0 ;

    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i]->getIsEstaVivo() ) {
            enemigosVivos++;
        }
    }

    //Decidir aleatoriamente si usa AOE o ataque normal:
    bool usarAOE = false;

    if ( enemigosVivos >= 2 ) {
        //40% de probabilidad de usar AOE si hay multiples enemigos.
        int probabilidad = rand() % 100;
        usarAOE = (probabilidad < 40);
    }

    if (usarAOE) {
        //Usar el ataque AOE:

        cout << this-> nombre << " decide desatar el caos total!!!!!" << endl;
        realizarAccionAOE(aliados, enemigos);
    }
    else {
        //Ataque normal al enemigo con mayor ataque (la mayor amenaza):
        Personaje* objetivo = nullptr;
        int mayorAtaque  = -1;

        for (int i = 0; i < enemigos.size(); i++) {

            if (enemigos[ i ] ->getIsEstaVivo() && enemigos[i]->getAtaque() > mayorAtaque ) {
                mayorAtaque = enemigos[i]->getAtaque();
                objetivo = enemigos[i];
            }
        }

        if (objetivo != nullptr) {
            realizarAccion( objetivo);
        }
        else {
            cout << this-> nombre << " no encuentra objetivos vivos." << endl;
        }
    }
}

void HechiceroOscuro::realizarAccionAOE(vector<Personaje*> aliados, vector<Personaje*> enemigos) {
    /*Ataque de Area del hechicero Oscuro:
     *- Hace el 60% del danio normal a Todos los enemigos.
     *- Hace el un danio 30% del danio normal a Todos los aliados (excepto asi mismo).
     *- Cuesta el 15% de vida maxima (mas que el ataque normal).
     */

    if ( !this->isEstaVivo ) {
        cout << this-> nombre << " esta derrotado y no puede lanzar hechizos." << endl;
        return;
    }

    //Calcular el danio Base( 60% del danio Oscuro Normal):
    int danioBase = (int) ( ( calcularDanioOscuro() ) * 0.6 ) ;
    int danioAliados = this->calcularDanioColateral(danioBase) ; // 50% del danio base a aliados.

    //El costo del AOE es mayor: 15% de vida maxima:
    int costoVida = (this->getVidaMaxima() * 15)/100;

    cout << endl << "============================================" << endl;
    cout << "     EXPLOSION DE OSCURIDAD TOTAL" << endl;
    cout << "============================================" << endl;
    cout << this -> nombre << " canaliza un ritual de magia oscura!" << endl;
    cout << "Las sombras se expanden en todas direcciones!" << endl;
    cout << endl;
    cout << "Sacrificio de energia vital: -" << costoVida << " puntos de vida." << endl;

    pausar(1200);

    //Aplicar el costo de vida al hechicero.
    this->vida -= costoVida;
    cout << "Vida restante de " << this->nombre << ": " << ( this->vida <= 0 ?
        0: this->vida) << "/" << this->vidaMaxima << endl;

    //Verificamos si el hechicero muere por su propio poder:
    if (this-> vida <= 0) {
        this->vida = 0;
        this->isEstaVivo = false;
        cout << endl << "La Magia Oscura ha consumido a " << this->nombre << "!!!!" << endl;
        cout << this->nombre << " Ha sido derrotado por su propio poder!!!!" << endl;
        cout << "============================================" << endl;
        pausar(1200);
        return; //Muere antes de atacar.
    }
    pausar(1000);

    //Danio a Todos los enemigos:

    cout << endl << ">>> DANIO A ENEMIGOS <<<" << endl;
    int enemigosAfectados = 0;

    for (int i = 0; i < enemigos.size(); i++) {
        if ( enemigos[i] -> getIsEstaVivo() ) {
            cout << " -->" << enemigos[i]->getNombre() << " recibe la oscuridad!!!!" << endl;
            enemigos[i] -> recibirDanio(danioBase);
            enemigosAfectados++;
        }
    }

    if (enemigosAfectados == 0) {
        cout << " No hay enemigos vivos para afectar."<< endl;
    }

    pausar(800);

    //Danio a Todos los Aliados vivos (excepto asi mismo) :

    cout << endl << ">>> DANIO COLATERAL A ALIADOS <<<" << endl;
    cout << " ###### La Oscuridad no Distingue amigos de enemigos!!! ########" << endl;
    int aliadosAfectados = 0;

    for ( int i = 0; i < aliados.size(); i++) {
        if ( aliados[i]->getIsEstaVivo() && aliados[i] != this) {
            cout << " -->" << aliados[i]->getNombre() << " es alcanzado por las sombras!!!" << endl;
            aliados[i]->recibirDanio( danioAliados);
            aliadosAfectados++;
        }
    }

    if (aliadosAfectados == 0) {
        cout << " No hay aliados cercanos afectados." << endl;
    }

    cout << endl << "Danio infligido a enemigos: " << danioBase << " puntos cada uno." << endl;
    cout << "Danio colateral a aliados: " << danioAliados << " puntos cada uno." << endl;
    cout << "============================================" << endl;

    pausar(1200);
}

bool HechiceroOscuro::realizarAccionJugador( vector<Personaje*> aliados, vector<Personaje*> enemigos) {
    /*El Hechicero Oscuro puede:
     * 1. Ataque normal (un objetivo, puede ser enemigo o aliado).
     * 2. Ateque AOE (danio a Todos, incluyendo a Aliados).
     */

    if ( !this -> isEstaVivo) {
        cout << this->nombre  << " esta derrotado y no puede actuar." << endl;
        return false;
    }

    cout << endl << "========================================" << endl;
    cout << "  El Hechicero Oscuro puede elegir:" << endl;
    cout << "  1. Hechizo Oscuro (un objetivo - cuesta 10% vida)" << endl;
    cout << "  2. Explosion de Oscuridad - AOE (todos - cuesta 15% vida)" << endl;
    cout << "  0. Cancelar" << endl;
    cout << "========================================" << endl;
    cout << "Seleccione: ";

    int opcion;
    cin >> opcion;


    switch ( opcion) {
        case 1: {
            // Ataque normal - puede elegir enemigo O aliado.
            cout << endl << "La oscuridad no distingue amigos de enemigos..." << endl;
            cout << "1. Atacar a un enemigo." << endl;
            cout << "2. Atacar a un aliado (sacrificio oscuro)." << endl;
            cout << "0. Cancelar." << endl;
            cout << "Seleccione: ";

            int tipoObjetivo;
            cin >> tipoObjetivo;
            Personaje* objetivo = nullptr;
            if (tipoObjetivo == 1) {
                objetivo = seleccionarObjetivo(enemigos, "Seleccione un enemigo (Al que castigara el Destino"
                                                         "): ");
            }
            else if (tipoObjetivo == 2 ){
                cout << "ADEVERTENCIA: Vas a atacar a tu propio equipo!!!!" << endl;
                objetivo = seleccionarObjetivo( aliados, "Seleccione a "
                                                         "un aliado para atacar (Le pudo el trago): ");

            }
            else if (tipoObjetivo){
                cout << "Accion cancelada." << endl;
                return false;
            }
            else {
                cout << "Opcion invalida." << endl;
                return false;
            }

            if (objetivo != nullptr) {
                realizarAccion(objetivo);
                return true;
            }
            break;
        }
        case 2: {
            //Ataque AOE - afecta a todos.
            cout << "ADVERTENCIA: El ataque AOE danara a TODOS, " << endl;
            cout << "incluyendo a tus propios aliados!!!" << endl;
            cout << "Confirmar? ( 1 = Si, 0 = No): ";

            int confirmar;
            cin >> confirmar;

            if (confirmar == 1) {
                realizarAccionAOE( aliados, enemigos);
                return true;
            }
            else {
                cout << "Ataque AOE cancelado." << endl;
                return false;
            }

            break;
        }
        case 0: {
            cout << "Accion cancelada." << endl;
            return false;
            break;
        }

        default: {
            cout << "Opcion invalida." << endl;
            return false;
            break;
        }
    }


return false;

}

void HechiceroOscuro::mostrarInformacion( ) {
    // Muestra información detallada del Hechicero Oscuro

    cout << endl << "=======================================" << endl;
    cout << "#   Información del Hechicero Oscuro     #" << endl;
    cout << "==========================================" << endl;

    cout << "Nombre: " << this -> nombre << endl;
    cout << "Bando: " << this -> bando << endl;
    cout << "Nivel: " << this -> nivel << endl;
    cout << "Vida: " << this -> vida << "/" << this -> vidaMaxima << endl;
    cout << "Ataque: " << this -> ataque << endl;
    cout << "Poder Oscuro: " << this -> poderOscuro << endl;
    cout << "Defensa: " << this -> defensa << endl;
    cout << "Daño AoE: " << ( this -> porcentajeDanioAOE * 100 ) << "% del daño principal" << endl;
    cout << "Radio AoE: Afecta hasta " << this -> radioAOE << " objetivos adicionales" << endl;
    cout << "Estado: " << ( this -> isEstaVivo ? "Vivo" : "Derrotado" ) << endl;

    // Mostrar objetos equipados
    cout << endl << "Objetos equipados (" << this -> objetosEquipados.size( ) << "/2):" << endl;
    mostrarObjetosEquipados( );

    cout << endl << "ADVERTENCIA: Los hechizos oscuros dañan" << endl;
    cout << "tanto a enemigos como a aliados cercanos." << endl;
    cout << "==========================================" << endl;
}

// Getters

int HechiceroOscuro::getPoderOscuro( ) {
    return this -> poderOscuro;
}

double HechiceroOscuro::getPorcentajeDanioAOE( ) {
    return this -> porcentajeDanioAOE;
}

int HechiceroOscuro::getRadioAOE( ) {
    return this -> radioAOE;
}