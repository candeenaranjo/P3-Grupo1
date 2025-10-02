#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include <ctype.h>
#include "HASH.h"

typedef struct nodo
{
    Alumno dato;
    struct nodo *sig;
} Nodo;

typedef Nodo* Lista[MRS];  // sin  cabecera

void initRS(Lista lista)
{
    int i;
    for(i = 0; i < MRS; i++)
    {
        lista[i] = NULL;
    }
}

void limpiarRS(Lista lista)
{
    int i;
    Nodo* pos = NULL;
    Nodo* aux = NULL;

    for(i = 0; i < MRS; i++)
    {
        pos = lista[i];
        aux = lista[i];
        while(pos != NULL)
        {
            pos = aux->sig;
            free(aux);
            aux = pos;
        }
        free(aux);
        lista[i] = NULL;
    }
}

Nodo* crearNodo(Alumno dato)
{
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    if(nuevoNodo != NULL)
    {
        nuevoNodo->sig = NULL;
        nuevoNodo->dato = dato;
    }

    return nuevoNodo;
}

int localizarRS(Lista lista, char codigo[], int *i, int *celdas, Nodo **pos, Nodo **aux)
{
    *i = hashing(codigo, MRS);
    (*celdas)=0;
    (*pos) = lista[*i];
    (*aux) = lista[*i];


    while((*pos) != NULL && strcmp(codigo, (*pos)->dato.codigo) != 0)
    {
        (*celdas)++;
        (*aux) = (*pos);
        (*pos) = (*aux)->sig;

    }

    if((*pos) != NULL)
    {
        (*celdas)++;
        return 1;
    }
    return 0;
}

int altaRS(Lista lista, Alumno dato)
{
    Nodo* nuevoNodo = crearNodo(dato);
    int celdas = 0;

    if(nuevoNodo == NULL) return -1;

    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i;

    if(localizarRS(lista, dato.codigo, &i, &celdas, &pos, &aux))
    {
        free(nuevoNodo);
        return 0;  // Ya existe
    }
    else
    {
        pos = lista[i];
        nuevoNodo->sig = pos;
        lista[i] = nuevoNodo;
        return 1;
    }
}

int bajaRS(Lista lista, Alumno dato)
{
    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i, celdas = 0;

    if(localizarRS(lista, dato.codigo, &i, &celdas, &pos, &aux) &&
            strcmp(pos->dato.nombre, dato.nombre) == 0 &&
            strcmp(pos->dato.correo, dato.correo) == 0 &&
            pos->dato.nota == dato.nota &&
            strcmp(pos->dato.condicion, dato.condicion) == 0)
    {

        if(aux==NULL)  // Es el primer nodo
        {
            aux = pos->sig;
            lista[i] = pos->sig;
            pos=aux;
        }
        else
        {
            aux->sig = pos->sig;
            pos = aux->sig;
        }
        free(pos);
        return 1;
    }
    return 0;
}

int evocarRS(Lista lista, char cod[], Alumno *dato, int *celdas)
{
    Nodo* pos = NULL;
    Nodo* aux = NULL;
    int i;
    (*celdas)=0;
    if(localizarRS(lista, cod, &i, celdas, &pos, &aux))
    {
        *dato = pos->dato;
        return 1;
    }
    return 0;
}

void mostrarRS(Lista lista)
{
    Nodo* pos = NULL;
    int i, j = 1;

    for(i = 0; i < MRS; i++)
    {
        if(lista[i] == NULL)
        {
            printf("- Lista %d vacia\n", i + 1);
        }
        else
        {
            pos = lista[i];
            printf("- Lista %d\n", i + 1);

            while(pos != NULL)
            {
                printf("  Elemento %d:\n", j);
                printf("\tCodigo: %s\n", pos->dato.codigo);
                printf("\tApellido y Nombre: %s\n", pos->dato.nombre);
                printf("\tcorreo: %s\n", pos->dato.correo);
                printf("\tNota: %d\n", pos->dato.nota);
                printf("\tCondicion Final: %s\n\n", pos->dato.condicion);
                pos = pos->sig;
                j++;

                if(j % 3 == 0)
                {
                    printf("\t");
                    system("pause");
                    printf("\n");
                }
            }
            j = 1;
        }

        if((i + 1) % 5 == 0)
        {
            printf("\n");
            printf(AMARILLO);
            system("pause");
            printf(RESET);
            printf("\n");
        }
    }
}
#endif // RS_H_INCLUDED
