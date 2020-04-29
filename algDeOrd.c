#include "glist.h"

typedef int (* Compara ) ( void * dato1 , void * dato2 ) ;

void intercambiar(GList min, GList primerElemento){
  GList aux2 = primerElemento->sig;
  primerElemento->sig = min->sig;
  min->sig = aus2;

  aux2 = primerElemento->ant;
  primerElemento->ant = min->ant;
  min->ant = aus2;
  if(!glist_vacia(primerElemento->sig->ant))
    primerElemento->sig->ant = primerElemento);;
  if(!glist_vacia(aux->ant->sig))
    aux->ant->sig = aux;

  min->sig->ant = min;
  primerElemento->ant->sig = primerElemento;
}

void rotar(GList pivot, GList eleARotar){
  GList aux;
  eleARotar->sig = pivot->sig;
  pivot->sig = eleARotar;
  if(eleARotar->sig != NULL)
    eleARotar->sig->ant = eleARotar;

  aux = eleARotar->ant;
  eleARotar->ant = pivot;
  pivot->ant = aux;

  if(pivot->ant != NULL)
    pivot->ant->sig = pivot;
}

GList glist_marge(GList left, GList right, Compara c) {
  GList primerElemento;
  GList ultimoElemento;
  int lenleft = glist_longitud(left);
  int lenright = glist_longitud(right);

  while(lenleft > 0 && lenright > 0) {
    if (c(left->dato, right->dato)) {
      if(glist_vacia(primerElemento)) {
        primerElemento = left;
        left->ant = NULL;
        ultimoElemento = left;
      }
      else {
        ultimoElemento->sig = left;
        left->ant = ultimoElemento;
        ultimoElemento = left;
      }
      left = left->sig;
      left->ant = NULL;
      lenleft = lenleft - 1;
    }
    else {
      if(glist_vacia(primerElemento)) {
        primerElemento = right;
        right->ant = NULL;
        ultimoElemento = right;
      }
      else {
        ultimoElemento->sig = right;
        right->ant = ultimoElemento;
        ultimoElemento = right;
      }
      right = right->sig;
      right->ant = NULL;
      lenright= lenright - 1;
    }
  }

  if (lenleft > 0) {
    ultimoElemento->sig = left;
    left->ant = ultimoElemento;
  }
  if (lenright > 0 ) {
    ultimoElemento->sig = right;
    right->ant = ultimoElemento;
  }
  return primerElemento;
}


GList glist_mergeSort(GList lista, Compara c) {
  int len = glist_longitud(lista);
  if (len <= 1)
    return lista;
  //pasamos a dividir la lista en dos.
  GList lista2 = lista;
  for (size_t i = 0; i < (len/2) - 1; i++)
    lista2 = lista2->sig;
  GList aux= lista2;
  lista2 = lista2->sig;
  aux->sig = NULL;
  lista2->ant = NULL;
  //aplicamos recursion
  lista = glist_mergeSort(lista, c);
  lista2 = glist_mergeSort(lista2, c);
  //mezclamos las listas
  return lista = glist_marge(lista, lista2, c);

}


GList glist_selectionSort( GList lista , Compara c ) {
  GList primerElemento = lista;
  GList min, pivot;
  int len = glist_longitud(lista);
  for ( ; primerElemento != NULL;  primerElemento = primerElemento->sig) {
    min = primerElemento;
    pivot = primerElemento->sig;
    for (; pivot != NULL; pivot = pivot->sig ) {
      if(c(pivot, min))
        min = pivot;
    }
    if(min != primerElemento){
      if(primerElemento == lista){
        if(primerElemento->sig != min)
          intercambiar( min, primerElemento);
        else
          rotar(min, primerElemento);
        lista = min;
      }
      else{
        if(primerElemento->sig != min)
          intercambiar( min, primerElemento);
        else
          rotar(min, primerElemento);
      }
      primerElemento = min;
    }
  }
return lista;
}



//creo que esto funciona.
GList glist_insertionSort( GList lista , Compara c ) {
  if(glist_vacia(lista) || glist_vacia(lista->sig))
    return lista;
  GList pivot;
  GList clave = lista->sig;;
  for ( ; clave == NULL; clave = clave->sig) {
    pivot = clave;
    while(c(pivot, pivot->ant)) {
      //entonces es menor que el elemento anterior
      if(pivot->ant == lista){
        rotar( pivot, pivot->sig)
        lista = pivot;
      }
      else{
        rotar( pivot, pivot->sig)
      }
    }
  }
  return lista;
}
