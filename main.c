#include <stdio.h>
#include <stdlib.h>
#include "RS.h"
#include "RAL.h"
#include "RAC.h"

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

int main()
{
    Lista RS[MRS];
    Alumno RAC[MRAC];
    Alumno RAL[MRAL];

    initRAC(RAC);
    initRAL(RAL);
    initRS(RS);

    int cantRAL = 0;
    int cantRAC = 0;

    int opcion;


    do{
        system("cls");
        printf("Ingresar opcion\n");
        printf("1 - Comparar estructuras\n");
        printf("2 - Mostrar rebalse abierto lineal\n");
        printf("3 - Mostrar rebalse abierto cuadratico\n");
        printf("4 - Mostrar rebalse separado\n");
        printf("5 - Salir\n");
        scanf("%d", &opcion);
        fflush(stdin);

        switch(opcion){
            case 1:
                system("cls");
                initRAC(RAC);
                initRAL(RAL);
                limpiarRS(RS);
                cantRAC = 0;
                cantRAL = 0;
                compararEstructuras(RAL, RAC, RS, &cantRAC, &cantRAL);
                system("pause");
            break;
            case 2:
                system("cls");
                mostrarRAL(RAL);
                system("pause");
            break;
            case 3:
                system("cls");
                mostrarRAC(RAC);
                system("pause");
            break;
            case 4:
                system("cls");
                mostrarRS(RS);
                system("pause");
            break;
        }
    }while(opcion!=5);
}
