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
    this -> porcentajeDanioAOE = 0.4;  // 40% del daño principal se aplica como AoE
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

    if( this -> bando == objetivo -> getBando( ) ) {
        cout << "¡Advertencia! Los hechizos oscuros dañan a todos, incluso aliados." << endl;
        cout << "Usa realizarAccionAOE( ) para ataques de area." << endl;
        return;
    }

    if( !objetivo -> getIsEstaVivo( ) ) {
        cout << "El objetivo ya esta derrotado." << endl;
        return;
    }

    // Calcular daño oscuro
    int danioOscuro = calcularDanioOscuro( );

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║  ⚫ MAGIA OSCURA DESATADA ⚫           ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " invoca un hechizo de oscuridad total!" << endl;
    cout << "La energía corrupta envuelve a " << objetivo -> getNombre( ) << "..." << endl;

    // Aplicar daño al objetivo principal
    objetivo -> recibirDanio( danioOscuro );

    cout << "¡Daño oscuro infligido: " << danioOscuro << " puntos!" << endl;
    cout << "═══════════════════════════════════════════" << endl;
}

void HechiceroOscuro::realizarAccionAOE( Personaje* objetivoPrincipal, vector<Personaje*> objetivosAdicionales ) {
    // Ataque de área que daña a múltiples objetivos (enemigos Y aliados)

    if( !this -> isEstaVivo ) {
        cout << this -> nombre << " esta derrotado y no puede lanzar hechizos." << endl;
        return;
    }

    if( !objetivoPrincipal -> getIsEstaVivo( ) ) {
        cout << "El objetivo principal ya esta derrotado." << endl;
        return;
    }

    // Calcular daño principal
    int danioPrincipal = calcularDanioOscuro( );
    int danioColateral = calcularDanioColateral( danioPrincipal );

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║  💀 EXPLOSIÓN DE OSCURIDAD TOTAL 💀    ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " libera un ritual de magia oscura!" << endl;
    cout << "¡Las sombras consumen todo a su alrededor!" << endl;
    cout << endl;

    // Daño al objetivo principal
    cout << "► OBJETIVO PRINCIPAL: " << objetivoPrincipal -> getNombre( ) << endl;
    objetivoPrincipal -> recibirDanio( danioPrincipal );
    cout << "   Daño infligido: " << danioPrincipal << " puntos" << endl;
    cout << endl;

    // Daño colateral a objetivos adicionales (pueden ser aliados o enemigos)
    cout << "► DAÑO COLATERAL (AoE):" << endl;
    int afectados = 0;

    for( int i = 0; i < objetivosAdicionales.size( ) && afectados < this -> radioAOE; i++ ) {
        Personaje* objetivo = objetivosAdicionales[ i ];

        if( objetivo -> getIsEstaVivo( ) && objetivo != objetivoPrincipal ) {
            cout << "   • " << objetivo -> getNombre( );

            if( objetivo -> getBando( ) == this -> bando ) {
                cout << " (¡ALIADO!) ";
            } else {
                cout << " (Enemigo) ";
            }

            objetivo -> recibirDanio( danioColateral );
            cout << "- " << danioColateral << " puntos de daño" << endl;
            afectados++;
        }
    }

    if( afectados == 0 ) {
        cout << "   No hay objetivos adicionales en rango." << endl;
    }

    cout << endl << "═══════════════════════════════════════════" << endl;
    cout << "¡El hechicero oscuro ha causado devastación!" << endl;
    cout << "Advertencia: La magia oscura no distingue entre" << endl;
    cout << "aliados y enemigos. ¡Úsala con precaución!" << endl;
    cout << "═══════════════════════════════════════════" << endl;
}

void HechiceroOscuro::mostrarInformacion( ) {
    // Muestra información detallada del Hechicero Oscuro

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║   Información del Hechicero Oscuro     ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

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

    cout << endl << "⚠ ADVERTENCIA: Los hechizos oscuros dañan" << endl;
    cout << "tanto a enemigos como a aliados cercanos." << endl;
    cout << "════════════════════════════════════════════" << endl;
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