#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "pilas.h"
#define MAX 100

#include "pilas_arreglos.c"


/**
4.	Construir un algoritmo que, utilizando el TAD Pila, permita convertir un número decimal pasado como parámetro,
	a su correspondiente valor expresado en una base de 2 a 16 (hexadecimal).
	Determinar la complejidad algorítmica de la solución.
*/
// retorna el valor cambiado de base como un string (char*).  Si la base no esta entre 2 y 16 retorno el mismo numero recibido como string (char*).
char*  p_ej4_cambiarbase(int decimal, int base){
    if ((base < 2) || (base > 16)) {
        char* error = malloc(MAX * sizeof(char));
        sprintf(error, "%d", decimal);
        return error;
    }
    Pila P1 = p_crear();
    if (decimal == 0){
        p_apilar(P1, te_crear(0));
    }

    while (decimal > 0){
        int newDecimal = decimal/base;
        int resto = decimal % base;
        p_apilar(P1, te_crear(resto));

        decimal = newDecimal;
    }

    char* resultado = (char*)malloc(MAX * sizeof(char));
    int i= 0;
    while (!p_es_vacia(P1)){
        TipoElemento elemento = p_desapilar(P1);
        int valor =elemento->clave;
        if (valor < 10){
            resultado[i]= valor + '0';
        }
        else{
            resultado[i] = valor + 'A' -10;
        }
        free (elemento);
        i++;        
    }
    resultado[i] = '\0';
    free(P1);
    return resultado;

}


int main(){
    int decimal;
    int base;
    printf("Ingrese un numero decimal:\n");
    scanf("%d", &decimal);

    printf("Ingrese la base a la que quiere pasar su decimal:\n");
    scanf("%d", &base);

    char* resultado = p_ej4_cambiarbase(decimal, base);
    printf("%s\n", resultado);

    free(resultado); 
    system("pause");
    return 0;
}