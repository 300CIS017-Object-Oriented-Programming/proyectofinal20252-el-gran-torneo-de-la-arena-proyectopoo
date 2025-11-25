cmake_minimum_required(VERSION 4.0)
project(proyectofinal20252_el_gran_torneo_de_la_arena_proyectopoo)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyectofinal20252_el_gran_torneo_de_la_arena_proyectopoo src/main.cpp
        src/Personajes/Personaje.cpp
        src/Personajes/Personaje.h
        src/Personajes/Guerrero.cpp
        src/Personajes/Guerrero.h
        src/Personajes/Mago.cpp
        src/Personajes/Mago.h
        src/Personajes/Sanador.cpp
        src/Personajes/Sanador.h
        src/Guild/Guild.cpp
        src/Guild/Guild.h
        src/Torneo/Torneo.cpp
        src/Torneo/Torneo.h
        src/Inventario/ObjetoAsignado.h
        src/Inventario/ObjetoAsignado.cpp
        src/Inventario/Inventario.h
        src/Inventario/Inventario.cpp
        src/Objetos/ObjetoMagico.h
        src/Objetos/ObjetoMagico.cpp
        src/Objetos/PocionVida.h
        src/Objetos/PocionVida.cpp
        src/Objetos/CaballaLegendaria.h
        src/Objetos/CaballaLegendaria.cpp
        src/Objetos/PactoSangriento.h
        src/Objetos/PactoSangriento.cpp
        src/Personajes/HechiceroOscuro.cpp
        src/Personajes/HechiceroOscuro.h
        src/Personajes/Paladin.h
        src/Personajes/Paladin.cpp)
