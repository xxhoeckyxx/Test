/* 
----- primzahl.c -------------------------------------------------------- 
 Description: Aufgabe 18.2 - Primzahlen zwischen m und n ermitteln
     Project: Praktikum Informatik 1
      Author: hoeckch80619@th-nuernberg.de
        Date: 30-Mai-2022
------------------------------------------------------------------------- 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main()
{
	int 	m = 0, 
			n = 0, 
			zahl = 0, 
			teiler = 0, 
			output = 0, 
			zeahler = 0;
	bool	pruefen = true,
			is_prim = false;
	printf("Primzahlen\n");
	printf("==========\n\n");
	printf("Dieses Programm gibt Ihnen alle Primzahlen zwischen\nm und n aus. m und n sind dabei einzugeben.\n");
	do 
	{
		printf("m: ");
		scanf("%d", &m);
		fflush(stdin);
		printf("n: ");
		scanf("%d", &n);
		fflush(stdin);
		if(m == 0 || n == 0 || n < m)
		{
			printf("Erneut Versuchen!\n");
		}
	} while(m == 0 || n == 0 || n < m);
	printf("\t");

	for(zahl = m; zahl <= n; zahl++)
	{
		if(zahl == 1)
		{
			zahl++;
		}
		is_prim = true;
		for(teiler = 2; teiler < (zahl/2); teiler++)
		{
			if(zahl % teiler == 0)
			{
				is_prim = false;
				break;
			}
		}
		if(is_prim == true)
		{
			zeahler++;
			if(zeahler < 8)
			{
				printf("%d,\t", zahl);
			}
			else
			{
				printf("%d, \r\v\t", zahl);
				zeahler = 0;
			}
		}
	}
	return 0;
}