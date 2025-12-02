# Manual Técnico - El Gran Torneo de Lyrenhold

Sistema de gestión de torneos de guilds con combate por turnos.

Proyecto Final - Programación Orientada a Objetos 2025-2

---

## Descripción General

Este proyecto simula un torneo donde diferentes guilds (gremios) compiten entre sí. El jugador controla una guild de héroes que pueden combatir contra guilds enemigas en una arena por turnos. Cada héroe tiene un rol específico (Guerrero, Mago, Sanador, Paladín o Hechicero Oscuro) que determina cómo actúa en combate.

El sistema incluye:
- Gestión de personajes (crear, consultar, retirar)
- Inventario de objetos mágicos
- Sistema de combate por turnos
- Guardado y carga de datos en JSON

---

## Estructura del Proyecto

```
src/
├── main.cpp                    Punto de entrada del programa
├── Torneo/
│   ├── Torneo.h               Controlador principal
│   └── Torneo.cpp
├── Guild/
│   ├── Guild.h                Gestiona los personajes de un equipo
│   └── Guild.cpp
├── Arena/
│   ├── Arena.h                Sistema de combate por turnos
│   └── Arena.cpp
├── Personajes/
│   ├── Personaje.h            Clase base de todos los personajes
│   ├── Personaje.cpp
│   ├── Guerrero.h/cpp         Especializado en ataques físicos
│   ├── Mago.h/cpp             Especializado en magia
│   ├── Sanador.h/cpp          Especializado en curación
│   ├── Paladin.h/cpp          Defensa elevada y protección
│   └── HechiceroOscuro.h/cpp  Magia oscura con daño de área
├── Inventario/
│   ├── Inventario.h           Gestiona objetos mágicos del torneo
│   ├── Inventario.cpp
│   ├── ObjetoAsignado.h       Representa un objeto equipado
│   └── ObjetoAsignado.cpp
├── Objetos/
│   ├── ObjetoMagico.h         Clase base de objetos mágicos
│   ├── ObjetoMagico.cpp
│   ├── PocionVida.h/cpp       Restaura vida
│   ├── AmuletoFuria.h/cpp     Aumenta ataque temporalmente
│   ├── EscudoBendito.h/cpp    Aumenta defensa temporalmente
│   ├── PactoSangriento.h/cpp  Sacrifica vida por poder
│   ├── CaballaLegendaria.h/cpp 50% matar enemigo / 50% morir
│   └── Revivir.h/cpp          Resucita aliados caídos
└── ArchivosJson/
    └── heroes.json            Archivo de guardado
```

---

## Clases Principales

### Torneo

Es el controlador principal del sistema. Se encarga de inicializar todo (guilds, inventario, arena) y de manejar los menús.

**Atributos importantes:**
- `guildJugador`: Puntero a la guild que controla el jugador.
- `guildsEnemigas`: Vector con las guilds rivales.
- `inventario`: Puntero al inventario global de objetos.
- `arena`: Puntero al sistema de combate.

**Menú principal:**
```
========================================
     Gran Torneo de la Arena de Lyrenhold
========================================
1) Gestionar Guild.
2) Gestionar inventario.
3) Iniciar Arena (combates).
4) Ver Guilds enemigas.
5) Guardar heroes de la Guild en JSON.
6) Cargar heroes desde JSON.
0) Salir del torneo.
========================================
```

### Guild

Gestiona una colección de personajes usando `unordered_map`. La clave del mapa es el nombre del personaje, y el valor es un puntero al objeto Personaje.

**Por qué usamos unordered_map:**
- Búsqueda rápida por nombre.
- Evita duplicados automáticamente (no puede haber dos personajes con el mismo nombre).

**Métodos principales:**
- `cargarPersonajesIniciales()`: Crea 5 héroes base al iniciar.
- `agregarPersonaje()`: Añade un nuevo personaje verificando que no exista.
- `retirarPersonaje()`: Elimina un personaje y libera su memoria.
- `buscarPersonaje()`: Retorna el puntero al personaje o nullptr si no existe.
- `getPersonajesVivos()`: Retorna un vector solo con los personajes vivos.
- `guardarHeroesEnJSON()`: Guarda los héroes en un archivo.
- `cargarHeroesDesdeJSON()`: Carga héroes desde un archivo.

### Arena

Controla el sistema de combate por turnos. Recibe los personajes de ambos equipos y alterna sus turnos hasta que un equipo sea derrotado.

**Flujo del combate:**
1. `iniciarCombate()`: Recibe los héroes y enemigos, muestra los equipos.
2. `ejecutarTurno()`: Primero actúan todos los héroes, luego todos los enemigos.
3. `verificarFinCombate()`: Verifica si algún equipo perdió.
4. `mostrarResumenFinal()`: Muestra quién ganó y las estadísticas.
5. `procesarObjetosPostCombate()`: Retira los objetos usados.

**IA de los enemigos:**
Cada tipo de personaje tiene su propia lógica de IA en el método `realizarAccionIA()`:
- Guerrero: Ataca al enemigo con menos vida.
- Mago: Ataca al enemigo con mayor defensa (aprovecha que ignora defensa).
- Sanador: Cura al aliado más herido.
- Paladín: Protege aliados en peligro o ataca.
- Hechicero Oscuro: 40% usa AOE si hay 2+ enemigos, sino ataca al más fuerte.

### Personaje (Clase Base)

Es la clase abstracta de la que heredan todos los tipos de personajes. Define los atributos y métodos comunes.

**Atributos protegidos:**
- `nombre`, `rol`, `bando`: Identificación del personaje.
- `nivel`, `vida`, `vidaMaxima`, `ataque`, `defensa`: Estadísticas de combate.
- `isEstaVivo`: Si el personaje puede actuar.
- `isTieneEscudoProtector`: Si tiene un escudo que bloquea el próximo ataque.
- `objetosEquipados`: Vector de punteros a ObjetoAsignado (máximo 2).
- Atributos de buffs temporales para efectos de habilidades.

**Métodos abstractos (las clases hijas los implementan):**
- `realizarAccion()`: La acción principal del personaje.
- `realizarAccionIA()`: Cómo actúa cuando es controlado por la IA.
- `realizarAccionJugador()`: Cómo actúa cuando es controlado por el jugador.
- `mostrarInformacion()`: Muestra los detalles del personaje.

**Método recibirDanio():**
```cpp
void Personaje::recibirDanio(int danio) {
    // Si tiene escudo, bloquea completamente el ataque
    if (this->isTieneEscudoProtector) {
        cout << "¡¡¡ESCUDO PROTECTOR ACTIVADO!!!" << endl;
        this->isTieneEscudoProtector = false;
        return;
    }
    
    // Calcula daño real considerando defensa
    int danioReal = danio - this->defensa;
    if (danioReal < 0) {
        danioReal = 0;
    }
    
    this->vida -= danioReal;
    
    // Verifica si murió
    if (this->vida <= 0) {
        this->vida = 0;
        this->isEstaVivo = false;
    }
}
```

### Clases Hijas de Personaje

**Guerrero:**
- Tiene 25% de probabilidad de golpe crítico (doble daño).
- Alta vida y defensa.
- IA: Ataca al enemigo con menos vida para eliminarlo rápido.

**Mago:**
- Sus ataques ignoran el 50% de la defensa enemiga.
- Daño variable con poder mágico adicional.
- Poca defensa pero mucho daño.
- IA: Ataca al enemigo con mayor defensa.

**Sanador:**
- No ataca, solo cura aliados.
- La curación tiene efectividad variable (puede fallar).
- IA: Cura al aliado más herido.

**Paladín:**
- Puede atacar, proteger aliados o dar bendición de defensa.
- `protegerAliado()`: 50% de éxito para dar escudo que bloquea 1 ataque.
- `bendiccionDivina()`: +15 defensa por 2 turnos.
- IA: Si un aliado tiene menos del 30% de vida, intenta protegerlo.

**Hechicero Oscuro:**
- Ataque normal cuesta 10% de su vida máxima.
- Puede atacar a aliados o enemigos.
- `realizarAccionAOE()`: Ataque de área que daña a todos, cuesta 15% de vida.
- IA: 40% de usar AOE si hay 2+ enemigos.

### Inventario

Gestiona el catálogo de objetos mágicos del torneo usando `unordered_map`. La clave es el nombre del objeto.

**Objetos iniciales:**
- 5 Pociones de Vida
- 3 Amuletos de Furia
- 3 Escudos Benditos
- 2 Pactos Sangrientos
- 1 Caballa Legendaria
- 2 Pociones de Resurrección

**Menú de inventario:**
```
=======$ GESTION DE INVENTARIO $========
Stock total: X objetos.
1) Crear objeto magico.
2) Listar objetos disponibles.
3) Consultar objeto especifico.
4) Actualizar stock de objeto.
5) Eliminar objeto (si stock = 0).
========================================
6) Asignar objeto a heroe.
7) Retirar objeto de heroe.
8) Ver objetos equipados por heroes.
0) Volver al menu principal.
========================================
```

### ObjetoMagico (Clase Base)

Clase abstracta para todos los objetos mágicos. Define el stock y los métodos que deben implementar las clases hijas.

**Métodos importantes:**
- `aplicarEfecto()`: Método abstracto que define qué hace el objeto.
- `getTurnosEfecto()`: Retorna cuántos turnos dura el efecto (0 si es instantáneo).
- `revertirEfecto()`: Revierte el efecto cuando expira (para objetos temporales).
- `incrementarStock()` / `decrementarStock()`: Maneja el stock disponible.

### ObjetoAsignado

Representa una instancia de un objeto equipado por un personaje. Guarda el puntero al tipo de objeto y si ya fue usado.

**Atributos importantes:**
- `tipoObjeto`: Puntero al ObjetoMagico del catálogo.
- `usado`: Si el objeto ya fue consumido.
- `personajeAfectado`: Para efectos temporales, quién recibió el efecto.
- `turnosRestantes`: Turnos que quedan del efecto.
- `ultimoAumento`: Guarda cuánto aumentó para poder revertirlo exactamente.

**Patrón de diseño:**
Esto funciona similar al patrón Flyweight. El catálogo (Inventario) tiene los tipos de objetos con su stock. Cuando se asigna un objeto a un personaje, se crea un ObjetoAsignado que apunta al tipo pero representa una instancia específica.

### Clases Hijas de ObjetoMagico

**PocionVida:**
- Cura entre 20 y 40 puntos de vida.
- Efecto instantáneo.

**AmuletoFuria:**
- Aumenta ataque entre 5 y 10 puntos.
- Dura 2 turnos, luego se revierte.

**EscudoBendito:**
- Aumenta defensa entre 10 y 20 puntos.
- Dura 1 turno, luego se revierte.

**PactoSangriento:**
- Sacrifica 30% de vida máxima.
- Aumenta ataque entre 25 y 40 puntos (permanente).
- No puede matarte, mínimo quedas con 1 de vida.

**CaballaLegendaria:**
- 50% de matar al enemigo seleccionado instantáneamente.
- 50% de morir tú.
- Permite seleccionar el objetivo.

**Revivir:**
- Permite seleccionar un aliado muerto.
- Lo revive con 50% de su vida máxima.

---

## Sistema de Combate

### Turno del Héroe (Jugador)

Cuando es el turno de un héroe del jugador, aparece este menú:

```
====== Turno de Stark (Guerrero) ======
Vida: 150/150 -- Defensa: 15 -- Ataque: 35
1. Realizar accion principal (atacar/curar segun rol).
2. Usar objeto equipado.
3. Ver estado del combate.
4. Saltar turno.
========================================
Seleccione una opcion:
```

Si elige la opción 1, cada rol muestra sus opciones específicas. Por ejemplo, el Paladín:

```
========================================
  El Paladin puede realizar diferentes acciones:
  1. Atacar a un enemigo (Justicia Divina)
  2. Otorgar Escudo Protector a un aliado (bloquea 1 ataque)
  3. Bendicion Divina a un aliado (+15 defensa por dos turnos)
  0. Cancelar
========================================
```

### Turno del Enemigo (IA)

Los enemigos actúan automáticamente según su rol. El método `realizarAccionIA()` de cada clase define el comportamiento:

```cpp
// Ejemplo: IA del Guerrero
void Guerrero::realizarAccionIA(vector<Personaje*> aliados, vector<Personaje*> enemigos) {
    // Busca al enemigo con menos vida
    Personaje* objetivo = nullptr;
    int menorVida = 9999;
    
    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i]->getIsEstaVivo() && enemigos[i]->getVida() < menorVida) {
            menorVida = enemigos[i]->getVida();
            objetivo = enemigos[i];
        }
    }
    
    if (objetivo != nullptr) {
        realizarAccion(objetivo);
    }
}
```

### Efectos Temporales

Al final de cada turno, la Arena procesa los efectos temporales:

1. Revisa los objetos equipados de todos los personajes.
2. Si un objeto tiene efecto activo, decrementa los turnos restantes.
3. Si los turnos llegan a 0, llama a `revertirEfecto()` del objeto.
4. También procesa los buffs de habilidades (como Bendición Divina).

```
--- Procesando efectos temporales ---
 >> El efecto del [Amuleto de Furia] ha expirado!!!!
 Ataque de Stark restaurado: 45 --> 35
```

### Fin del Combate

El combate termina cuando todos los miembros de un equipo mueren:

```
===============================================
            FIN DEL COMBATE
===============================================

*** VICTORIA PARA LA GUILD DEL JUGADOR! ***
Motivo: Todos los oponentes han sido derrotados.

Heroes supervivientes: Stark, Fern
Duracion del combate: 7 turnos
Objetos magicos usados: 2
===============================================
```

---

## Persistencia en JSON

### Formato del archivo

Cada héroe se guarda en una línea con formato JSON:

```json
{"nombre":"Stark","rol":"Guerrero","nivel":2,"vida":150,"vidaMaxima":150,"ataque":35,"defensa":15}
{"nombre":"Fern","rol":"Mago","nivel":1,"vida":80,"vidaMaxima":80,"ataque":45,"defensa":5}
```

### Guardar héroes

El método `guardarHeroesEnJSON()` de Guild recorre todos los personajes y escribe cada uno en una línea:

```cpp
for (int i = 0; i < todosLosHeroes.size(); i++) {
    Personaje* h = todosLosHeroes[i];
    
    archivo << "{\"nombre\":\"" << h->getNombre() << "\","
            << "\"rol\":\"" << h->getRol() << "\","
            << "\"nivel\":" << h->getNivel() << ","
            << "\"vida\":" << h->getVida() << ","
            << "\"vidaMaxima\":" << h->getVidaMaxima() << ","
            << "\"ataque\":" << h->getAtaque() << ","
            << "\"defensa\":" << h->getDefensa() << "}" << endl;
}
```

### Cargar héroes

El método `cargarHeroesDesdeJSON()` lee línea por línea y extrae los valores buscando las claves:

```cpp
// Extraer nombre
size_t posNombre = linea.find("\"nombre\":\"");
size_t inicioNombre = posNombre + 10;
size_t finNombre = linea.find("\"", inicioNombre);
string nombre = linea.substr(inicioNombre, finNombre - inicioNombre);
```

Si el héroe ya existe, actualiza sus estadísticas. Si no existe, crea uno nuevo según el rol.

---

## Gestión de Memoria

### Quién es dueño de qué

- **Guild** es dueña de sus Personajes (los crea y destruye).
- **Inventario** es dueño de los ObjetoMagico del catálogo.
- **Personaje** es dueño de sus ObjetoAsignado equipados.
- **Arena** NO es dueña de nada, solo usa punteros prestados.
- **Torneo** es dueño de la Guild del jugador, las guilds enemigas, el Inventario y la Arena.

### Destructores

Cada clase libera lo que le pertenece:

```cpp
Guild::~Guild() {
    // Libera todos los personajes
    for (pair<string, Personaje*> par : this->personajes) {
        delete par.second;
    }
    this->personajes.clear();
}

Personaje::~Personaje() {
    // Libera los objetos equipados
    for (int i = 0; i < this->objetosEquipados.size(); i++) {
        delete objetosEquipados[i];
    }
    this->objetosEquipados.clear();
}
```

### Validación antes de crear

Cuando agregamos un personaje, primero verificamos que no exista para evitar crear memoria que luego se rechaza:

```cpp
void Guild::agregarPersonaje(Personaje* personaje) {
    string nombre = personaje->getNombre();
    
    // Verifica primero
    if (this->personajes.find(nombre) != this->personajes.end()) {
        cout << "Error: Ya existe un personaje llamado " << nombre << endl;
        return;  // No se agregó, el que llamó debe liberar la memoria
    }
    
    personajes[nombre] = personaje;
}
```

---

## Decisiones de Diseño

### Forward Declarations

Para evitar dependencias circulares, usamos declaraciones adelantadas en los headers:

```cpp
// En Personaje.h
class ObjetoAsignado;  // Forward declaration

// El include completo va en Personaje.cpp
#include "../Inventario/ObjetoAsignado.h"
```

### Métodos virtuales puros

Los métodos `realizarAccion()`, `realizarAccionIA()`, `realizarAccionJugador()` y `mostrarInformacion()` son virtuales puros en Personaje:

```cpp
virtual void realizarAccion(Personaje* objetivo) = 0;
```

Esto obliga a cada clase hija a implementar su propia versión, y permite usar polimorfismo:

```cpp
Personaje* heroe = new Guerrero("Stark", "Jugador", 2, 150, 35, 15);
heroe->realizarAccion(enemigo);  // Llama a Guerrero::realizarAccion()
```

### Separación de IA y Jugador

Cada personaje tiene dos métodos para actuar:
- `realizarAccionIA()`: Para cuando la IA controla al personaje (enemigos).
- `realizarAccionJugador()`: Para cuando el jugador controla al personaje.

Ambos terminan llamando a `realizarAccion()` con el objetivo seleccionado.

---

## Equipo de Desarrollo

- Juan Felipe (Pipe)
- Jose Andrade (Richi)
- Angel Obando

---