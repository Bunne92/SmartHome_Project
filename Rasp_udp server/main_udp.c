#include "udp_server.h"

#define BUFLEN 512  // Buffer längd
#define PORT 8888   // Port för inkommande data


int main(void) {

  struct udp server = create_udp_server(PORT);
  struct sockaddr_in clients;
  int slen = sizeof(clients) , recv_len;
  char buf[BUFLEN];

  // Sensor dataparametrar
  char *sensor_number, *sensor_data;
  // int snr, sd;

  // Filhanterings parametrar
  FILE *fp1, *fp2;

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

      if(strcmp(sensor_number, "1") == 0) {
          fp1 = fopen("sensor1.txt", "a");
          fprintf(fp1, "%s\n", sensor_data);
          //fprintf(fp1, "%s", "\n");
          fclose(fp1);
      } else if(strcmp(sensor_number, "2") == 0) {
          fp2 = fopen("sensor2.txt", "a");
          fprintf(fp2, "%s\n", sensor_data);
          //fprintf(fp2, "%s", "\n");
          fclose(fp2);
      }

  }

  // Stäng ner socketen.
  close(server.s_descriptor);

  return 0;
}
