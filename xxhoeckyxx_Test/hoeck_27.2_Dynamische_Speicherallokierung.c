/*----- strilist.c --------------------------------------------------------
 Description: Aufgabe 27.1 - Strichliste
     Project: Praktikum Informatik 2
      Author: hoeckch80619@th-nuernberg.de
        Date: 10-Dezember-2022
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_fkt(int *input)
{
    int pruefe = 0;
    do                                              /*  Schleife um die Eingabe zu ueberpruefen                         */
    {
        printf("Gib eine Zahlenfolge ein: \n");     /*  Text zum einlesen der Zahl                                      */
        pruefe = scanf("%d", input);                /*  Einlesen der Zahl                                               */
        fflush(stdin);
        if (pruefe != 1)                            /*  Wird solange wiederholt bis der Benutzer das richtige eingibt   */
        {
            printf("Erneut Versuchen!\n\n");
        }
    } while (pruefe != 1);                          /*  Pruefbedingung                                                  */
    printf("Die Zahlenfolge ist %d\n", *input);
}

void haeufigkeits_berechnung(int *haeufigkeit, int *size, int *input)
{
    int groesse = *input;
    //printf("%d\n", *size);
    //printf("%d\n", groesse);
    while(groesse > 0)
    {
        if(groesse > 0)
        {
            groesse = groesse/10;
            //printf("Groesse: %d\n", groesse);
        }
        *size = *size + 1;
    }
    *size = *size + 1;
    printf("%d\n", *size);
    haeufigkeit = (int *)malloc((*size) * sizeof(int));
    while(*input > 0)
    {
        haeufigkeit[*input%10] = haeufigkeit[*input%10] + 1;
        printf("Haeufigkeit[%d]: %d\n", *input%10, haeufigkeit[*input%10]);
        *input = *input/10;
        //printf("Input %d\n", *input);
    }
}

void strichliste_array(int *size, int *input, int *haeufigkeit, char *array, int zaehler)
{
    // printf("Array-Groesse eingeben: ");
    // scanf("%d", &size);
    
    //  Speicher reservieren
    array = (char *)malloc((haeufigkeit[zaehler]) * sizeof(char));
    memset(array, '|', haeufigkeit[zaehler]);
    array[haeufigkeit[zaehler]] = NULL;

    if (array != NULL)
    {
        printf("\nSpeicher ist reserviert - Groesse ist %d\n", *size);
    }
    else
    {
        printf("\nKein freier Speicher vorhanden.\n");
    }

    printf("%d %s, %d\n", haeufigkeit[zaehler], array, *size);
    free(array);
}

int main()
{
    int  size = 0, 
         input = 0,
         *haeufigkeit = 0;
    char *array = NULL;

    input_fkt(&input);
    haeufigkeits_berechnung(haeufigkeit, &size, &input);
    strichliste_array(&size, &input, haeufigkeit, array, 1);

    return 0;
}