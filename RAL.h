#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include <ctype.h>
#include "HASH.h"

void initRAL(Alumno lista[]){
    int i;

    for(i = 0; i < MRAL; i++){
        strcpy(lista[i].codigo, VIRGEN);
    }
}

int localizarRAL(Alumno lista[], char codigo[], int *pos, int *celdas){
    int i = hashing(codigo, MRAL);
    int primerLibre = -1;
    int vistos = 0;


    while(vistos < MRAL && strcmp(lista[i].codigo, VIRGEN) != 0 && strcmp(lista[i].codigo, codigo) != 0){

        if(strcmp(lista[i].codigo, LIBRE) == 0 && primerLibre == -1) primerLibre = i;

        vistos++;
        (*celdas)++;
        i = (i + 1) % MRAL;
    }

    if(strcmp(lista[i].codigo, VIRGEN) == 0) (*celdas)++;

    if(strcmp(lista[i].codigo, codigo) == 0){
        (*celdas)++;
        *pos = i;
        return 1;
    }
    else if(strcmp(lista[i].codigo, VIRGEN) == 0 && primerLibre == -1) *pos = i;
    else if((vistos == MRAL && primerLibre != -1) || (strcmp(lista[i].codigo, VIRGEN) == 0 && primerLibre != -1)) *pos = primerLibre;

    return 0;
}

int altaRAL(Alumno lista[], Alumno dato, int *cant){
    int celdas = 0;

    if(*cant == MRAL) return -1;
    else{
        int pos;

        if(localizarRAL(lista, dato.codigo, &pos, &celdas)) return 0;
        else{
            lista[pos] = dato;
            (*cant)++;
            return 1;
        }
    }
}

int bajaRAL(Alumno lista[], Alumno dato, int *cant){
    int pos, celdas = 0;

    if(localizarRAL(lista, dato.codigo, &pos, &celdas) &&
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

int evocarRAL(Alumno lista[], Alumno *dato, char codigo[], int *celdas){
    int pos;
    (*celdas)=0;
    if(localizarRAL(lista, codigo, &pos, celdas)){
        *dato = lista[pos];
        return 1;
    }

    return 0;
}

void mostrarRAL(Alumno lista[]){
    int i;

    for(i = 0; i < MRAL; i++){
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

#endif // RAL_H_INCLUDED
