#ifndef UDPSERVER
#define UDPSERVER

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include <fcntl.h> // for open
#include <unistd.h> // for close

struct udp {
    int s_descriptor;
    struct sockaddr_in bonding;
};

void kill_prog(char *);

struct udp create_udp_server(int);

#endif // UDPSERVER
