#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "transmission.h"
#include "divers.h"
#include "multithreading.h"

int main (int argc, char *argv[]){
	char ok = 0;
	int dossier_fichier;
        
        CoupleClients clients;

	SOCKET sock;
	SOCKADDR_IN sin;
	socklen_t taille = sizeof(sin);

	SOCKADDR_IN csin;
	socklen_t ctaille = sizeof(csin);

	SOCKADDR_IN csin2;
	socklen_t ctaille2 = sizeof(csin2);

	initSocket(&sock, &sin, taille, 2500, SERVEUR, NULL);

	clients.csock = accept(sock, (SOCKADDR*)&csin, &ctaille);
	printf("socket serveur connectee\n");
	clients.csock2 = accept(sock, (SOCKADDR*)&csin2, &ctaille2);
	printf("socket client connectee\n");
		
	if (clients.csock == SOCKET_ERROR || clients.csock2 == SOCKET_ERROR){
		printf("erreur a la connexion d'une des sockets");
	} else {
		printf("Les deux sockets se sont connectees avec succes"); 
	}

	send(clients.csock, &ok, sizeof(char), 0);
	send(clients.csock2, &ok, sizeof(char), 0);

	if (recv(clients.csock, (char*)&dossier_fichier, sizeof(int), 0) != SOCKET_ERROR){
		printf("dossier_fichier recu avec succes (en principe)");
	} else {
		printf("Probleme a la reception de la variable dossier_fichier");
	}

	printf("dossier_fichier : %d", (int)ntohl(dossier_fichier));
        send(clients.csock2, (char*)&dossier_fichier, sizeof(int), 0);

        gestionClients(clients);
        
        shutdown(clients.csock, 2);
        shutdown(clients.csock2, 2);
        
        closesocket(clients.csock);
        closesocket(clients.csock2);
        
#ifdef WIN32
        WSACleanup();
#endif
        
        return EXIT_SUCCESS;
}