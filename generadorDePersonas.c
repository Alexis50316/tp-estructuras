#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "glist.h"
#include "persona.h"
#include "funcionesExtras.c"
#include "algDeOrd.c"


/*creamos las funciones para glist_destruir*/
void destruir_char(void* dato){
  free(dato);
}

void destruir_persona(void* dato){
  Persona *persona = dato;
  persona_destruir(persona);
}

int comparar( void * dato1 , void * dato2 ) {
  Persona* persona = dato1;
  Persona* persona2 = dato2;
  if(persona->edad <= persona2->edad)
    return 1;
  return 0;
}

/*


Por otra parte en el Main, recibir por consola , nombre de archivos países , nombre, y cantidad a generar.

Funciones a generar, elegir_ramdom(GList lista ) ;
El cual Dada una lista de elementos retorna un elemento de la misma al azar.

Bien ahora la implementación en general.

Por un lado leer los archivos de nombres y países y guardar la información substraida en una lista.
Luego de eso crear una GLits de personas , rellenarla según la cantidad de personas a generar que especifique el usuario.

Volcar los datos en el archivo de salida ,

Por último liberar todas las listas
*/

int main(int argc, char *argv[]){
  /*nombres(argv[1]), lugarDeNacimiento(argv[2]),
     salida(argv[3]) , cantidad(argv[4]) */
  /*semilla random*/
	srand(time(NULL));

	//creamos dos listas, una para nombres y otra para los lugares de nacimiento.
	GList listaN ,listaP;
	listaN = glist_crear();
	listaP = glist_crear();

	//Rellenamos las listas de nombres y  de los lugares de nacimiento.
	listaP=leer_archivo(argv[2], listaP);
	listaN=leer_archivo(argv[1], listaN);

  /*generamos las N personas al azar*/
  GList personas= glist_crear();
  personas = generar_personas(listaP, listaN, personas, atoi(argv[4]));

  personas = glist_mergeSort( personas , comparar);
  /*generamos el archivo de salida*/
	salida(personas,argv[3], atoi(argv[4]));

	/*Destruimos las listas creadas*/
	glist_destruir(listaN, destruir_char);
	glist_destruir(listaP, destruir_char);
  glist_destruir(personas, destruir_persona);
}
