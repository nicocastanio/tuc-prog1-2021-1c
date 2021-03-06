#include <stdio.h>

// Eleva al cubo una variable mediante una llamada por referencia, con un apuntador como argumento
void cuboPorReferencia(int *ptrN); 

int main()
{
  int numero = 5; /* inicializa numero */

  printf("El valor original de numero es %d", numero);

  /* pasa la dirección de numero a cuboPorReferencia */
  cuboPorReferencia(&numero);

  printf("\nEl nuevo valor de numero es %d\n", numero);

  return 0; /* indica terminación exitosa */

} /* fin de main */

/* calcula el cubo de *ptrN; modifica la variable numero en main */
void cuboPorReferencia(int *ptrN)
{
  // ptrN = 10; -> NO 
  *ptrN = *ptrN * *ptrN * *ptrN; /* cubo de *ptrN */
} /* fin de la función cuboPorReferencia */
