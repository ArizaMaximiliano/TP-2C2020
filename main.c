#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "subrutinas.h"

int main (void){
    short retorno = 0;
    int puntero;
    puntero = INICIAR(listado);
    for (int i = 0; i < puntero; i++){
        printf("%s %s %d\n", listado[i].espanol, listado[i].ingles, listado[i].cant_busquedas);
    }
    while(!retorno){
        retorno = MENU(listado, puntero);
    }
    FINALIZAR(listado, puntero);
    scanf(" %d", &puntero);
    return 0;
}