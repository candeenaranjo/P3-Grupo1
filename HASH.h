#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

// Notacion
#define VIRGEN "*"
#define LIBRE "+"

// N = 130
// RAC -> p = 0,81 --------> M = N / p ------> M = 160
// RAL -> P = 0,75 --------> M = N / p ------> M = 173
// RS  -> P = 1.53 --------> M = N / p ------> M = 85

// Definir tamaños de cada rebalse
#define MRAC 160
#define MRAL 173
#define MRS 85

typedef struct{
    char codigo[8];
    char nombre[81];
    char correo[24];
    int nota;
    char condicion[11];
}Alumno;

i nt hashing (char* x, int M)
{
    i nt longitud, i ;
    i nt contador =0;
    l ongitud=strlen (x );
    for ( i =0; i< longitud ; i++) contador +=(( int )x[ i ]) * ( i +1);
    return ( contador %M );
}

#endif // HASH_H_INCLUDED
