#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

// Funktion zur Polynom-Multiplikation
void polymul(double *a, int a_size, double *b, int b_size, double *result)
{
    for (int i = 0; i < a_size + b_size - 1; i++)
    {
        result[i] = 0;
    }
    for (int i = 0; i < a_size; i++)
    {
        for (int j = 0; j < b_size; j++)
        {
            result[i + j] += a[i] * b[j];
        }
    }
}

// Funktion zur Berechnung der Übertragungsfunktion bei einer bestimmten Frequenz
complex double polyval(double *coeffs, int size, complex double s)
{
    complex double result = 0;
    for (int i = 0; i < size; i++)
    {
        result += coeffs[i] * cpow(s, size - 1 - i);
    }
    return result;
}

int main()
{
    // Gegebene Übertragungsfunktion des Reglers
    double num_G_R[] = {19.95}; // {1.46 * 0.17, 1.46};
    int num_G_R_size = 1;
    double den_G_R[] = {1}; // {0.17, 0};
    int den_G_R_size = 1;

    // Gegebene Systemübertragungsfunktion
    double num_G_S[] = {560.2918371};
    int num_G_S_size = 1;
    double den_G_S[] = {1, 45.80555021, 256.2606541};
    int den_G_S_size = 3;

    // Offene Übertragungsfunktion
    double num_G0[num_G_R_size + num_G_S_size - 1];
    double den_G0[den_G_R_size + den_G_S_size - 1];
    polymul(num_G_R, num_G_R_size, num_G_S, num_G_S_size, num_G0);
    polymul(den_G_R, den_G_R_size, den_G_S, den_G_S_size, den_G0);

    // Ausgabe der Koeffizienten von G0
    printf("G0(s) Zählerkoeffizienten: ");
    for (int i = 0; i < num_G_R_size + num_G_S_size - 1; i++)
    {
        printf("%f ", num_G0[i]);
    }
    printf("\n");

    printf("G0(s) Nennerkoeffizienten: ");
    for (int i = 0; i < den_G_R_size + den_G_S_size - 1; i++)
    {
        printf("%f ", den_G0[i]);
    }
    printf("\n");

    // Frequenzbereich
    int N = 1000;
    double w[N];
    for (int i = 0; i < N; ++i)
    {
        w[i] = pow(10, -2 + 6.0 * i / (N - 1));
    }

    // Bode-Diagramm berechnen
    double mag[N], phase[N];
    for (int i = 0; i < N; ++i)
    {
        complex double s = I * w[i];
        complex double G0_val = polyval(num_G0, num_G_R_size + num_G_S_size - 1, s) / polyval(den_G0, den_G_R_size + den_G_S_size - 1, s);
        mag[i] = 20 * log10(cabs(G0_val));
        phase[i] = carg(G0_val) * 180 / M_PI;
    }

    // Daten in Datei schreiben für gnuplot
    FILE *mag_file = fopen("magnitude.dat", "w");
    FILE *phase_file = fopen("phase.dat", "w");
    for (int i = 0; i < N; ++i)
    {
        fprintf(mag_file, "%f %f\n", w[i], mag[i]);
        fprintf(phase_file, "%f %f\n", w[i], phase[i]);
    }
    fclose(mag_file);
    fclose(phase_file);

    // gnuplot Skript
    FILE *gnuplot_script = fopen("plot_bode.gnu", "w");
    fprintf(gnuplot_script, "set terminal pngcairo size 2500,1750\n");
    fprintf(gnuplot_script, "set output 'bode_plot.png'\n");
    fprintf(gnuplot_script, "set grid xtics mxtics \n");
    fprintf(gnuplot_script, "set mxtics 10 \n");
    fprintf(gnuplot_script, "set logscale x \n");
    fprintf(gnuplot_script, "set grid ytics mytics \n");
    fprintf(gnuplot_script, "set mytics 5 \n");
    fprintf(gnuplot_script, "set grid\n\n");
    fprintf(gnuplot_script, "set multiplot layout 2,1 title 'Bode-Diagramm'\n\n");
    fprintf(gnuplot_script, "#Magnitude plot\n");
    fprintf(gnuplot_script, "set xlabel 'Frequency (rad/s)'\n");
    fprintf(gnuplot_script, "set xrange [1e-2:1e4]\n");
    fprintf(gnuplot_script, "set ylabel 'Magnitude (dB)'\n");
    fprintf(gnuplot_script, "plot 'magnitude.dat' with lines title 'Magnitude' lt rgb 'blue' lw 3\n\n");
    fprintf(gnuplot_script, "#Phase plot\n");
    fprintf(gnuplot_script, "set xlabel 'Frequency (rad/s)'\n");
    fprintf(gnuplot_script, "set xrange [1e-2:1e4]\n");
    fprintf(gnuplot_script, "set ylabel 'Phase (degrees)'\n");
    //fprintf(gnuplot_script, "set yrange [-300:0]\n");
    fprintf(gnuplot_script, "plot 'phase.dat' with lines title 'Phase' lt rgb 'green' lw 3\n");
    fprintf(gnuplot_script, "unset multiplot\n");

    fclose(gnuplot_script);

    // gnuplot aufrufen
    system("gnuplot plot_bode.gnu");

    return 0;
}
