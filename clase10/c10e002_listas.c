#include <stdio.h>
#include <stdlib.h>

//  Listas ligadas o enlazadas
/*
es una colección *lineal* de estructuras autorreferenciadas, llamadas nodos, conectadas por medio
de ligas apuntador; de aquí el término lista "ligada". 
Se accede a una lista ligada a través de un apuntador al primer nodo de la lista. 
Se accede a los nodos subsiguientes a través del miembro liga almacenado en cada nodo. 
Por convención, el apuntador liga del último nodo de una lista se establece en NULL, para marcar el final
de la lista. Los datos se almacenan en una lista ligada dinámicamente; conforme es necesario, se crea cada
nodo. Un nodo puede contener datos de cualquier tipo, incluso otros objetos struct.

ventajas sobre los arrays: 
. cuando el número de elementos a representarse en la estructura de datos es impredecible
. son dinámicas, por lo que la longitud de una lista puede cambiar
. los arrays pueden llenarse, para las listas es mas dificil
. si se declara un array mas grande que lo necesario, estamos desperdiciando memoria. 

*/

// Operación y mantenimiento de una lista
// manipula una lista de caracteres. El programa proporciona dos opciones:
// 1) insertar un carácter en la lista en orden alfabético (función insertar), y
// 2) eliminar un carácter de la lista (función eliminar).

/* estructura auto_referenciada */
struct nodoLista
{
  char dato;                      /* cada nodoLista contiene un caracter */
  struct nodoLista *ptrSiguiente; /* apuntador al siguiente nodo */
};                                /* fin de la estructura nodoLista */

typedef struct nodoLista NodoLista; /* sinónimo para la estructura nodoLista */
typedef NodoLista *ptrNodoLista;    /* sinónimo para de NodoLista* */

/* prototipos */
void insertar(ptrNodoLista *ptrS, char valor);
char eliminar(ptrNodoLista *ptrS, char valor);
int estaVacia(ptrNodoLista ptrS);
void imprimeLista(ptrNodoLista ptrActual);
void instrucciones(void);

int main()
{
  ptrNodoLista ptrInicial = NULL; /* inicialmente no existen nodos */
  int eleccion;                   /* elección del usuario */
  char elemento;                  /* carácter introducido por el usuario */

  instrucciones(); /* despliega el menú */
  printf("? ");
  scanf("%d", &eleccion);

  /* repite mientras el usuario no elija 3 */
  while (eleccion != 3)
  {

    switch (eleccion)
    {

    case 1:
      printf("Introduzca un caracter: ");
      scanf("\n%c", &elemento);
      insertar(&ptrInicial, elemento); /* inserta el elemento en la lista */
      imprimeLista(ptrInicial);
      break;

    case 2:

      /* si la lista no está vacía */
      if (!estaVacia(ptrInicial))
      {
        printf("Introduzca un caracter para eliminar: ");
        scanf("\n%c", &elemento);

        /* si encuentra el carácter, lo remueve */
        if (eliminar(&ptrInicial, elemento))
        { /* elimina elemento */
          printf("caracter %c eliminado.\n", elemento);
          imprimeLista(ptrInicial);
        } /* fin de if */
        else
        {
          printf("no se encuentra el caracter %c.\n\n", elemento);
        } /* fin de else */

      } /* fin de if */
      else
      {
        printf("La lista esta vacia.\n\n");
      } /* fin de else */

      break;

    default:
      printf("Opcion invalida.\n\n");
      instrucciones();
      break;

    } /* fin de switch */

    printf("? ");
    scanf("%d", &eleccion);
  } /* fin de while */

  printf("Fin de la ejecucion.\n");

  return 0; /* indica terminación exitosa */

} /* fin de main */

/* despliega las instrucciones del programa para el usuario */
void instrucciones(void)
{
  printf("Introduzca su eleccion:\n"
         " 1 para insertar un elemento en la lista.\n"
         " 2 para eliminar un elemento de la lista.\n"
         " 3 para terminar.\n");
} /* fin de la función instrucciones */

/* Inserta un nuevo valor dentro de la lista en orden */
void insertar(ptrNodoLista *ptrS, char valor)
{
  ptrNodoLista ptrNuevo;    /* apuntador a un nuevo nodo */
  ptrNodoLista ptrAnterior; /* apuntador a un nodo previo de la lista */
  ptrNodoLista ptrActual;   /* apuntador al nodo actual de la lista */

  ptrNuevo = malloc(sizeof(NodoLista)); /* crea un nodo */

  if (ptrNuevo != NULL)
  {                                /* es espacio disponible */
    ptrNuevo->dato = valor;        /* coloca el valor en el nodo */
    ptrNuevo->ptrSiguiente = NULL; /* el nodo no se liga a otro nodo */

    ptrAnterior = NULL;
    ptrActual = *ptrS;

    /* ciclo para localizar la ubicación correcta en la lista */
    while (ptrActual != NULL && valor > ptrActual->dato)
    {
      ptrAnterior = ptrActual;             /* entra al ... */
      ptrActual = ptrActual->ptrSiguiente; /* ... siguiente nodo */
    }                                      /* fin de while */

    /* inserta un nuevo nodo al principio de la lista */
    if (ptrAnterior == NULL)
    {
      ptrNuevo->ptrSiguiente = *ptrS;
      *ptrS = ptrNuevo;
    } /* fin de if */
    else
    { /* inserta un nuevo nodo entre ptrAnterior y ptrActual */
      ptrAnterior->ptrSiguiente = ptrNuevo;
      ptrNuevo->ptrSiguiente = ptrActual;
    } /* fin de else */

  } /* fin de if */
  else
  {
    printf("No se inserto %c. No hay memoria disponible.\n", valor);

  } /* fin de else */

} /* fin de la función insertar */

/* Elimina un elemento de la lista */
char eliminar(ptrNodoLista *ptrS, char valor)
{
  ptrNodoLista ptrAnterior; /* apuntador a un nodo previo de la lista */
  ptrNodoLista ptrActual;   /* apuntador al nodo actual de la lista */
  ptrNodoLista tempPtr;     /* apuntador a un nodo temporal */

  /* elimina el primer nodo */
  if (valor == (*ptrS)->dato)
  {
    tempPtr = *ptrS;               /* almacena el nodo a eliminar */
    *ptrS = (*ptrS)->ptrSiguiente; /* desata el nodo */
    free(tempPtr);                 /* libera el nodo desatado */
    return valor;
  } /* fin de if */
  else
  {
    ptrAnterior = *ptrS;
    ptrActual = (*ptrS)->ptrSiguiente;

    /* ciclo para localizar la ubicación correcta en la lista */
    while (ptrActual != NULL && ptrActual->dato != valor)
    {
      ptrAnterior = ptrActual;             /* entra al ... */
      ptrActual = ptrActual->ptrSiguiente; /* ... siguiente nodo */
    }                                      /* fin de while */

    /* elimina el nodo de ptrActual */
    if (ptrActual != NULL)
    {
      tempPtr = ptrActual;
      ptrAnterior->ptrSiguiente = ptrActual->ptrSiguiente;
      free(tempPtr);
      return valor;
    } /* fin de if */

  } /* fin de else */

  return '\0';

} /* fin de la función eliminar */

/* Devuelve 1 si la lista está vacía, de lo contrario, 0 */
int estaVacia(ptrNodoLista ptrS)
{
  return ptrS == NULL;

} /* fin de la función function estaVacia */

/* Imprime la lista */
void imprimeLista(ptrNodoLista ptrActual)
{

  /* si la lista está vacía */
  if (ptrActual == NULL)
  {
    printf("La lista esta vacia.\n\n");
  } /* fin de if */
  else
  {
    printf("La lista es:\n");

    /* mientras no sea el final de la lista */
    while(ptrActual != NULL)
    {
      printf("%c —> ", ptrActual->dato);
      ptrActual = ptrActual->ptrSiguiente;
    } /* fin de while */

    printf("NULL\n\n");
  } /* fin de else */

} /* fin de la función imprimeLista */

/*
Introduzca su eleccion:
1 para insertar un elemento en la lista.
2 para eliminar un elemento de la lista.
3 para terminar.
? 1
Introduzca un caracter: B
La lista es:
B --> NULL
? 1
Introduzca un caracter: A
La lista es:
A --> B --> NULL
? 1
Introduzca un caracter: C
La lista es:
A --> B --> C --> NULL
? 2
Introduzca un caracter para eliminar: D
no se encuentra el caracter D.
? 2
Introduzca un caracter para eliminar: B
caracter B eliminado.
La lista es:
A --> C --> NULL
? 2
Introduzca un caracter para eliminar: C
caracter C eliminado.
La lista es:
A --> NULL
? 2
Introduzca un caracter para eliminar: A
caracter A eliminado.
La lista esta vacia.
? 4
Opcion invalida.
Introduzca su eleccion:
1 para insertar un elemento en la lista.
2 para eliminar un elemento de la lista.
3 para terminar.
? 3
Fin de la ejecucion.
*/