/*
----- lotto.c -----------------------------------------------------------
 Description: Aufgabe 25.1.1 - Ziehen der Lottozahlen simulieren 
     Project: Praktikum Informatik 1
      Author: hoeckch80619@th-nuernberg.de
        Date: 23-Juni-2022
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
  int pruefen = 0,
      kugeln_gesamt = 0,
      kugeln_gezogen = 0,
      random_zahl = 0,
      kugeln[100] = {0},
      zeit_kugeln_gesamt = 0,
      zeit_kugeln_gezogen = 0,
      kugeln_gesamt_ergebnis = 0,
      kugeln_gezogen_ergebnis = 0,
      check_var1 = 0,
      check_var2 = 0,
      check_var3 = 0;

  printf("Lottozahlen-Simulation\n");
  printf("=======================\n");

  printf("Wieviele Kugeln sollen zur Verfuegung stehen (mind. 1 und max 100): ");
  check_var1 = scanf("%d", &kugeln_gesamt);
  fflush(stdin);
  while (check_var1 > 1)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Wieviele Kugeln sollen zur Verfuegung stehen (mind. 1 und max 100): ");
    check_var1 = scanf("%d", &kugeln_gesamt);
    fflush(stdin);
  }

  printf("Wieviele werden davon gezogen (mind. 1 und max. %d): ", kugeln_gesamt);
  check_var2 = scanf("%d", &kugeln_gezogen);
  fflush(stdin);
  printf("check-var2: %d\n", check_var2);
  while (check_var2 > 1)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Wieviele werden davon gezogen (mind. 1 und max. %d): ", kugeln_gesamt);
    check_var2 = scanf("%d", &kugeln_gezogen);
    fflush(stdin);
  }
  
  printf("==== %d aus %d ====", kugeln_gezogen, kugeln_gesamt);

  // fill_with_random

  int tmp = 0;
  for (int i = kugeln_gezogen; i > 0; i--)
  {
    srand(tmp);
    tmp = tmp % kugeln_gezogen;
    if (kugeln[tmp] != tmp)
    {
      kugeln[tmp] = tmp;
    }
    else
    {
      i++;
    }
  }

  // gib_aus

  for (int i = 0; i <= 100; i++)
  {
    if (kugeln[i] != 0)
    {
      printf("\t%d", kugeln[i]);
    }
  }

  return 0;
}