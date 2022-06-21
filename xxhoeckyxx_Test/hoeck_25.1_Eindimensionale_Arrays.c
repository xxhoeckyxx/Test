/*
----- lotto.c -----------------------------------------------------------
 Description: Aufgabe 25.1.1 - Ziehen der Lottozahlen simulieren 
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
  int pruefen = 0,
      kugeln_gesamt[100],
      kugeln_gezogen[100],
      kugeln_gesamt1 = 0,
      kugeln_gezogen1 = 0,
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
  while (check_var1 > 3)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Wieviele Kugeln sollen zur Verfuegung stehen (mind. 1 und max 100): ");
    check_var1 = scanf("%d", &kugeln_gesamt);
    fflush(stdin);
  }

  printf("Wieviele werden davon gezogen (mind. 1 und max. %d): ", kugeln_gesamt);
  check_var2 = scanf("%d", &kugeln_gezogen);
  fflush(stdin);
  while (check_var2 > 3)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Wieviele werden davon gezogen (mind. 1 und max. %d): ", kugeln_gesamt);
    check_var2 = scanf("%d", &kugeln_gezogen);
    fflush(stdin);
  }

  printf("%d\n", kugeln_gesamt);
  printf("%d\n", kugeln_gezogen);

  return 0;
}