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

//FUNCIONES/SUBRUTINAS***********************************************

int INICIAR(diccionario lista[]){   //Devulve la cantidad de palabras del archivo
    int puntero = 0;
    FILE *diccionario;
    diccionario = fopen("espaingl.dat","r");
    while (!feof(diccionario)){
        fscanf(diccionario, "%s %s %d", lista[puntero].espanol, lista[puntero].ingles, &lista[puntero].cant_busquedas);
        puntero++;
    }
    fclose(diccionario);
    return puntero;
};

void FINALIZAR(diccionario lista[], int puntero){  //puntero1 = puntero donde termina el archivo  puntero2 = puntero dondeva a terminar el archivo luego del agregado de palabras
    FILE *diccionario;
    diccionario = fopen("espaingl.dat","a");
    for (int i = 0; i<=puntero; i++){
        fprintf(diccionario, "%s %s %d\n", lista[i].espanol, lista[i].ingles, &lista[i].cant_busquedas);
    }
    fclose(diccionario);
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

void ORDENAR_ALFABETICAMENTE(diccionario lista[], int puntero){  //Ordena la estructura, luego al finalizar, se sobreescribe el archivo
    int  j;
    short flag;
    diccionario aux;

    for (int i = 1; i<puntero; i++){
        aux = lista[i];
        j = i-1;
        flag = 1;
        while (flag && j>0){
            if (strcmp(aux.espanol, lista[j].espanol)<0){
                lista[j+1] = lista[j];
                j--;
            }else{
                flag = 0;
            }
        }
        lista[j+1] = aux;
    }
};

int AGREGAR(char palabra[], diccionario lista[], short idioma, int puntero){    //Devuleve el puntero actualizado
    char traduccion[LONGITUD_PALABRA];
    char seleccion = 'N';
    if(puntero<LONGITUD_LISTA){
        while (seleccion == 'N'){
            if (idioma == ESPANOL){
                printf("Ingresar la traduccion al ingles\v\n");
            }else{
                printf("Ingresar la traduccion al español\v\n");
            }
            scanf(" %s", &traduccion);
            printf("¿La traduccion de %s es %s? (Y/N)\v\n", palabra, traduccion);
            scanf(" %c", &seleccion);
            toupper(seleccion);
            while (seleccion != 'Y' && seleccion != 'N'){
                printf("Ingrese una opcion correcta\v\n");
                scanf(" %c", &seleccion);
                toupper(seleccion);
            }
            if (idioma == ESPANOL){
                strcpy(lista[puntero+1].espanol, palabra);
                strcpy(lista[puntero+1].ingles, traduccion);
                lista[puntero+1].cant_busquedas = 0;
            }else{
                strcpy(lista[puntero+1].ingles, palabra);
                strcpy(lista[puntero+1].espanol, traduccion);
                lista[puntero+1].cant_busquedas = 0;
            }
        }
        printf("Palabra agregada con exito!\v\n");
    }else{
        printf("Se alcanzo el tope del diccionario, no se pueden agregar mas palabras!\v\n");  
    }
    return puntero+1;
};

int TRADUCIR(diccionario lista[], short idioma, int puntero){
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
        printf("Palabra no encontrada, ¿Desea agregarla al diccionario? (Y/N)\v\n");
        scanf(" %c", &seleccion);
        toupper(seleccion);
        while (seleccion != 'Y' && seleccion != 'N'){
            printf("Seleccione una opcion correcta!\v\n");
            scanf(" %c", &seleccion);
            toupper(seleccion);
        }
        puntero = AGREGAR(palabra, lista, idioma, puntero);
    }
    return puntero;
};

short SUBMENU(diccionario lista[], short idioma, int puntero){
    char seleccion;
    char seleccion2 = 'Y';
    char palabra[LONGITUD_PALABRA];
    short flag;
    if(idioma == INGLES){
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
        puntero = TRADUCIR(lista,idioma,puntero);
        break;
    
    case 'A':
        while (seleccion2 == 'Y'){
            printf("Ingrese la palabra a agregar\v\n");
            scanf(" %s", palabra);
            if(BUSCAR(palabra, lista, idioma)>=0){
                printf("La palabra buscada ya existe!\v\n");
            }else{
                puntero = AGREGAR(palabra, lista, idioma, puntero);
            }
            printf("¿Desea agregar otra palabra distinta? (Y/N)");
            scanf(" %c", &seleccion2);
            toupper(seleccion2);
            while (seleccion2 != 'Y' && seleccion2 != 'N'){
                printf("Seleccione una opcion correcta!\v\n");
                scanf(" %c", &seleccion2);
                toupper(seleccion2);
            }
        }
        ORDENAR_ALFABETICAMENTE(lista, puntero);
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

short MENU(diccionario lista[], int puntero){
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
        while(SUBMENU(lista, ESPANOL, puntero));//Ingles a español//
        flag = 1;
        break;
    
    case 2:
        while(SUBMENU(lista, INGLES, puntero));//Español a ingles//
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

#endif
//*******************************************************************