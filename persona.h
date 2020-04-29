#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>

typedef struct {
  char * nombre ;
  int edad ;
  char * lugarDeNacimiento ; // pais o capital
} Persona ;

//typedef Persona Persona;

/*
  iniciamos una persona.

*/

Persona* persona_init();

/*
  le asiganmos a una persona la informacion correspondiente.

*/
Persona* persona_rellenar(Persona* persona, char* nombre, char* lugarDeNacimiento, int edad );

/*
  liberamos una persona.

*/
void persona_destruir(Persona* persona);



#endif /* __PERSONA_H__ */
