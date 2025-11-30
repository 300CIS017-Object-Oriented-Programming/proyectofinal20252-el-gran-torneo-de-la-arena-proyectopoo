//
// Paladín - Implementación
// Especializado en ataques moderados con defensa elevada y protección
//

#include "Paladin.h"

// Constructores

Paladin::Paladin( ) : Personaje( ) {
    // Constructor por defecto
    this -> rol = "Paladin";
    this -> poderDivino = 25;
    this -> probabilidadEscudoSagrado = 0.30;  // 30% de probabilidad de bloqueo total
    this -> escudoActivado = false;
    this -> contadorTurnos = 0;

    // Stats balanceados: vida alta, defensa muy alta, ataque moderado
    this -> vida = 140;
    this -> vidaMaxima = 140;
    this -> ataque = 25;
    this -> defensa = 25;  // Defensa elevada característica del Paladín
}

Paladin::Paladin( string nombre, string bando, int nivel, int vida, int ataque, int defensa )
    : Personaje( nombre, "Paladin", bando, nivel, vida, ataque, defensa ) {
    // Constructor parametrizado
    this -> poderDivino = 25;
    this -> probabilidadEscudoSagrado = 0.30;
    this -> escudoActivado = false;
    this -> contadorTurnos = 0;
}

// Métodos auxiliares privados

int Paladin::calcularDanioDivino( ) {
    // Calcula el daño divino (moderado pero constante)
    int variacion = ( rand( ) % 11 ) - 5;  // Rango: -5 a +5 (poca variación)
    int danio = this -> ataque + this -> poderDivino + variacion;

    if( danio < 0 ) {
        danio = 0;
    }

    return danio;
}

bool Paladin::activarEscudoSagrado( ) {
    // Verifica si se activa el escudo sagrado (probabilidad de bloqueo)
    double random = ( double ) rand( ) / RAND_MAX;
    return random < this -> probabilidadEscudoSagrado;
}

// Métodos sobrescritos

void Paladin::realizarAccion( Personaje* objetivo ) {
    // Ataque del Paladín con poder divino

    if( !this -> isEstaVivo ) {
        cout << this -> nombre << " esta derrotado y no puede atacar." << endl;
        return;
    }

    if( this -> bando == objetivo -> getBando( ) ) {
        cout << "No puede atacar a un aliado. ¡Los paladines protegen a sus compañeros!" << endl;
        return;
    }

    if( !objetivo -> getIsEstaVivo( ) ) {
        cout << "El objetivo ya esta derrotado." << endl;
        return;
    }

    // Calcular daño divino
    int danioDivino = calcularDanioDivino( );

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║    JUSTICIA DIVINA                   ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " invoca el poder de la luz sagrada!" << endl;
    cout << "Un destello divino ilumina su arma mientras ataca a "
         << objetivo -> getNombre( ) << "!" << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.

    // Aplicar daño
    objetivo -> recibirDanio( danioDivino );

    cout << "¡Golpe divino! Daño infligido: " << danioDivino << " puntos" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.

    // Incrementar contador de turnos
    this -> contadorTurnos++;
}

void Paladin::protegerAliado( Personaje* aliado ) {
    // Habilidad especial: Proteger a un aliado

    if( !this -> isEstaVivo ) {
        cout << this -> nombre << " esta derrotado y no puede proteger aliados." << endl;
        return;
    }

    if( aliado == nullptr ) {
        cout << "Error: No hay aliado especificado." << endl;
        return;
    }

    if( this -> bando != aliado -> getBando( ) ) {
        cout << "Solo puedes proteger a aliados de tu mismo bando." << endl;
        return;
    }

    if( !aliado -> getIsEstaVivo( ) ) {
        cout << aliado -> getNombre( ) << " esta derrotado y no puede ser protegido." << endl;
        return;
    }

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║   ESCUDO PROTECTOR                ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " se interpone para proteger a "
         << aliado -> getNombre( ) << "!" << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.

    // Verificar si el escudo sagrado se activa
    if( activarEscudoSagrado( ) ) {
        this -> escudoActivado = true;
        cout << "¡El ESCUDO SAGRADO se activa!" << endl;
        cout << "Una barrera de luz divina envuelve al Paladín." << endl;
        cout << "El próximo ataque será completamente bloqueado!" << endl;
    } else {
        cout << this -> nombre << " adopta una postura defensiva." << endl;
        cout << aliado -> getNombre( ) << " recibe un bonus temporal de +10 defensa." << endl;

        // Aumentar defensa del aliado temporalmente
        int defensaActual = aliado -> getDefensa( );
        aliado -> setDefensa( defensaActual + 10 );
    }

    cout << "═══════════════════════════════════════════" << endl;
    pausar(1200); //Para que el usuario pueda leer el texto.
}

void Paladin::bendiccionDivina( Personaje* aliado ) {
    // Habilidad especial: Bendición que aumenta defensa del aliado

    if( !this -> isEstaVivo ) {
        cout << this -> nombre << " esta derrotado y no puede otorgar bendiciones." << endl;
        return;
    }

    if( aliado == nullptr ) {
        cout << "Error: No hay aliado especificado." << endl;
        return;
    }

    if( this -> bando != aliado -> getBando( ) ) {
        cout << "Solo puedes bendecir a aliados de tu mismo bando." << endl;
        return;
    }

    if( !aliado -> getIsEstaVivo( ) ) {
        cout << aliado -> getNombre( ) << " esta derrotado y no puede ser bendecido." << endl;
        return;
    }

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║   BENDICIÓN DIVINA                 ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " canaliza el poder sagrado hacia "
         << aliado -> getNombre( ) << "!" << endl;

    pausar(1200); //Para que el usuario pueda leer el texto.

    // Aumentar defensa del aliado
    int defensaAnterior = aliado -> getDefensa( );
    int aumentoDefensa = 15;
    aliado -> setDefensa( defensaAnterior + aumentoDefensa );

    cout << "Una aura dorada envuelve a " << aliado -> getNombre( ) << "!" << endl;
    cout << "Defensa aumentada: +" << aumentoDefensa << " puntos" << endl;
    cout << "Defensa: " << defensaAnterior << " → " << aliado -> getDefensa( ) << endl;
    cout << "═══════════════════════════════════════════" << endl;
    pausar(1200); //Para que el usuario pueda leer el texto.
}

void Paladin::realizarAccionIA( vector<Personaje*> aliados, vector<Personaje*> enemigos) {
    /*IA del Paladin: ataca al enemigos, pero si un aliado esta muy herido, lo protege
     * Estrategia: Balance entre ataque y proteccion.
     */

    if (!this->isEstaVivo) {
        return; // los muertos no actuan;
    }

    cout << endl << ">> " << this->nombre << " (Paladin) evalua el campo de batalla..." << endl;
    pausar(2000);  //  Pausa para crear tensión

    //Primero verificamos si algun aliado necesita proteccion (vida < 30%):
    Personaje * aliadoEnPeligro = nullptr;

    for ( int i = 0 ; i < aliados.size(); i++) {
        //Nota el "!= this" es para que no se seleccione a si mismo, ya que el hace parte del equipo.
        if (aliados[i] -> getIsEstaVivo() && aliados[i] != this) {
            double porcentajeVida = (double) aliados[i] ->getVida() / aliados[i]->getVidaMaxima();
            if (porcentajeVida < 0.30) {
                aliadoEnPeligro = aliados[i];
                break;
            }
        }
    }

    //Si hay aliado en peligro, usar bencion divina:
    if (aliadoEnPeligro != nullptr) {
        cout << this->nombre << " decide proteger a su aliado herido!!!!" << endl;
        bendiccionDivina(aliadoEnPeligro);
        return;
    }

    //Si no hay aliados en peligro, atacar al enemigo con mas vida:
    Personaje * objetivo = nullptr;
    int mayorVida = -1;

    for (int i = 0; i < enemigos.size() ; i++) {
        if (enemigos[i]->getIsEstaVivo( ) && enemigos[ i ] -> getVida() > mayorVida) {
            mayorVida = enemigos[i]->getVida();
            objetivo = enemigos[i];
        }
    }

    if (objetivo != nullptr) {
        realizarAccion(objetivo); //Reutilizamos el metodo;
    }
    else {
        cout << this->nombre << " no encuentra objetivos." << endl;
    }

}

void Paladin::mostrarInformacion( ) {
    // Muestra información detallada del Paladín

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║     Informacion del Paladín            ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    cout << "Nombre: " << this -> nombre << endl;
    cout << "Bando: " << this -> bando << endl;
    cout << "Nivel: " << this -> nivel << endl;
    cout << "Vida: " << this -> vida << "/" << this -> vidaMaxima << endl;
    cout << "Ataque: " << this -> ataque << " (Moderado)" << endl;
    cout << "Poder Divino: " << this -> poderDivino << endl;
    cout << "Defensa: " << this -> defensa << " (Elevada)" << endl;
    cout << "Escudo Sagrado: " << ( this -> probabilidadEscudoSagrado * 100 )
         << "% de bloqueo total" << endl;
    cout << "Estado del Escudo: " << ( this -> escudoActivado ? "Activado" : "Desactivado" ) << endl;
    cout << "Estado: " << ( this -> isEstaVivo ? "Vivo" : "Derrotado" ) << endl;

    // Mostrar objetos equipados
    cout << endl << "Objetos equipados (" << this -> objetosEquipados.size( ) << "/2):" << endl;
    mostrarObjetosEquipados( );

    cout << endl << "️ Habilidades Especiales:" << endl;
    cout << "  • Proteger Aliado: Intercepta ataques" << endl;
    cout << "  • Bendición Divina: Aumenta defensa aliada" << endl;
    cout << "  • Escudo Sagrado: Probabilidad de bloqueo total" << endl;
    cout << "════════════════════════════════════════════" << endl;
}

// Getters

int Paladin::getPoderDivino( ) {
    return this -> poderDivino;
}

double Paladin::getProbabilidadEscudoSagrado( ) {
    return this -> probabilidadEscudoSagrado;
}

bool Paladin::getEscudoActivado( ) {
    return this -> escudoActivado;
}
