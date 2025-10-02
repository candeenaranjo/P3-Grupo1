#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include <ctype.h>
#include "HASH.h"

void initRAC(Alumno lista[]){
    int i;

    for(i = 0; i < MRAC; i++){
        strcpy(lista[i].codigo, VIRGEN);
    }
}

int localizarRAC(Alumno lista[], char codigo[], int *pos, int *celdas){
    int i = hashing(codigo, MRAC);
    int primeraLibre = -1;
    int vistos = 0;

    (*celdas)=0;


    while(vistos < MRAC && strcmp(lista[i].codigo, VIRGEN) != 0 && strcmp(codigo, lista[i].codigo) != 0){
        if(strcmp(lista[i].codigo, LIBRE) == 0 && primeraLibre == -1) primeraLibre = i;

        vistos++;
        (*celdas)++;
        i = (i + (vistos * vistos)) % MRAC; // Sondeo cuadrático
    }

    if(strcmp(lista[i].codigo, VIRGEN) == 0) (*celdas)++;

    if(strcmp(codigo, lista[i].codigo) == 0){
        (*celdas)++;
        *pos = i;
        return 1;
    }else if(vistos == MRAC && primeraLibre == -1){
        return -1;
    }else if((vistos == MRAC && primeraLibre != -1) || (strcmp(lista[i].codigo, VIRGEN) == 0 && primeraLibre != -1)){
        *pos = primeraLibre;
    }
    else{
        *pos = i;
    }

    return 0;
}

int altaRAC(Alumno lista[], Alumno dato, int *cant){
    int celdas = 0;

    if(*cant == MRAC) return -1;
    else{
        int pos;
        int resultado = localizarRAC(lista, dato.codigo, &pos, &celdas);

        if(resultado == 1 || resultado == -1) return 0;
        else{
            lista[pos] = dato;
            (*cant)++;
            return 1;
        }
    }
}

int bajaRAC(Alumno lista[], Alumno dato, int *cant){
    int pos, celdas = 0;

    if(localizarRAC(lista, dato.codigo, &pos, &celdas) == 1 &&
       strcmp(lista[pos].nombre, dato.nombre) == 0 &&
       strcmp(lista[pos].correo, dato.correo) == 0 &&
       lista[pos].nota == dato.nota &&
       strcmp(lista[pos].condicion, dato.condicion) == 0){
        strcpy(lista[pos].codigo, LIBRE);
        (*cant)--;
        return 1;
    }else{
        return 0;
    }
}

int evocarRAC(Alumno lista[], Alumno *dato, char codigo[], int *celdas){
    int pos;
    (*celdas)=0;
    if(localizarRAC(lista, codigo, &pos, celdas) == 1){
        *dato = lista[pos];
        return 1;
    }

    return 0;
}

void mostrarRAC(Alumno lista[]){
    int i;

    for(i = 0; i < MRAC; i++){
        if(strcmp(lista[i].codigo, VIRGEN) == 0){
            printf("Celda %d virgen\n", i + 1);
        }else if(strcmp(lista[i].codigo, LIBRE) == 0){
            printf("Celda %d libre\n", i + 1);
        }else{
            printf("Celda %d\n", i + 1);
            printf("\tCodigo: %s\n", lista[i].codigo);
            printf("\tApellido y Nombre: %s\n", lista[i].nombre);
            printf("\tcorreo: %s\n", lista[i].correo);
            printf("\tNota: %d\n", lista[i].nota);
            printf("\tCondicion Final: %s\n\n", lista[i].condicion);
        }

        if((i + 1) % 3 == 0){
            printf("\n");
            printf(AMARILLO);
            system("pause");
            printf(RESET);
            printf("\n");
        }
    }
}
#endif // RAC_H_INCLUDED
