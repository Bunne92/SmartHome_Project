#include "udp_server.h"

#define BUFLEN 512  // Buffer längd
#define PORT 8888   // Port för inkommande data

int main(void) {

  struct udp server = create_udp_server(PORT);
  struct sockaddr_in clients;
  int slen = sizeof(clients) , recv_len;
  char buf[BUFLEN];

  while(1)
  {
      printf("Waiting for data...");
      fflush(stdout);

      //try to receive some data, this is a blocking call
      if ((recv_len = recvfrom(server.s_descriptor, buf, BUFLEN, 0, (struct sockaddr *) &clients, &slen)) == -1)
      {
          kill_prog("recvfrom()");
      }

      //print details of the client/peer and the data received
      printf("Received packet from %s:%d\n", inet_ntoa(clients.sin_addr), ntohs(clients.sin_port));
      printf("Data: %s\n" , buf);

      // //now reply the client with the same data
      // if (sendto(server.s_descriptor, buf, recv_len, 0, (struct sockaddr*) &clients, slen) == -1)
      // {
      //     kill_prog("sendto()");
      // }

  }

  // Stäng ner socketen.
  close(server);

  return 0;
}
