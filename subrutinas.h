#ifndef SUBRUTINAS_H
#define SUBRUTINAS_H

//LIBRERIAS**********************************************************
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//DEFINICIONES*******************************************************
#define LONGITUD_LISTA      10000
#define LONGITUD_PALABRA    20
#define ESPANOL     1
#define INGLES      0
#define DICOTOMICA  1
#define SECUENCIAL  0

//ESTRUCTURA DE DATOS************************************************
typedef struct diccionario{
    char espanol[LONGITUD_PALABRA];
    char ingles[LONGITUD_PALABRA];
    int cant_busquedas;
}diccionario;

diccionario lista[LONGITUD_LISTA];

//FUNCIONES/SUBRUTINAS***********************************************
short MENU(diccionario lista[]){
    short flag;
    int seleccion;
    printf("\vMENU\v\n 1 - Ingles a español \v\n 2 - Español a ingles \v\n 0 - Volver\v\n");
    scanf(" %d", &seleccion);
    while(seleccion<0 || seleccion>3){
        printf("Ingrese un valor correcto!\n");
        scanf(" %d", &seleccion);
    }
    switch (seleccion){
    case 1:
        //Ingles a español//
        flag = 1;
        break;
    
    case 2:
        //Español a ingles//
        flag = 1;
        break;

    case 0:
        //Volver//
        flag = 0;
        break;
    
    default:
        break;
    }
    return flag;
};

short SUBMENU(diccionario lista[], short al_idioma){
    char seleccion;
    short flag;
    if(al_idioma == ESPANOL){
        printf("\v\nINGLES A ESPAÑOL\v\n");
    }else{
        printf("\v\nESPAÑOL A INGLES\v\n");
    }
    printf("\v\nT - Traducir \v\n A - Agregar palabra \v\n M - Mas buscadas \v\n V - Volver\v\n");
    scanf(" %d", &seleccion);
    toupper(seleccion);

    while(seleccion != 'T' && seleccion != 'A' && seleccion != 'M' && seleccion != 'V'){
        printf("Ingrese una opcion correcta!\n");
        scanf(" %d", &seleccion);
        toupper(seleccion);
    }

    switch (seleccion){
    case 'T':
        //Traduccion//
        break;
    
    case 'A':
        //Agregar palabra//
        break;

    case 'M':
        //Mas buscados//
        break;

    case 'V':
        //Volver//
        break;

    default:
        break;
    }

};

int BUSCAR(char palabra[], diccionario lista[], short idioma){
    int posicion;
    int i = 0;
    int min = 0;
    int max = LONGITUD_LISTA;
    if (idioma == ESPANOL){
        while(i<LONGITUD_LISTA && strcmp(palabra, lista[i].espanol) != 0){
            i++;
        }
    }else{
        i = (min+max)/2;
        while(min<=max && strcmp(palabra, lista[i].espanol) != 0){
            if(strcmp(palabra, lista[i].espanol)<0){
                max = i-1;
            }else{
                min = i+1;
            }
            i = (min+max)/2;
        }
    }
    return posicion;  
};

void TRADUCIR(diccionario lista[], short idioma){
    int i;
    char seleccion;
    char palabra[LONGITUD_PALABRA];

    printf("Ingrese la palabra a traducir\v\n");
    scanf(" %s", &palabra);
    i = BUSCAR(palabra, lista, idioma);

    if(i>=0){
        lista[i].cant_busquedas++;
        printf("La traduccion de %c%s%c es ", '"', palabra);
        if(idioma == ESPANOL){
            printf("%c%s%c\v\n", '"', lista[i].espanol, '"');
        }else{
            printf("%c%s%c\v\n", '"', lista[i].ingles, '"');
        }
    }else{
        printf("Palabra no encontrada, %cDesea agregarla al diccionario? (Y/N)\v\n", '¿');
        scanf(" %c", &seleccion);
        toupper(seleccion);
        while (seleccion != 'Y' && seleccion != 'N'){
            printf("Seleccione una opcion correcta!\v\n");
            scanf(" %c", &seleccion);
            toupper(seleccion);
        }
        //Agregar palabra al diccionario//
    }
};

void AGREGAR(char palabra[],diccionario lista[], short idioma){
    
};
#endif
//*******************************************************************