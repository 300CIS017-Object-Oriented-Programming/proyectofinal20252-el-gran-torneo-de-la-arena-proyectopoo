[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Wv2uUvIt)
# El Gran Torneo de Lyrenhold

## Presentación del Proyecto

---

## ¿De qué trata el proyecto?

Imagina un mundo de fantasía llamado Lyrenhold, donde grupos de aventureros (llamados guilds o gremios) compiten en torneos de combate. Tú eres el líder de una de estas guilds y tu misión es:

1. **Reclutar héroes** de diferentes tipos para tu equipo
2. **Equiparlos con objetos mágicos** que les den ventaja
3. **Enfrentarlos contra guilds enemigas** en combates por turnos
4. **Ganar el torneo** derrotando a todos los oponentes

Es como un juego de rol por turnos, pero en la consola de comandos.

---

## ¿Qué tipos de héroes hay?

Cada héroe tiene un rol que define cómo pelea:

### Guerrero
El tanque del equipo. Tiene mucha vida y defensa, y a veces puede dar golpes críticos que hacen el doble de daño. Es el que aguanta los golpes.

### Mago
El cañón de cristal. Hace muchísimo daño mágico que ignora parte de la defensa del enemigo, pero tiene poca vida. Es de vidrio pero pega durísimo.

### Sanador
El soporte del equipo. No ataca, pero puede curar a los compañeros heridos. La curación es variable, a veces cura mucho y a veces poco (como en la vida real, no siempre el médico acierta a la primera).

### Paladín
El protector. Puede atacar, pero también puede poner un escudo a un aliado que bloquea completamente un ataque, o darle una bendición que aumenta su defensa.

### Hechicero Oscuro
El caótico. Usa magia oscura muy poderosa, pero cada vez que ataca se lastima a sí mismo. También puede hacer un ataque de área que daña a TODOS (incluyendo a sus propios aliados). Es muy riesgoso pero muy poderoso.

---

## ¿Qué objetos mágicos hay?

Antes de un combate, puedes equipar a tus héroes con objetos del inventario. Cada héroe puede llevar máximo 2 objetos, y cada objeto solo se puede usar una vez por combate.

### Poción de Vida
Recupera entre 20 y 40 puntos de vida. Lo básico.

### Amuleto de Furia
Aumenta el ataque del héroe por 2 turnos. Después vuelve a la normalidad.

### Escudo Bendito
Aumenta la defensa del héroe por 1 turno. Útil cuando sabes que te van a atacar.

### Pacto Sangriento
Sacrificas parte de tu vida a cambio de un aumento permanente de ataque. Para los que les gusta vivir al límite.

### Caballa Legendaria del Destino
Un pez místico. Cuando lo usas, hay 50% de probabilidad de matar instantáneamente al enemigo que elijas... y 50% de probabilidad de que TÚ mueras. Solo para los valientes (o locos).

### Poción de Resurrección
Revive a un compañero caído con la mitad de su vida. Puede cambiar el rumbo de una batalla.

---

## ¿Cómo funciona el combate?

El combate es por turnos, como en los juegos de rol clásicos:

1. **Turno de tus héroes**: Tú decides qué hace cada uno. Pueden atacar, usar habilidades especiales, o usar un objeto equipado.

2. **Turno de los enemigos**: La computadora decide automáticamente qué hace cada enemigo según su tipo.

3. **Repetir** hasta que un equipo completo sea derrotado.

### Ejemplo de turno:

```
====== Turno de Stark (Guerrero) ======
Vida: 150/150 -- Defensa: 15 -- Ataque: 35
1. Realizar accion principal (atacar/curar segun rol).
2. Usar objeto equipado.
3. Ver estado del combate.
4. Saltar turno.
========================================
```

Si eliges atacar y tienes suerte con el golpe crítico:

```
╔════════════════════════════════════════╗
║    ESTOCADA MORTAL                     ║
╚════════════════════════════════════════╝
Stark invoca todo su poder!!!!
¡¡¡¡GOLPE CRITICO!!!!
Stark ataca a Dravos con un golpe devastador!
Dravos recibe: 70 puntos de daño. Vida restante: 70
```

---

## ¿Qué más puedo hacer?

Además de combatir, el juego tiene varias funciones:

### Gestión de tu Guild
- Ver todos tus héroes y sus estadísticas
- Crear nuevos héroes
- Retirar héroes que ya no quieras
- Ver qué objetos tiene equipado cada héroe

### Gestión del Inventario
- Ver qué objetos mágicos hay disponibles
- Asignar objetos a tus héroes
- Retirar objetos de los héroes
- Crear nuevos objetos (si se eliminaron)
- Modificar el stock de objetos

### Ver Guilds Enemigas
- Conocer contra quién vas a pelear
- Ver los miembros de cada guild enemiga

### Guardar y Cargar
- Guardar el estado de tus héroes en un archivo
- Cargar héroes guardados anteriormente

---

## Menú Principal

Así se ve el menú principal del juego:

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

---

## Ejemplo de una batalla

### Inicio del combate:

```
===============================================
          PREPARANDO LA ARENA
===============================================

======= Tu Equipo (5 Heroes): ========
 -Stark (Guerrero)
 -Fern (Mago)
 -Sein (Sanador)
 -Himmel (Paladin)
 -Ubel (Hechicero Oscuro)

======= Equipo Enemigo (4 Oponentes): ========
 -Korgath (Guerrero)
 -Miriel (Sanador)
 -Shalltear (Paladin)
 -Momonga (Hechicero Oscuro)

===============================================
          QUE COMIENCE EL COMBATE!
===============================================
```

### Durante el combate:

```
================================================
              TURNO 3
================================================

--- FASE DE LOS HEROES ---

====== Turno de Fern (Mago) ======
Vida: 80/80 -- Defensa: 5 -- Ataque: 45

╔════════════════════════════════════════╗
║    ZOOLTRAAK                           ║
╚════════════════════════════════════════╝
Fern invoca el poder de la luz sagrada!
El hechizo ignora 50% de la defensa enemiga!!!!!
Korgath recibe: 65 puntos de daño. Vida restante: 35
```

### Fin del combate:

```
===============================================
            FIN DEL COMBATE
===============================================

*** VICTORIA PARA LA GUILD DEL JUGADOR! ***
Motivo: Todos los oponentes han sido derrotados.

Heroes supervivientes: Stark, Fern, Himmel
Duracion del combate: 8 turnos
Objetos magicos usados: 3
===============================================
```

---

## Datos curiosos del proyecto

- Hay 5 tipos de héroes diferentes, cada uno con su propia inteligencia artificial.
- Hay 6 tipos de objetos mágicos con efectos únicos.
- El sistema puede guardar y cargar partidas.
- Los efectos de algunos objetos duran varios turnos y se revierten automáticamente.
- La Caballa Legendaria es un homenaje a los objetos absurdamente riesgosos de los RPGs (mas especificamente a la caballa del juego **NieR: Automata** del director **Yoko Taro**).

---

## Tecnologías usadas

- **C++**: Lenguaje de programación
- **POO**: Programación Orientada a Objetos (herencia, polimorfismo, encapsulamiento)
- **STL**: Librería estándar de C++ (vector, unordered_map, string)
- **JSON**: Formato para guardar datos

---

## El equipo

Este proyecto fue desarrollado por:

- **Juan Felipe (Pipe)**: Diseño general, sistema de personajes y combate
- **Jose Andrade (Richi)**: Sistema de objetos mágicos e inventario
- **Angel Obando**: Integración y pruebas

---


