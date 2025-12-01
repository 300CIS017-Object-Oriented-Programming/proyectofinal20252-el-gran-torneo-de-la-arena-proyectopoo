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

    if (aliado-> getEscudoProtector() ) {
        cout << aliado->getNombre() << " ya tiene un escudo protector activo." << endl;
        return;
    }

    cout << endl << "╔════════════════════════════════════════╗" << endl;
    cout << "║   ESCUDO PROTECTOR                ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << this -> nombre << " se interpone para proteger a "
         << aliado -> getNombre( ) << "!!!!" << endl;

    pausar(1500); //Para que el usuario pueda leer el texto.

    //Activar el escudo sagrado en el aliado:

    aliado->setEscudoProtector(true);

    cout << "Una barrera de luz divina envueve a " << aliado->getNombre() << "!!!" << endl;
    cout << "El proximo ataque sera completamente bloqueado!!!" << endl;
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

    pausar(1500); //Para que el usuario pueda leer el texto.

    //Verificar si ya tiene buff de defensa (el aliado o objetivo (puede ser el mismo):
    if ( aliado ->tieneBuffDefensa() ) {
        cout << aliado->getNombre() << " ya tiene un buff de defensa activo!!!!" << endl;
        cout << "Debe de esperar a que termine." << endl;
        cout << "═══════════════════════════════════════════" << endl;
        return;
    }



    // Aumentar defensa del aliado

    int aumentoDefensa = 15;
    int duracionTurnos = 2;
    int defensaAnterior = aliado -> getDefensa( );

    //Usar el sistema general de buffs de defensa:
    aliado->aplicarBuffDefensa( aumentoDefensa, duracionTurnos);

    cout << "Una aura dorada envuelve a " << aliado -> getNombre( ) << "!" << endl;
    cout << "Defensa aumentada: +" << aumentoDefensa << " puntos" << endl;
    cout << "Defensa: " << defensaAnterior << " → " << aliado -> getDefensa( ) << endl;
    cout << "═══════════════════════════════════════════" << endl;
    pausar(1200); //Para que el usuario pueda leer el texto.
}

void Paladin::realizarAccionIA(vector<Personaje*> aliados, vector<Personaje*> enemigos) {

    /*IA del Paladin: ataca al enemigos, pero si un aliado esta muy herido, lo protege
     * Estrategia: Balance entre ataque y proteccion con variabilidad.
     * - Si un aliado tiene menos del 30% de vida y no tiene escudo, tiene 70% de probabilidad de protegerlo.
     * - Si un aliado tiene menos del 50% de vida, tiene 60% de probabilidad de usar bendicion.
     * - Si no, ataca al enemigo con mas vida (o aleatoriamente si hay varios).
     */

    if (!this->isEstaVivo) {
        return; // los muertos no actuan;
    }

    cout << endl << ">> " << this->nombre << " (Paladin) evalua el campo de batalla..." << endl;
    pausar(2000);  //  Pausa para crear tensión

    // Primero verificamos si algun aliado (o el mismo) necesita escudo (vida < 30% y sin escudo):
    for (int i = 0; i < aliados.size(); i++) {
        if (aliados[i]->getIsEstaVivo()) {
            double porcentajeVida = (double)aliados[i]->getVida() / aliados[i]->getVidaMaxima();

            if (porcentajeVida < 0.30 && !aliados[i]->getEscudoProtector()) {
                // 70% de probabilidad de proteger en situación crítica
                int probabilidad = rand() % 100;
                if (probabilidad < 70) {
                    if (aliados[i] == this) {
                        cout << this->nombre << " se prepara para protegerse a si mismo!!!" << endl;
                    } else {
                        cout << this->nombre << " decide proteger a su aliado en peligro!!!" << endl;
                    }
                    pausar(1500);
                    protegerAliado(aliados[i]);
                    return;
                } else {
                    cout << this->nombre << " duda por un momento..." << endl;
                    pausar(1500);
                    cout << "Decide mantener la presion ofensiva en su lugar!" << endl;
                    pausar(1500);
                    // Continua para atacar
                    break;
                }
            }
        }
    }

    // Si no hay aliados en peligro Critico, verificar si alguien necesita bendicion (vida < 50%):
    for (int i = 0; i < aliados.size(); i++) {
        if (aliados[i]->getIsEstaVivo()) {
            double porcentajeVida = (double)aliados[i]->getVida() / aliados[i]->getVidaMaxima();
            if (porcentajeVida < 0.5) {
                // 60% de probabilidad de bendecir
                int probabilidad = rand() % 100;
                if (probabilidad < 60) {
                    if (aliados[i] == this) {
                        cout << this->nombre << " decide bendecirse a si mismo!!!!!" << endl;
                    } else {
                        cout << this->nombre << " decide bendecir a su aliado herido!!!!" << endl;
                    }
                    pausar(1500);
                    bendiccionDivina(aliados[i]);
                    return;
                } else {
                    cout << this->nombre << " considera curar a sus aliados..." << endl;
                    pausar(1500);
                    cout << "Pero prefiere seguir atacando!" << endl;
                    pausar(1500);
                    // Continúa para atacar
                    break;
                }
            }
        }
    }

    // Si no hay aliados que necesiten ayuda, atacar a un enemigo
    vector<Personaje*> enemigosVivos;

    // Recopilar enemigos vivos
    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i]->getIsEstaVivo()) {
            enemigosVivos.push_back(enemigos[i]);
        }
    }

    if (!enemigosVivos.empty()) {
        // 50% de probabilidad de atacar al de mas vida, 50% a uno aleatorio
        Personaje* objetivo = nullptr;
        int probabilidad = rand() % 100;

        if (probabilidad < 50) {
            // Atacar al enemigo con más vida
            int mayorVida = -1;
            for (int i = 0; i < enemigosVivos.size(); i++) {
                if (enemigosVivos[i]->getVida() > mayorVida) {
                    mayorVida = enemigosVivos[i]->getVida();
                    objetivo = enemigosVivos[i];
                }
            }
            cout << this->nombre << " se enfoca en el enemigo mas fuerte!" << endl;
            pausar(1500);
        } else {
            // Atacar a un enemigo aleatorio
            int indiceAleatorio = rand() % enemigosVivos.size();
            objetivo = enemigosVivos[indiceAleatorio];
            cout << this->nombre << " elige un objetivo estrategico!" << endl;
            pausar(1500);
        }

        realizarAccion(objetivo);
    } else {
        cout << this->nombre << " no encuentra objetivos." << endl;
        pausar(1500);
    }
}

bool Paladin::realizarAccionJugador(vector<Personaje*> aliados, vector<Personaje*> enemigos) {
      /*El paladin puede atacar enemigos O proteger/bendecir aliados
       * El jugador elige que hacer.
       */

       if (!this-> isEstaVivo) {
           cout << this->nombre << " esta derrotado y no puede actuar." << endl;
           return false;
       }

    cout << endl << "========================================" << endl;
    cout << "  El Paladin puede realizar diferentes acciones:" << endl;
    cout << "  1. Atacar a un enemigo (Justicia Divina)" << endl;
    cout << "  2. Otorgar Escudo Protector a un aliado (bloquea 1 ataque)" << endl;
    cout << "  3. Bendicion Divina a un aliado (+15 defensa por dos turnos)" << endl;
    cout << "  0. Cancelar" << endl;
    cout << "========================================" << endl;
    cout << "Seleccione: ";

    int opcion;
    cin >> opcion;

    Personaje * objetivo = nullptr;

    switch ( opcion ) {
        case 1: {
            objetivo = seleccionarObjetivo(enemigos, "Seleccione un enemigo "
                                                     "para atacar (No dio el Diezmo) : ");
            if (objetivo != nullptr) {
                realizarAccion(objetivo);
                return true;
            }

            break;
        }
        case 2: {
            objetivo = seleccionarObjetivo(aliados, "Seleccione un aliado"
                                                    " a proteger (Tiene que ser un creyente con tarjeta Premium): ");
            if (objetivo != nullptr) {
                protegerAliado(objetivo);
                return true;
            }
            break;
        }
        case 3: {
            objetivo = seleccionarObjetivo( aliados, "Seleccione un "
                                                     "aliado para bendecir (Si no viene a "
                                                     "misa los domingos, pailas): ");
            if (objetivo != nullptr) {
                bendiccionDivina(objetivo);
                return true;
            }
            break;
        }
        case 0: {
            cout << "Accion cancelada. (No pagaron)" << endl;
            return false;
            break;

        }
        default: {
            cout << "Opcion invalida. " << endl;
            return false;
            break;

        }
    }

    return false;

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
