#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persona.h"


/*
  iniciamos una persona.

*/

Persona* persona_init() {

  Persona *persona = malloc(sizeof(Persona));
  persona->nombre = NULL;
  persona->lugarDeNacimiento = NULL;

  return persona;
}

/*
  rellenamos una persona con la informacion correspondiente.

*/
Persona* persona_rellenar(Persona* persona, char* nombre, char* lugarDeNacimiento, int edad ){

  persona->nombre = malloc (sizeof(char) * (strlen(nombre) + 1) );
  persona->lugarDeNacimiento = malloc (sizeof(char) * (strlen(lugarDeNacimiento) + 1) );

  strcpy(persona->nombre, nombre);
  strcpy(persona->lugarDeNacimiento, lugarDeNacimiento);
  persona->edad = edad;

  return persona;//Devolvemos en puntero a la estructura.
}

/*
  liberamos una persona.

*/
void persona_destruir(Persona* persona){
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
}
