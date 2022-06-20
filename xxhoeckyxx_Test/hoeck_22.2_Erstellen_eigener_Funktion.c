/*
----- strekzug.c --------------------------------------------------------
 Description: Aufgabe 22.2.1 - Leange eines Streckenzuges
     Project: Praktikum Informatik 1
      Author: hoeckch80619@th-nuernberg.de
        Date: 16-Juni-2022
-------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define Pi 3.14159265359

int strecke(int x_1, int x_2)
{
    //Vektoraufsstellung: Spitze minus Fuß
    int delta_x = x_2 - x_1;
    return delta_x;
}

float pythagoras(float a, float b)
{
    // Satz des Pythagoras, da rechtwinkliges Dreieck
    float c = sqrt(pow(a, 2.0)+pow(b, 2.0));
    return c;
}
int streckenabschnit(int var1, int var2)
{
    // Addiert zwei Abschnitte
    // In diesem Fall nicht notwendig!
    int abschnitt = var1 + var2;
    return abschnitt;
}

float differenz_zweier_punkte(int var1, int var2, int var3, int var4)
{
    // Rechnet die Länge des Vektors aus mit Hilfe des Pythagoras und der Vektoraufsstellung
    int strecke_x = strecke(var1, var2);
    //printf("Strecke X: %d\n", strecke_x);
    int strecke_y = strecke(var3, var4);
    //printf("Strecke Y: %d\n", strecke_y);
    float fstrecke_x = strecke_x;
    float fstrecke_y = strecke_y;
    float ergebnis = pythagoras(fstrecke_x, fstrecke_y);
    //printf("Ergebnis: %f\n", ergebnis);
    return ergebnis;
}

int main()
{
    int     x = 0,
            y = 0,
            x1 = 0,
            y1 = 0,
            strecke_x = 0,
            strecke_y = 0,
            zeahler = 1,
            check_var1 = 0,
            check_var2 = 0;
    float   teiler_a, 
            teiler_b, 
            streckenergebnis = 0;
    bool    pruefen = true,
            is_prim = false;
    printf("Strecken-Berechnungen\n");
    printf("=======================\n");
    printf("Bitte Startpunkt eingeben (x,y): ");
    check_var1 = scanf("%d,%d", &x, &y);
    fflush(stdin);
    if(check_var1 != 2)
    {
        // Pruefe ob die Eingabe richtig is^1y234t
        printf("Erneut Versuchen! Bitte Startpunkt eingeben (x,y): ");
        check_var1 = scanf("%d,%d", &x, &y);
        fflush(stdin);
    }

    do
    {
        printf("Neuen %d.Streckenpunkt x,y (Abbruch mit x=-1): ", zeahler);
        check_var2 = scanf("%d,%d", &x1, &y1);
        fflush(stdin);
        //printf("\nZeahler vorher: %d\n", zeahler);
        if(zeahler >= 2)
        {
            if((check_var2 == 1) && (x1 == -1))
            {
                // Abruchbedingung
                break;
            }
            /**else
            {
                printf("Es fehlen noch Streckenpunkte!\n");
            }**/
        }
        //printf("\nZeahler nach zeahler>=2: %d\n", zeahler);

        if(check_var2 != 2)
        {
            // Pruefe ob die Eingabe richtig ist
            printf("Erneut Versuchen! Bitte %d.Streckenpunkt eingeben (x,y): ", zeahler);
            check_var2 = scanf("%d,%d", &x, &y);
            fflush(stdin);
        }
        //printf("\nZeahler nach check_var2: %d\n", zeahler);

        //printf("check_var2: %d & x: %d\n", check_var2, x);
        // Errechnen der Strecke, bei jeder Wiederholung addieren des naechsten Punktes: 
        streckenergebnis += differenz_zweier_punkte(x, x1, y, y1);
        //printf("check_var2: %d & x: %d\n", check_var2, x);
        x = x1;
        y = y1;
        zeahler++;
        //printf("\nZeahler nach zeahler++: %d\n", zeahler);

    }
    while(zeahler >= 1);

    /*do
    {
        printf("Neuer Streckenpunkt x,y (Abbruch mit x=-1):");
        int check_var2 = scanf("%d,%d", &x1, &y1);
        fflush(stdin);
        strecke_x = strecke(x, x1);
        strecke_y = strecke(y, y1);
        teiler_a = strecke_x;
        teiler_b = strecke_y;
        streckenergebnis += pythagoras(teiler_a, teiler_b);
        x = x1;
        y = y1;
        printf("X neu: %d, Y neu: %d", x, y);
    } while(check_var2 > 1 && x1 != -1);*/
   
    //printf("check_var2: %d & x: %d\n", check_var2, x);
    printf("\n => Die Streckenleange betreagt: %.2f Einheiten", streckenergebnis);
}