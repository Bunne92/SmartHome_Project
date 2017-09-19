#include "mean.h"

void mean(FILE **fp, int sensor, int *pos, char *first_time) {

  printf("Inside mean-file.\n");

  char line[4096], mean[20], *str;
  double d, n_val = 0, sum = 0;

  fseek(*fp, *pos, SEEK_SET); // Sätt filpekarn på rätt position
  while (fgets(line, sizeof(line), *fp) != 0)
  {
    d = strtod(line, &str);
    sum = sum + d;
    n_val++;
  }

  // Lagra filpekarens position.
  *pos = ftell(*fp);

  // Lagra medelvärde i textfil
  double medel = sum/n_val;
  printf("Sum: %g Medel: %g\n", sum, medel);
  ftoa(medel, mean, 3);
  //printf("Medel: %s\n", medel);

  FILE *fp_mean;
  if (sensor == 1) {
      fp_mean = fopen("sensor1_mean.txt", "a");
      fprintf(fp_mean, "%s  %s%s\n", mean, first_time, str);
  } else if (sensor == 2) {
      fp_mean = fopen("sensor2_mean.txt", "a");
      fprintf(fp_mean, "%s  %s%s\n", mean, first_time, str);
  }

  fclose(fp_mean);

}
