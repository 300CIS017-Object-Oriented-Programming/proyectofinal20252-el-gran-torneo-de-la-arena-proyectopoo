//
// Created by felip on 13/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HEROE_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HEROE_H

//Librerias:
#include <iostream>
#include <vector>
#include <iomanip>

//Otras Clase:
#include "ObjetoMagico.h"

//Usings

using std::cout;
using std::vector;
using std::cin;
using std::string;
using std::endl;
using std:: setprecision;
using std:: fixed;




class Heroe {

protected:
    string nombre;
    string rol;
    int nivel;
    int vida;
    int vidaMaxima; //Es el valor de vida maxima con la que empieza el personaje.
    // Se inicializa al igual que la vida.
    int ataque;
    int defensa;
    vector <ObjetoMagico*> objetosEquipados;
    bool isEstaVivo;
public:
    Heroe(string nombre, string rol, int nivel, int vida, int ataque, int defensa);

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTOPOO_HEROE_H