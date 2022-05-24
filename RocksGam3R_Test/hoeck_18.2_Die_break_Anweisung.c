/* 
----- primzahl.c -------------------------------------------------------- 
 Description: Aufgabe 18.2 - Primzahlen zwischen m und n ermitteln
     Project: Praktikum Informatik 1
      Author: hoeckch80619@th-nuernberg.de
        Date: 24-Mai-2022
------------------------------------------------------------------------- 
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define Pi 3.14159265359
int main()
{
	int	m = 0, n = 0, pruefen, zahl = 0, teiler = 0, output = 0;
    int	is_prim = 0, zeahler = 0;
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

    for (zahl = m; zahl <= n; ++zahl)
    {
		bool prim = true;

        for (teiler = 2; prim && teiler <= (zahl+1)/2; ++teiler)
        {
			if (zahl % teiler == 0 || zahl == 1) 
			{
				prim = false;
			}
        }
        if(prim == true || zahl == 1)
        {
			zeahler++;
		    if(zeahler < 8)
		    {
			    printf("%d,\t", zahl);
		    } else {
			    printf("%d, \r\v\t", zahl);
			    zeahler = 0;
		    }
		}
	} 
	return 0;
}