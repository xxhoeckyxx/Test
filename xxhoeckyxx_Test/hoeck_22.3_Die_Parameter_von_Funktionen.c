/*
----- zeitrech.c --------------------------------------------------------
 Description: Aufgabe 22.3.1 - Zeiten-Tachenrechner
     Project: Praktikum Informatik 1
      Author: hoeckch80619@th-nuernberg.de
        Date: 20-Juni-2022
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

int addition(int var1, int var2)
{
  //printf("add var1: %d, var2: %d\n", var1, var2);
  int result = var1 + var2;
  //printf("result: %d\n", result);
  return result;
}

int subtraktion(int var1, int var2)
{
  //printf("sub var1: %d, var2: %d\n", var1, var2);
  int result = var1 - var2;
  //printf("result: %d\n", result);
  return result;
}

int berechnung(int var1, int var2, int var3)
{
  int result;
  //printf("\n var1: %d, var2: %d, var3: %d\n", var1, var2, var3);
  if(var1 == 0)
  {
    result = addition(var2, var3);
  } else {
    result = subtraktion(var2, var3);
  }
  //printf("result: %d\n", result);
  return result;
}

int ueberlaufs_pruefung(int zeitwert, int wert)
{
  int zeahler = 0;
  if (wert == 0 || wert == 1)
  {
    while (zeitwert > 60 || zeitwert < 0)
    {
      if (zeitwert > 60)
      {
        zeitwert = zeitwert - 60;
        zeahler++;
      }
      if (zeitwert < 0)
      {
        zeitwert = zeitwert + 60;
        zeahler--;
      }
    }
  }
  if (wert == 2)
  {
    while (zeitwert > 24 || zeitwert < 0)
    {
      if (zeitwert > 24)
      {
        zeitwert = zeitwert - 24;
        zeahler++;
      }
      if (zeitwert < 0)
      {
        zeitwert = zeitwert + 24;
        zeahler--;
      }
    }
  }
  return zeahler;
}

int richtigstellung_zeit(int zeitwert, int wert)
{
  int zeahler = 0;
  if (wert == 0 || wert == 1)
  {
    while (zeitwert > 60 || zeitwert < 0)
    {
      if(zeitwert > 60)
      {
        zeitwert = zeitwert - 60;
        zeahler++;
      }
      if(zeitwert < 0)
      {
        zeitwert = zeitwert + 60;
        zeahler--;
      }
    }
  }
  if (wert == 2)
  {
    while (zeitwert > 24 || zeitwert < 0)
    {
      if (zeitwert > 24)
      {
        zeitwert = zeitwert - 24;
        zeahler++;
      }
      if (zeitwert < 0)
      {
        zeitwert = zeitwert + 24;
        zeahler--;
      }
    }
  }
  return zeitwert;
}

int pruefe_operand(int pruefen)
{
  if(pruefen == 43)
  {
    return 0;
  } else if(pruefen == 45) {
    return 1;
  } else {
    return 2;
  }
}

int main()
{
  char  operand;
  int pruefen = 0,
      hh = 0,
      mm = 0,
      ss = 0,
      hh1 = 0,
      mm1 = 0,
      ss1 = 0,
      zeit_hh = 0,
      zeit_mm = 0,
      zeit_ss = 0,
      dd_ergebnis = 0,
      hh_ergebnis = 0,
      mm_ergebnis = 0,
      ss_ergebnis = 0,
      check_var1 = 0,
      check_var2 = 0,
      check_var3 = 0;

  printf("STaschenrechner fuer Uhrzeiten\n");
  printf("==============================\n");
  printf("Bitte Startzeit eingeben (hh:mm:ss): ");
  check_var1 = scanf("%d:%d:%d", &hh, &mm, &ss);
  fflush(stdin);
  while(check_var1 > 3)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Bitte Startzeit eingeben (hh:mm:ss): ");
    check_var1 = scanf("%d:%d:%d", &hh, &mm, &ss);
    fflush(stdin);
  }
  printf("Bitte 2. Zeit eingeben (hh:mm:ss): ");
  check_var2 = scanf("%d:%d:%d", &hh1, &mm1, &ss1);
  fflush(stdin);
  while (check_var2 > 3)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Bitte 2. Zeit eingeben (hh:mm:ss): ");
    check_var2 = scanf("%d:%d:%d", &hh1, &mm1, &ss1);
    fflush(stdin);
  }
  printf("Bitte Operation eingeben (+/-): ");
  check_var3 = scanf("%c", &operand);
  //printf("Operand: %d, check_var3: %d\n", operand, check_var3);
  pruefen = pruefe_operand(operand);
  fflush(stdin);
  while (check_var3 != 1 || pruefen > 1)
  {
    // Pruefe ob die Eingabe richtig ist!
    printf("Erneut Versuchen! Bitte  Operation eingeben (+/-): ");
    check_var3 = scanf("%c", &operand);
    //printf("Operand: %d, check_var3: %d\n", operand, check_var3);
    pruefen = pruefe_operand(operand);
    fflush(stdin);
  }
  //printf("pruefen: %d\n", pruefen);

  zeit_hh = berechnung(pruefen, hh, hh1);
  zeit_mm = berechnung(pruefen, mm, mm1);
  zeit_ss = berechnung(pruefen, ss, ss1);

  dd_ergebnis = ueberlaufs_pruefung(hh_ergebnis, 2);
  hh_ergebnis = zeit_hh + ueberlaufs_pruefung(mm_ergebnis, 1);
  mm_ergebnis = zeit_mm + ueberlaufs_pruefung(ss_ergebnis, 0);
  ss_ergebnis = zeit_ss;

  ss_ergebnis = richtigstellung_zeit(ss_ergebnis, 0);
  mm_ergebnis = richtigstellung_zeit(mm_ergebnis, 1);
  hh_ergebnis = richtigstellung_zeit(hh_ergebnis, 2);

  printf("%d:%d:%d %c %d:%d:%d = %d:%d:%d", hh, mm, ss, operand, hh1, mm1, ss1, hh_ergebnis, mm_ergebnis, ss_ergebnis);
}