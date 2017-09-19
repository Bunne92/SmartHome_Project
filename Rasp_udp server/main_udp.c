#include "udp_server.h"
#include "mean.h"
#include <time.h>

#define BUFLEN 512  // Buffer längd
#define PORT 8888   // Port för inkommande data


int main(void) {

  struct udp server = create_udp_server(PORT);
  struct sockaddr_in clients;
  int slen = sizeof(clients) , recv_len;
  char buf[BUFLEN];

  // Sensor dataparametrar
  char *sensor_number, *sensor_data;

  // Filhanterings parametrar
  FILE *fp, *fp_latest, *fp_mean;

  // Beräkna medelvärdet efter denna "tid"
  int mean_time = 6;

  // Funktion för att plocka ut ett specifikt ord i en sträng
  char *getElementFromChar(char *theString, int nr) {
      char *token;
      const char s[2] = " ";

      token = strtok(theString, s);
      int i;
      for(i = 0; i < nr; i++) {
          token = strtok(NULL, s);
      }
      return token;
  }


  // Lagra undan position i filen
  int sense1_txt_pos = 0, sense2_txt_pos = 0;
  char sensor1_time_stamp1[80], sensor2_time_stamp1[80];
  int cntr1 = 0, cntr2 = 0;
  while(1)
  {
      printf("Waiting for data...");
      fflush(stdout);
      memset(buf, 0, BUFLEN);

      //try to receive some data, this is a blocking call
      if ((recv_len = recvfrom(server.s_descriptor, buf, BUFLEN, 0, (struct sockaddr *) &clients, &slen)) == -1)
      {
          kill_prog("recvfrom()");
      }

      //print details of the client/peer and the data received
      printf("Received packet from %s:%d\n", inet_ntoa(clients.sin_addr), ntohs(clients.sin_port));
    //  printf("Data: %s\n" , buf);

      sensor_data = getElementFromChar(buf, 1);
      //printf("I bufferten finns nu: %s\n", buf);
      sensor_number = getElementFromChar(buf, 0);

      printf("snr: %s   sd: %s\n", sensor_number, sensor_data);

      // Ta tiden
      time_t t = time(NULL);
      struct tm *tm = localtime(&t);

      if(strcmp(sensor_number, "1") == 0) {
          cntr1++;
          if(cntr1 == 1) {
              strftime(sensor1_time_stamp1, 80, "%Y-%m-%d %H:%M:%S", tm);
          }

          fp = fopen("sensor1.txt", "a");
          fprintf(fp, "%s %d-%d-%d %d:%d:%d\n",
           sensor_data, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
          fclose(fp);

          if (cntr1 == mean_time) {
              fp_mean = fopen("sensor1.txt", "a+");
              mean(&fp_mean, 1, &sense1_txt_pos, sensor1_time_stamp1);
              fclose(fp_mean);
              cntr1 = 0;
          }


          // Spara undan i filen som endast visar senaste värdet
          fp_latest = fopen("sensor1_latest.txt", "w");
          fprintf(fp_latest, "%s    %d-%d-%d %d:%d:%d",
           sensor_data,  tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
          fclose(fp_latest);

      } else if(strcmp(sensor_number, "2") == 0) {
          cntr2++;
          if(cntr2 == 1) {
              strftime(sensor2_time_stamp1, 80, "%Y-%m-%d %H:%M:%S", tm);
          }

          fp = fopen("sensor2.txt", "a");
          fprintf(fp, "%s %d-%d-%d %d:%d:%d\n",
           sensor_data,  tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
          fclose(fp);

          if(cntr2 == mean_time) {
              fp_mean = fopen("sensor2.txt", "a+");
              mean(&fp_mean, 2, &sense2_txt_pos, sensor2_time_stamp1);
              fclose(fp_mean);
              cntr2 = 0;
          }


          // Spara undan i filen som endast visar senaste värdet
          fp_latest = fopen("sensor2_latest.txt", "w");
          fprintf(fp_latest, "%s %d-%d-%d %d:%d:%d",
           sensor_data,  tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
          fclose(fp_latest);
      }

  }

  // Stäng ner socketen.
  close(server.s_descriptor);

  return 0;
}
