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
  //  Einfache Addition zweier Zahlen

  //printf("add var1: %d, var2: %d\n", var1, var2);
  int result = var1 + var2;
  //printf("result: %d\n", result);
  return result;
}

int subtraktion(int var1, int var2)
{
  //  Einfache Subtraktion zweier Zahlen
  
  //printf("sub var1: %d, var2: %d\n", var1, var2);
  int result = var1 - var2;
  //printf("result: %d\n", result);
  return result;
}

int berechnung(int var1, int var2, int var3)
{
  //  Auswahl der Add oder Sub mit hilfe einer Variablen + uebergabe der Einzelnen Operanten

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
  // Ueberpruefen ob eine Zahl in das Uhren-Format passt bspw. 24h oder 60min/sec 
  // durch die Variable "wert" wird uebermittelt um welchen Stellenwert es sich handelt
  // durch den Zeahler wird der Wert des neachst hoeheren Stellenwert ermittelt
  // -> Somit umrechnung von Sek in Min und von Min in Std sowie von Std in Tage moeglich

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
  // selbes Prinzip wie bei "ueberlaufs_pruefung()" 
  // Aenderungen:
  // - Es wird die Zeit auf den tatsaechlichen Wert gesetzt nicht nur der Ueberlauf ermittelt
  // - Stunden werden richtig Subtrahiert und Addiert

  int zeahler = 0,
      zeitwert_alt = zeitwert;
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
    if(zeitwert_alt < zeitwert)
    {
      zeitwert = -zeitwert;
    }
  }
  return zeitwert;
}

int pruefe_operand(int pruefen)
{
  // Pruefung ob der richtige Operant eingegeben wurde 
  // ASCII 43 = +
  // ASCII 45 = -
  // fuer alle faschen Werte erhealt man "2" zurueck

  if(pruefen == 43)
  {
    return 0;
  } else if(pruefen == 45) {
    return 1;
  } else {
    return 2;
  }
}

int printZeiten(char operand, int std1, int min1, int sek1, int std2, int min2, int sek2, int day3, int std3, int min3, int sek3)
{
  if(day3 == 0)
  {
    printf("%d:%d:%d %c %d:%d:%d = %d:%d:%d", std1, min1, sek1, operand, std2, min2, sek2, std3, min3, sek3);
  } else if(std3 == 0) {
    printf("%d:%d %c %d:%d = %d:%d", min1, sek1, operand, min2, sek2, min3, sek3);
  } else if(min3 == 0) {
    printf("%d %c %d = %d", sek1, operand, sek2, sek3);
  } else if(day3 == 1){
    printf("%d:%d:%d %c %d:%d:%d = %d Tag %d:%d:%d", std1, min1, sek1, operand, std2, min2, sek2, day3, std3, min3, sek3);
  } else {
    printf("%d:%d:%d %c %d:%d:%d = %d Tage %d:%d:%d", std1, min1, sek1, operand, std2, min2, sek2, day3, std3, min3, sek3);
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

  printf("Taschenrechner fuer Uhrzeiten\n");
  printf("=============================\n");

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

  // Neue Zeiten werden berechnet und zwischen gespeichert

  zeit_ss = berechnung(pruefen, ss, ss1);
  zeit_mm = berechnung(pruefen, mm, mm1);
  zeit_hh = berechnung(pruefen, hh, hh1);

  // Zeiten werden mit hilfe des Ueberlaufes erstmal zusammengefasst

  ss_ergebnis = zeit_ss;
  mm_ergebnis = zeit_mm + ueberlaufs_pruefung(ss_ergebnis, 0);
  hh_ergebnis = zeit_hh + ueberlaufs_pruefung(mm_ergebnis, 1);
  dd_ergebnis = ueberlaufs_pruefung(hh_ergebnis, 2);

  // Zeiten werden angepasst damit nichts mehr doppelt vorhanden ist

  ss_ergebnis = richtigstellung_zeit(ss_ergebnis, 0);
  mm_ergebnis = richtigstellung_zeit(mm_ergebnis, 1);
  hh_ergebnis = richtigstellung_zeit(hh_ergebnis, 2);

  //Ausgabefunktion mit Fallunterscheidung -> je nach Bedarf Tage, Std, Min und/oder Sek anzeigen

  printZeiten(operand, hh, mm, ss, hh1, mm1, ss1, dd_ergebnis, hh_ergebnis, mm_ergebnis, ss_ergebnis);
  
}