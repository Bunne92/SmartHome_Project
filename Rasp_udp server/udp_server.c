/*
    udp server (Linux)
*/
#include "udp_server.h"

/*
    Funktion för att avsluta programmet om något blir fel.
*/
void kill_prog(char *s)
{
    perror(s);
    exit(1);
}

/*
    Funktion som returnerar en UDP-socket server objekt
 */
struct udp create_udp_server(int PORT) {

    /*
        Skapa ett objekt som lagrar
        -File descriptor för socket.
        -sockaddr_in objekt
    */
    struct udp server;

    /*
        Skapa en socket för en udp-server.
    */
    int  descriptor;
    if((descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
       // Om fel uppstod vid skapandet, avlsuta programmet.
      kill_prog("UDP SERVER");
    }

    // Lagra undan vårt objekt
    server.s_descriptor = descriptor;

    /*
        Skapa ett sockaddr_in objekt (en IPv4 Socket Adressstruktur ).
     */
    struct sockaddr_in sa;
    // Nollställ eventuella förinställda inställningar i objektet
    memset((char *) &sa, 0, sizeof(sa));
    // Ställ om inställningarna
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY (UDP)

    /*
        Associera socketen med Adressstrukturen.
        "Most socket functions require a pointer to a socket address structure as an argument."
    */
    if( bind(descriptor , (struct sockaddr*)&sa, sizeof(sa) ) == -1)
    {
        kill_prog("bind UDP SERVER");
    }

    // Lagra undan i vårt objekt
    server.bonding = sa;

    // Returnera objektet
    return server;
}
