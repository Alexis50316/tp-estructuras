#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "glist.h"
#include "persona.h"
/*
  elegir_random: GList -> char*

  La función elegir_random recibe como único parámetro una SList (lista) y a partir de un número random n , avanza n elementos
  desde el inicio de la lista. Luego, devuelve el puntero a dicho elemento.

*/

char* elegir_random(GList lista,int len) {
  if (len == 1)
    return lista->dato;

  int distancia = rand() % len;
  /*Llegamos hasta el elemento de la lista que se encuentra a una distancia del inicio de la lista*/
  for (int i = 0; i < distancia; i++)
    lista = lista->sig;

  /*devolvemos el puntero a el elemento random de la lista*/
  return lista->dato;
}






/*
  leer_archivo: char* -> Datos -> void

  la función leer_archivo recibe como primer parámetro un array tipo char
  que tendrá el nombre del archivo a leer, como segundo parámetro recibe una
  estructura tipo Datos donde se guardara la información del archivo.
  como primer paso se leerá el archivo verificando que no sea vació ni null,
  luego de esto se leerá linea por linea guardando en la estructura correspondiente
  la información obtenida de cada linea según corresponda.

  Nota: castear la estructura correspondiente segun corresponda.

*/

GList leer_archivo(char* archivo, GList datos) {
  /*direccion del archivo en caso que la direccion obtenida no sea valida*/
  char direccionDeArchivo[100];

  /*tamaño predeterminados para leer las lineas.*/
  int longitud = 100;
  /*información: lugar donde ira la informacion extraida de cada linea*/
  char* informacion = malloc(sizeof(char) * longitud);

  /*Localizamos el archivo y lo abrimos en modo de lectura*/
  FILE *fp1;
  fp1 = fopen(archivo, "r");

  printf("Comenzando extraccion de los datos del archivo llamado %s.\n",archivo);

  /*Tomamos la primera linea*/
  if (fp1 != NULL) fgets(informacion, longitud, fp1);

  /*Verificamos que no este vacio y de que exista*/
  while (fp1 == NULL || strlen(informacion) == 0) {
    if (strlen(informacion) == 0 && fp1 != NULL){
      printf("El archivo ingresado es vacio, por favor ingrese un archivo con al menos un dato.\n>>");
      fclose(fp1);
    }
    else {
      printf("Error en apertura de archivo.\n Vuelva a ingresar la direccion del archivo. \n>>>");
    }
    scanf("%s", direccionDeArchivo);
    fp1 = fopen(direccionDeArchivo, "r"); /*Abrimos el archivo en modo lectura*/
    if (fp1 != NULL) fgets(informacion, longitud, fp1);
  }

  /*Extraemos la información del archivo*/
  int len;/*representa la longitud de la informacion estraida*/

  while (!feof(fp1)) {
    len = strlen(informacion);

    informacion[len - 2] = '\0';

    char* dato = malloc (sizeof(char) * (len + 1) );
    strcpy(dato, informacion);
    dato[len] = '\0';

    datos = glist_agregar_inicio(datos , dato);//Agregamos lo que este contenido en información dentro de la lista

    fgets(informacion, longitud, fp1);
  }
  free(informacion);
  printf("Extraccion finalizada con exito.\n\n");
  /*Cerramos el archivo*/
  fclose(fp1);

  return datos;
}



/*
	elegir_elementos: GList -> GList -> GList -> int -> GList.

	La función elegir_elementos recibe como parámetros dos GList (listaP y listaN)(las cuales contendrán lugares de nacimiento y nombres
	respectivamente)y se encarga de elegir elementos random de las dos listas y un numero al azar de 1 a 99 ,

*/


GList generar_personas(GList listaP, GList listaN, GList personas, int cantPersAGener) {
  int EdadAleatoria;
  char* nombre;
  char* lugarDeNacimiento;//punteros a un GNodo auxiliares para no modificar la listas recibidas en la función.
  Persona *NuevaPersona;

  int lenNombre = glist_longitud(listaN);
  int lenlugarDeNacimiento = glist_longitud(listaP);

  for (int i = 0; i < cantPersAGener; i++) {
    //Elegimos un elemnto random de listaN y listaP , y un número al azar .
    nombre = elegir_random(listaN, lenNombre);
    lugarDeNacimiento = elegir_random(listaP, lenlugarDeNacimiento);
    EdadAleatoria = (rand()%100)+1;

    NuevaPersona = persona_init();
    NuevaPersona = persona_rellenar(NuevaPersona, nombre, lugarDeNacimiento, EdadAleatoria);

    personas = glist_agregar_inicio(personas, NuevaPersona);
  }
  return personas;
}


void salida(GList personas , char* salida, int cantPersAGener) {

	FILE *fp;
	fp = fopen(salida ,"w+");//Abrimos el archivo en modo lectura y escritura.
	//Si el archivo existe entonces pisa todo su contenido y, si no existe lo crea.
        Persona* persona;

	for ( ; personas != NULL; personas = personas->sig) {
          persona = personas->dato;
	  fprintf(fp, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
	}

	//Cerramos el archivo
	fclose(fp);
	printf("Se creo con exito el archivo llamado: %s\ncon una cantidad %d de personas al azar.\n", salida, cantPersAGener);
}
