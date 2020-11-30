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

diccionario listado[LONGITUD_LISTA];

//FUNCIONES/SUBRUTINAS***********************************************

int INICIAR(diccionario listado[]){   //Devulve la cantidad de palabras del archivo
    int puntero = 0;
    FILE *diccionario;
    diccionario = fopen("espaingl.dat","r");
    while (!feof(diccionario)){
        fscanf(diccionario, "%s %s %d", listado[puntero].espanol, listado[puntero].ingles, &listado[puntero].cant_busquedas);
        puntero++;
    }
    fclose(diccionario);
    return puntero;
};

void FINALIZAR(diccionario listado[], int puntero){  //puntero1 = puntero donde termina el archivo  puntero2 = puntero dondeva a terminar el archivo luego del agregado de palabras
    FILE *diccionario;
    diccionario = fopen("espaingl.dat","a");
    for (int i = 0; i<=puntero; i++){
        fprintf(diccionario, "%s %s %d\n", listado[i].espanol, listado[i].ingles, &listado[i].cant_busquedas);
    }
    fclose(diccionario);
};

int BUSCAR(char palabra[], diccionario listado[], short idioma){
    int posicion;
    int i = 0;
    int min = 0;
    int max = LONGITUD_LISTA;
    if (idioma == ESPANOL){
        while(i<LONGITUD_LISTA && strcmp(palabra, listado[i].espanol) != 0){
            i++;
        }
    }else{
        i = (min+max)/2;
        while(min<=max && strcmp(palabra, listado[i].espanol) != 0){
            if(strcmp(palabra, listado[i].espanol)<0){
                max = i-1;
            }else{
                min = i+1;
            }
            i = (min+max)/2;
        }
    }
    return posicion;  
};

void ORDENAR_ALFABETICAMENTE(diccionario listado[], int puntero){  //Ordena la estructura, luego al finalizar, se sobreescribe el archivo
    int  j;
    short flag;
    diccionario aux;

    for (int i = 1; i<puntero; i++){
        aux = listado[i];
        j = i-1;
        flag = 1;
        while (flag && j>0){
            if (strcmp(aux.espanol, listado[j].espanol)<0){
                listado[j+1] = listado[j];
                j--;
            }else{
                flag = 0;
            }
        }
        listado[j+1] = aux;
    }
};

int AGREGAR(char palabra[], diccionario listado[], short idioma, int puntero){    //Devuleve el puntero actualizado
    char traduccion[LONGITUD_PALABRA];
    char seleccion = 'N';
    if(puntero<LONGITUD_LISTA){
        while (seleccion == 'N'){
            if (idioma == ESPANOL){
                printf("Ingresar la traduccion al ingles\n");
            }else{
                printf("Ingresar la traduccion al español\n");
            }
            scanf(" %s", &traduccion);
            printf("¿La traduccion de %s es %s? (Y/N)\n", palabra, traduccion);
            scanf(" %c", &seleccion);
            toupper(seleccion);
            while (seleccion != 'Y' && seleccion != 'N'){
                printf("Ingrese una opcion correcta\n");
                scanf(" %c", &seleccion);
                toupper(seleccion);
            }
            if (idioma == ESPANOL){
                strcpy(listado[puntero+1].espanol, palabra);
                strcpy(listado[puntero+1].ingles, traduccion);
                listado[puntero+1].cant_busquedas = 0;
            }else{
                strcpy(listado[puntero+1].ingles, palabra);
                strcpy(listado[puntero+1].espanol, traduccion);
                listado[puntero+1].cant_busquedas = 0;
            }
        }
        printf("Palabra agregada con exito!\n");
    }else{
        printf("Se alcanzo el tope del diccionario, no se pueden agregar mas palabras!\n");  
    }
    return puntero+1;
};

int TRADUCIR(diccionario listado[], short idioma, int puntero){
    int i;
    char seleccion;
    char palabra[LONGITUD_PALABRA];

    printf("Ingrese la palabra a traducir\n");
    scanf(" %s", palabra);
    i = BUSCAR(palabra, listado, idioma);

    if(i>=0){
        listado[i].cant_busquedas +=1;
        printf("La traduccion de %c%s%c es ", '"', palabra);
        if(idioma == ESPANOL){
            printf("%c%s%c\n", '"', listado[i].espanol, '"');
        }else{
            printf("%c%s%c\n", '"', listado[i].ingles, '"');
        }
    }else{
        printf("Palabra no encontrada, ¿Desea agregarla al diccionario? (Y/N)\n");
        scanf(" %c", &seleccion);
        toupper(seleccion);
        while (seleccion != 'Y' && seleccion != 'N'){
            printf("Seleccione una opcion correcta!\n");
            scanf(" %c", &seleccion);
            toupper(seleccion);
        }
        puntero = AGREGAR(palabra, listado, idioma, puntero);
    }
    return puntero;
};

short SUBMENU(diccionario listado[], short idioma, int puntero){
    char seleccion;
    char seleccion2 = 'Y';
    char palabra[LONGITUD_PALABRA];
    short flag;
    if(idioma == INGLES){
        printf("\t\tINGLES A ESPAÑOL\n");
    }else{
        printf("\t\tESPAÑOL A INGLES\n");
    }
    printf("\tT - Traducir\n A - Agregar palabra \n M - Mas buscadas \n V - Volver\n");
    scanf(" %c", &seleccion);
    toupper(&seleccion);
    while(seleccion != 'T' && seleccion != 'A' && seleccion != 'M' && seleccion != 'V'){
        printf("Ingrese una opcion correcta!\n");
        scanf(" %c", &seleccion);
        toupper(seleccion);
    }

    switch (seleccion){
    case 'T':
        puntero = TRADUCIR(listado,idioma,puntero);
        break;
    
    case 'A':
        while (seleccion2 == 'Y'){
            printf("Ingrese la palabra a agregar\n");
            scanf(" %s", palabra);
            if(BUSCAR(palabra, listado, idioma)>=0){
                printf("La palabra buscada ya existe!\n");
            }else{
                puntero = AGREGAR(palabra, listado, idioma, puntero);
            }
            printf("¿Desea agregar otra palabra distinta? (Y/N)");
            scanf(" %c", &seleccion2);
            toupper(seleccion2);
            while (seleccion2 != 'Y' && seleccion2 != 'N'){
                printf("Seleccione una opcion correcta!\n");
                scanf(" %c", &seleccion2);
                toupper(seleccion2);
            }
        }
        ORDENAR_ALFABETICAMENTE(listado, puntero);
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

short MENU(diccionario listado[], int puntero){
    short flag;
    int seleccion;
    printf("\t\tMENU\n 1 - Ingles a español\n 2 - Español a ingles\n 0 - Volver\n");
    scanf(" %d", &seleccion);
    while(seleccion<0 || seleccion>3){
        printf("Ingrese un valor correcto!\n");
        scanf(" %d", &seleccion);
    }
    switch (seleccion){
    case 1:
        while(SUBMENU(listado, INGLES, puntero));//Ingles a español//
        flag = 1;
        break;
    
    case 2:
        while(SUBMENU(listado, ESPANOL, puntero));//Español a ingles//
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