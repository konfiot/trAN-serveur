#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "transmission.h"
#include "divers.h"

int main (int argc, char *argv[]){
	char ok = 0;
	int dossier_fichier;

	SOCKET sock;
	SOCKADDR_IN sin;
	socklen_t taille = sizeof(sin);

	SOCKET csock;
	SOCKADDR_IN csin;
	socklen_t ctaille = sizeof(csin);

	SOCKET csock2;
	SOCKADDR_IN csin2;
	socklen_t ctaille2 = sizeof(csin2);

	initSocket(&sock, &sin, taille, 2500, SERVEUR, NULL);

	csock = accept(sock, (SOCKADDR*)&csin, &ctaille);
	printf("socket serveur connectee\n");
	csock2 = accept(sock, (SOCKADDR*)&csin2, &ctaille2);
	printf("socket client connectee\n");
		
	if (csock == SOCKET_ERROR || csock2 == SOCKET_ERROR){
		printf("erreur a la connexion d'une des sockets");
	} else {
		printf("Les deux sockets se sont connectees avec succes"); 
	}

	send(csock, &ok, sizeof(char), 0);
	send(csock2, &ok, sizeof(char), 0);

	if (recv(csock, (char*)&dossier_fichier, sizeof(int), 0) != SOCKET_ERROR){
		printf("dossier_fichier recu avec succes (en principe)");
	} else {
		printf("Probleme a la reception de la variable dossier_fichier");
	}

	printf("dossier_fichier : %d", (int)ntohl(dossier_fichier));
        send(csock2, (char*)&dossier_fichier, sizeof(int), 0);

        if (ntohl(dossier_fichier)){
            transmission(csock, csock2);
        } else {
            dtransmission(csock, csock2);
        }
        
        shutdown(csock, 2);
        shutdown(csock2, 2);
        
        closesocket(csock);
        closesocket(csock2);
        
#ifdef WIN32
        WSACleanup();
#endif
        
        return EXIT_SUCCESS;
}