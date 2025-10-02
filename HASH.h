#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <ctype.h>

#define RESET "\x1b[0m"
#define AMARILLO "\x1b[33m"

// Notacion
#define VIRGEN "*"
#define LIBRE "+"

// N = 130
// RAC -> p = 0,81 --------> M = N / p ------> M ≈ 160.5 → primo 161
// RAL -> P = 0,75 --------> M = N / p ------> M ≈ 173.3 → primo 173
// RS  -> P = 1.53 --------> M = N / p ------> M ≈ 84.97 → primo 85

// Definir tamaños de cada rebalse
#define MRAC 161
#define MRAL 174
#define MRS 85

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}


typedef struct
{
    char codigo[8];
    char nombre[81];
    char correo[24];
    int nota;
    char condicion[11];
} Alumno;

int hashing (char* x, int M)
{
    int longitud, i ;
    int contador =0;
    longitud=strlen (x );
    for ( i =0; i< longitud ; i++)
    {
        contador +=(( int )toupper(x[ i ])) * ( i +1);
    }
    return ( contador %M );
}

#endif // HASH_H_INCLUDED
