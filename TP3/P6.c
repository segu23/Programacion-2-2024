#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "pilas.h"


#include "pilas_arreglos.c"

/**
6.	Dada una pila con valores al azar eliminar todas las ocurrencias de un determinado ítem sin perder la pila original.
	Deberá retornar una nueva pila sin el ítem en consideración.
	Resolver iterativamente y recursivamente.
	Determinar la       complejidad algorítmica de ambas soluciones.
 */
// retornar la nueva pila sin la clave que se debe sacar (eliminar). Si la clave no esta se retorna la pila recibida.
// La definicion vale para ambas resoluciones

int random_number(int min_num, int max_num){
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; 
    } else {
        low_num = max_num + 1; 
        hi_num = min_num;
    }
    result = (rand() % (hi_num - low_num)) + low_num;

    return result;
}

Pila crearListaAleatoria(int longitud){
    Pila pila = p_crear();
    
    srand(time(NULL));
    for(int i = 0; i < longitud; i++) {
        int number = random_number(0, 9);
        TipoElemento tipoElemento = te_crear(number);
        p_apilar(pila, tipoElemento);
    }

    return pila;
}
Pila eliminarRecursivamente(Pila p, Pila aux, Pila aux2, int clave, int stage){
    if(stage == 2 && p_es_vacia(aux)) return aux2;

    if(p_es_vacia(p) && stage == 1) stage++;

    if(stage == 1){
        p_apilar(aux, p_desapilar(p));
        return eliminarRecursivamente(p, aux, aux2, clave, stage);
    }else if(stage == 2){
        TipoElemento tipoElemento = p_desapilar(aux);
        p_apilar(p, tipoElemento);
        if(tipoElemento->clave != clave){
            p_apilar(aux2, tipoElemento);
        }
        return eliminarRecursivamente(p, aux, aux2, clave, stage);
    }
}

Pila eleminarIterativamente(Pila p, Pila aux, Pila aux2, int clave){
    while(!p_es_vacia(p)){
        TipoElemento elemento1 = p_desapilar(p);
        p_apilar(aux, elemento1);
    }

    while (!p_es_vacia(aux)){
        TipoElemento elementoaux = p_desapilar(aux);
        p_apilar(p, elementoaux);
        if(elementoaux->clave != clave ){
            p_apilar(aux2, elementoaux);
        }

    }

    
    return aux2; 
    
}

Pila p_ej6_eliminarclave(Pila p, int clave){
    Pila aux = p_crear();
    Pila aux2 = p_crear();
    //Resuelto recursivamente
    return eliminarRecursivamente(p, aux, aux2, clave, 1);
    //Resuelto iterativamnte 
    //return eleminarIterativamente(p, aux, aux2, clave);
}

void cargarPila(Pila pila){
    bool seguirIngresando = true;
    int terminoElegido;
    char opcionSeguir;

    while (seguirIngresando){
        printf("[INPUT] Ingrese un elemento para agregar a la pila: ");
        if (scanf("%i", &terminoElegido)>0){
            p_apilar(pila, te_crear(terminoElegido));
            printf("[INFO] Agregado!\n");
        }
        else{
            if (scanf("%c", &opcionSeguir)>0 && opcionSeguir == 'n'){
                printf("[INFO] Finalizando carga de la pila.\n");
                seguirIngresando = false;
            }
            else{
                printf("[ERROR] Debe ingresar un numero.\n");
            }
            fflush(stdin);
        }
    }
}


int main(){
    Pila pila1 = crearListaAleatoria(10);
    p_mostrar(pila1);
    int clave;
    printf("Ingrese clave:");
    scanf("%d",&clave);

    Pila n = p_ej6_eliminarclave(pila1, clave);
    system("clear");
    printf("Pila original: \n");
    p_mostrar(pila1);
    
    printf("Nueva pila sin ocurrencias de %d:\n", clave);    
    p_mostrar(n);

    return 0;
}