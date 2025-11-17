//
// Created by felip on 17/11/2025.
//

#include "Guerrero.h"

// Constructores y destrucotres:


Guerrero:: Guerrero(): Personaje() //Constructor por defecto, llama al constructor de Personaje.
{
    this->rol = "Guerrero";
    this->probabilidadCritico = 0.25; // 25% de probabilidad de critico.
    // Los guerreros tienen mas vida y defensa.
    this-> vida = 150;
    this-> vidaMaxima = 150;
    this-> defensa = 15;
}

Guerrero::Guerrero( string nombre, string bando, int nivel, int vida, int ataque, int defensa)
    : Personaje(nombre, "Guerrero" , bando, nivel, vida, ataque, defensa)// Reutilizo el constructor
// parametrizado de Personaje.
{
    // inicializo con valores espcificos:
    this->probabilidadCritico = 0.25; // 25% de probabilidad de hacer critico.

}

bool Guerrero:: isEsCritico() {
    // Genera un numero aleatorio entre 0 y 1.0.
    // Si es menor a probabilidad Critico es un golpe critico.
    double random;

    random = (double)rand()/ RAND_MAX;
    // RAND_MAX: constante (macro) de la librería estándar.
    // (double)rand():  convierte el resultado de rand() a double, ya que rand() devuelve un int.

    return random < this->probabilidadCritico;
}

int Guerrero:: calcularDanioCritico( int danioBase) {
    // Los criticos hacen el doble de daño:
    return danioBase * 2;
}

// Metodos sobre escritos del Personaje:

void Guerrero::realizarAccion(Personaje* objetivo) {
    // El Guerrero con posibilidad de critico


    if (!this->isEstaVivo)// los muertos no atacan.
        {
        cout << this->nombre << " esta derrotado y no puede atacar." << endl;
        return;
    }

    // Verificamos que sea enemigo el objetivo:
    if (this->bando == objetivo->getBando() ) {
        cout << "No puede atacar a un aliado. ¡¡¡¡¡¡Solo ataca Enemigos!!!!!" << endl;
        return;
    }

    if (!objetivo->getIsEstaVivo())//Si no esta vivo para que ataca al chico.
        {
        cout << "El objetivo ya esta derrotado." << endl;
        return;
    }

    // Cacular el daño base del guerrero:
    int danioBase = this->ataque; // se declara aqui ya que si no pasa los condicionales de arriba
    // no hay necesidad de realizar ninguna declaracion.

    // Verificamos si es un golpe critico
    if ( isEsCritico() ) {
        int danioCritico = calcularDanioCritico(danioBase);
        cout << "¡¡¡¡GOLPE CRITICO!!!!" << endl;
        cout << this->nombre << " ataca a " << objetivo->getNombre()
        << " con un golpe devastador!" << endl;
        objetivo->recibirDanio(danioCritico);
    }
    else // Si no lo es realizamos un ataque normal:
        {
        cout << this-> nombre << " ataca a " << objetivo->getNombre() << "!!!!!" <<endl;
        objetivo->recibirDanio(danioBase);
    }

}

void Guerrero:: mostrarInformacion() {
    // Muestar informacion detallada del guerrero:
    cout << endl << "======== Informacion del Guerrero ========" << endl;

    cout << "Nombre: " << this->nombre << endl;
    cout << "Bando: " << this->bando << endl;
    cout << "Nivel: " << this->nivel << endl;
    cout << "Vida: " << this-> vida << endl;
    cout << "Ataque: "<< this -> ataque << endl;
    cout << "Defensa: " << this-> defensa << endl;
    cout << "Probabilidad Critico: " << (this-> probabilidadCritico * 100) << "%" << endl;
    cout << "Estado: " << (this->isEstaVivo ? "Vivo" : "Derrotado (Con su creador)") << endl; //
    // Se coloca un condicional en el cout de arriba para que de el estado real del Guerrero.
    cout << "Objetos equipados: " << objetosEquipados.size() << "/2" << endl;

    // -> Pendiente: Cuando ya este implementado los objetos magicos y objetos asignados, seria bueno que
    // podamos mostrar cuales objetos tiene equipado por sus nombres.

    cout << "==========================================" << endl;
}