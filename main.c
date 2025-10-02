#include <ctype.h>
#include "RS.h"
#include "RAL.h"
#include "RAC.h"

/*
// Rebalse abierto lineal
// Costos maximos ->    Evocacion Exitosa= 81         Evocacion Fracaso= 94
// Costos Medios  ->    Evocacion Exitosa= 16.47      Evocacion Fracaso= 70.31

// Rebalse abierto cuadratico
// Costos maximos ->    Evocacion Exitosa= 10         Evocacion Fracaso= 16
// Costos Medios  ->    Evocacion Exitosa= 3.01       Evocacion Fracaso= 7.55

// Rebalse separado
// Costos maximos ->    Evocacion Exitosa= 5          Evocacion Fracaso= 4
// Costos Medios  ->    Evocacion Exitosa= 1.74       Evocacion Fracaso= 1.79

Presione una tecla para continuar . . .
*/

int compararEstructuras(Alumno RAL[], Alumno RAC[], Lista RS, int *cantRAC, int *cantRAL)
{
    FILE* fp = fopen("Operaciones-Alumnos.txt", "r");

    Alumno aux, alumno;
    char cod[8];
    int op, i;
    initRAC(RAC);
    initRAL(RAL);
    initRS(RS);

    // Celdas consultadas
    int evoRS = 1, evoRAL = 0, evoRAC = 0;      //evoRS se inicializa en 1 porque se contempla la consulta de la celda en la posicion que devuelve la funcion de hashing

    // Exito
    int maxRS_E = 0, maxRAL_E = 0, maxRAC_E = 0;
    int cantRS_E = 0, cantRAL_E = 0, cantRAC_E = 0;
    float sumaRS_E = 0, sumaRAL_E = 0, sumaRAC_E = 0;

    // Fracaso
    int maxRS_F = 0, maxRAL_F = 0, maxRAC_F = 0;
    int cantRS_F = 0, cantRAL_F = 0, cantRAC_F = 0;
    float sumaRS_F = 0, sumaRAL_F = 0, sumaRAC_F = 0;

    if(fp == NULL)
    {
        printf("No se encontro el archivo \n");
        return -1;
    }
    else
    {
        while(!feof(fp))
        {
            fscanf(fp, "%d", &op);

            if(op == 1 || op == 2)   // Alta o Baja
            {
                fscanf(fp, " %[^\n]", aux.codigo);
                for(i = 0; i < 7 && aux.codigo[i] != '\0'; i++)
                {
                    aux.codigo[i] = toupper(aux.codigo[i]);
                }
                fscanf(fp, " %[^\n]", aux.nombre);
                fscanf(fp, " %[^\n]", aux.correo);
                fscanf(fp, "%d", &aux.nota);
                fscanf(fp, " %[^\n]", aux.condicion);

                for(i = 0; i < 80 && aux.nombre[i] != '\0'; i++)
                {
                    aux.nombre[i] = toupper(aux.nombre[i]);
                }
                for(i = 0; i < 23 && aux.correo[i] != '\0'; i++)
                {
                    aux.correo[i] = toupper(aux.correo[i]);
                }
                for(i = 0; i < 10 && aux.condicion[i] != '\0'; i++)
                {
                    aux.condicion[i] = toupper(aux.condicion[i]);
                }


                if(op == 1)
                {
                    altaRS(RS, aux);
                    altaRAL(RAL, aux, cantRAL);
                    altaRAC(RAC, aux, cantRAC);

                }
                else
                {
                    bajaRS(RS, aux);
                    bajaRAL(RAL, aux, cantRAL);
                    bajaRAC(RAC, aux, cantRAC);

                }
            }
            else if(op == 3)    // Evocación
            {
                fscanf(fp, " %[^\n]", cod);
                for(i = 0; i < 7 && cod[i] != '\0'; i++)
                {
                    cod[i] = toupper(cod[i]);
                }

                // Rebalse separado
                if(evocarRS(RS, cod, &alumno, &evoRS))
                {
                    sumaRS_E += evoRS;
                    if(evoRS > maxRS_E) maxRS_E = evoRS;
                    cantRS_E++;
                }
                else
                {
                    sumaRS_F += evoRS;
                    if(evoRS > maxRS_F) maxRS_F = evoRS;
                    cantRS_F++;
                }

                // Rebalse abierto lineal
                if(evocarRAL(RAL, &alumno, cod, &evoRAL))
                {
                    sumaRAL_E += evoRAL;
                    if(evoRAL > maxRAL_E) maxRAL_E = evoRAL;
                    cantRAL_E++;
                }
                else
                {
                    sumaRAL_F += evoRAL;
                    if(evoRAL > maxRAL_F) maxRAL_F = evoRAL;
                    cantRAL_F++;
                }

                // Rebalse abierto cuadrático
                if(evocarRAC(RAC, &alumno, cod, &evoRAC))
                {
                    sumaRAC_E += evoRAC;
                    if(evoRAC > maxRAC_E) maxRAC_E = evoRAC;
                    cantRAC_E++;
                }
                else
                {
                    sumaRAC_F += evoRAC;
                    if(evoRAC > maxRAC_F) maxRAC_F = evoRAC;
                    cantRAC_F++;
                }

                evoRS = 0;
                evoRAL = 0;
                evoRAC = 0;

            }
        }
        fclose(fp);

        printf("// Rebalse abierto lineal\n");
        gotoxy(0,2);
        printf("// Costos maximos ->");
        gotoxy(25,2);
        printf("Evocacion Exitosa= %d", maxRAL_E);
        gotoxy(55,2);
        printf("Evocacion Fracaso= %d", maxRAL_F);
        gotoxy(0,3);
        printf("// Costos Medios  ->");

        gotoxy(25,3);
        if(cantRAL_E != 0) printf("Evocacion Exitosa= %.2f", sumaRAL_E/cantRAL_E);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,3);
        if(cantRAL_F!=0) printf("Evocacion Fracaso= %.2f", sumaRAL_F/cantRAL_F);
        else printf("Evocacion Fracaso= 0");

        gotoxy(0,5);
        printf("// Rebalse abierto cuadratico");
        gotoxy(0,6);
        printf("// Costos maximos ->");
        gotoxy(25,6);
        printf("Evocacion Exitosa= %d", maxRAC_E);
        gotoxy(55,6);
        printf("Evocacion Fracaso= %d", maxRAC_F);
        gotoxy(0,7);
        printf("// Costos Medios  ->");
        gotoxy(25,7);

        if(cantRAC_E!=0) printf("Evocacion Exitosa= %.2f", sumaRAC_E/cantRAC_E);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,7);
        if(cantRAC_F) printf("Evocacion Fracaso= %.2f", sumaRAC_F/cantRAC_F);
        else printf("Evocacion Fracaso= 0");

        gotoxy(0,9);
        printf("// Rebalse separado");
        gotoxy(0,10);
        printf("// Costos maximos ->");
        gotoxy(25,10);
        printf("Evocacion Exitosa= %d", maxRS_E);
        gotoxy(55,10);
        printf("Evocacion Fracaso= %d", maxRS_F);
        gotoxy(0,11);
        printf("// Costos Medios  ->");
        gotoxy(25,11);

        if(cantRS_E!=0) printf("Evocacion Exitosa= %.2f", sumaRS_E/cantRS_E);
        else printf("Evocacion Exitosa= 0");

        gotoxy(55,11);
        if(cantRS_F!=0) printf("Evocacion Fracaso= %.2f", sumaRS_F/cantRS_F);
        else printf("Evocacion Fracaso= 0");

        gotoxy(0,13);

    }

    return 1;
}

int main()
{
    Lista RS;
    Alumno RAC[MRAC];
    Alumno RAL[MRAL];

    initRAC(RAC);
    initRAL(RAL);
    initRS(RS);

    int cantRAL = 0;
    int cantRAC = 0;

    int opcion;

    do
    {
        system("cls");
        printf("Ingresar opcion\n");
        printf("1 - Comparar estructuras\n");
        printf("2 - Mostrar rebalse abierto lineal\n");
        printf("3 - Mostrar rebalse abierto cuadratico\n");
        printf("4 - Mostrar rebalse separado\n");
        printf("5 - Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch(opcion)
        {
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
    }
    while(opcion != 5);

    return 0;
}
