/*
----- tictac.c ----------------------------------------------------------
 Description: Aufgabe 25.2.2 - Das Spiel Tictac
     Project: Praktikum Informatik 1
      Author: hoeckch80619@th-nuernberg.de
        Date: 22-Juni-2022
-------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define Pi 3.14159265359

int main()
{
  char operand;
  srand((int)time(0));
  int pruefen = 0,
      spielfeld_groesse = 0,
      spieler_wechsel = 0,
      zug_x = 0,
      zug_y = 0,
      sieger = 0,
      check_var1 = 0,
      check_var2 = 0;

  printf("Das Spiel TicTac\n");
  printf("===================\n");

  printf("Spielfeldgroesse (mind. 3, maximal 10): ");
  check_var1 = scanf("%d", &spielfeld_groesse);
  fflush(stdin);
  while (check_var1 > 1 || spielfeld_groesse < 3 || spielfeld_groesse > 10)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Spielfeldgroesse (mind. 3, maximal 10): ");
    check_var1 = scanf("%d", &spielfeld_groesse);
    fflush(stdin);
  }
  char spielfeld[spielfeld_groesse + 2][spielfeld_groesse + 2];

  //spielfeld mit . füllen
  for(int zeile = spielfeld_groesse; zeile > 0; zeile--)
  {
    for(int spalte=spielfeld_groesse; spalte >= 0; spalte--){
      spielfeld[zeile][spalte] = '.' ;
    }
  }
  //spielfeld erste spalte mit zeilennummern füllen
  for (int zeile = spielfeld_groesse; zeile >= 0; zeile--){
    spielfeld[zeile][0] = zeile + '0';
  }

  // Spieler Toggle Funktion
  while(1){
    if (spieler_wechsel == 1)
    {
      // Spieler 1 X ist dran
      printf("\nDein Zug, Spieler 1 (Zeile, Spalte): ");
      check_var2 = scanf("%d,%d", &zug_y, &zug_x);
      fflush(stdin);
      while (check_var2 > 2 || check_var2 < 1 || spielfeld[zug_y][zug_x] == 'X' || spielfeld[zug_y][zug_x] == 'O' || zug_y < 1 || zug_y > spielfeld_groesse || zug_x < 1 || zug_x > spielfeld_groesse)
      {
        // Pruefe ob die Eingabe richtig ist!
        printf("Erneut Versuchen! Dein Zug, Spieler 1 (Zeile, Spalte): ");
        check_var2 = scanf("%d,%d", &zug_y, &zug_x);
        fflush(stdin);
      }
      spielfeld[zug_y][zug_x] = 'X';
      spieler_wechsel--;
    }
    else
    {
      // Spieler 2 O ist dran
      printf("\nDein Zug, Spieler 2 (Zeile, Spalte): ");
      check_var2 = scanf("%d,%d", &zug_y, &zug_x);
      fflush(stdin);
      while (check_var2 > 2 || check_var2 < 1 || spielfeld[zug_y][zug_x] == 'X' || spielfeld[zug_y][zug_x] == 'O' || zug_y < 1 || zug_y > spielfeld_groesse || zug_x < 1 || zug_x > spielfeld_groesse)
      {
        // Pruefe ob die Eingabe richtig ist!
        printf("Erneut Versuchen! Dein Zug, Spieler 2 (Zeile, Spalte): ");
        check_var2 = scanf("%d,%d", &zug_y, &zug_x);
        fflush(stdin);
      }
      spielfeld[zug_y][zug_x] = 'O';
      spieler_wechsel++;
    }

    //spielfeld ausgeben
    for(int zeile = 1; zeile <= spielfeld_groesse; zeile++)
    {
      printf("\n");
      for(int spalte = 0; spalte <= spielfeld_groesse; spalte++)
      {
        printf("\t%c", spielfeld[zeile][spalte]);
      }
    }  
    //überprüfen ob jemand gewonnen hat
    
    for(int durchlauf)

  }
  if(sieger != 0)
  {
    printf("Spieler %d hat gewonnen!", sieger);
  }
  return 0;
}
