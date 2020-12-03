#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "subrutinas.h"

int main (void){
    short retorno = 0;
    int puntero;
    puntero = INICIAR(listado);
    while(MENU(listado, puntero));
    FINALIZAR(listado, puntero);
    return 0;
}