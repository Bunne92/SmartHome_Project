#include "udp_server.h"

#define BUFLEN 512  // Buffer längd
#define PORT 8888   // Port för inkommande data


int main(void) {

  struct udp server = create_udp_server(PORT);
  struct sockaddr_in clients;
  int slen = sizeof(clients) , recv_len;
  char buf[BUFLEN];

  // Sensor dataparametrar
  char *snr, *sd;

  // Filhanterings parametrar
  FILE *fp1, *fp2;

  char *getElementFromChar(char *theString, int number) {
      char *token;
      const char s[2] = " ";
      token = strtok(theString, s);
      for(int i = 0; i < number; i++) {
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
      printf("Data: %s\n" , buf);

      snr = getElementFromChar(buf, 0);
      sd = getElementFromChar(buf, 1);
      printf("\nsnr: %d   sd: %d\n", snr, sd);

      if(snr == "1") {
          fp1 = fopen("/var/www/html/sensor1.txt", "w");
          fprintf(fp1, "%d", sd);
          fprintf(fp1, "%s", "\n");
          fclose(fp1);
      } else if(snr == "2") {
          fp2 = fopen("/var/www/html/sensor2.txt", "w");
          fprintf(fp2, "%d", sd);
          fprintf(fp2, "%s", "\n");
          fclose(fp2);
      }

  }

  // Stäng ner socketen.
  close(server.s_descriptor);

  return 0;
}
