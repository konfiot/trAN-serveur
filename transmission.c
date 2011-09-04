#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "divers.h"
#define TAILLE_BUFFER 1024


void transmission(SOCKET csock, SOCKET csock2){
	int temp_taille_nom, taille_nom, temp_test_fin, test_fin;
	char *nom_fichier = NULL, fin;
	void *buffer = malloc(1024);

	puts("in transmission");
	if (recv(csock, (char*)&temp_taille_nom, sizeof(int), 0) == SOCKET_ERROR)
		printf("temp_taille_nom error");

	taille_nom = ntohl(temp_taille_nom);
	printf("taile_nom : %d\n", taille_nom);
	nom_fichier = malloc(taille_nom);
	if (recv(csock, nom_fichier, taille_nom * sizeof(char), 0) == SOCKET_ERROR)
		printf("temp_taille_nom error");

	printf("nom : %s\n", nom_fichier);

	send(csock2, (char*)&temp_taille_nom, sizeof(int), 0);
	send(csock2, nom_fichier, taille_nom * sizeof(char), 0);
	
	recv(csock2, &fin, sizeof(char), 0);
	send(csock, &fin, sizeof(char), 0);

	do {
		recv(csock, (char*)&temp_test_fin, sizeof(int), 0);
		recv(csock, (char*)buffer, 1024, 0);
		test_fin = ntohl(temp_test_fin);

		send(csock2, (char*)&temp_test_fin, sizeof(int), 0);
		send(csock2, (char*)buffer, 1024, 0);
		
		recv(csock2, &fin, sizeof(char), 0);
		send(csock, &fin, sizeof(char), 0);
	} while (test_fin == 1024);
}


void dtransmission(SOCKET csock, SOCKET csock2){

    int net_taille_chaine, nb_fichiers, net_nb_fichiers, taille_chaine, dossier_fichier, i;
    char *nom_fichier = NULL;
    
    
    recv(csock, &net_nb_fichiers, sizeof(int), 0);
    nb_fichiers = ntohl(net_nb_fichiers);
    
    for (i = 1 ; i < nb_fichiers ; i++){
        recv(csock, &net_taille_chaine, sizeof(int), 0);    
        taille_chaine = ntohl(net_taille_chaine);
        nom_fichier = malloc(taille_chaine);
        recv(csock, nom_fichier, taille_chaine, 0);
        
        recv(csock, &dossier_fichier, sizeof(int), 0);
        
        if (dossier_fichier){
            transmission(csock, csock2);
        }
    }
}
