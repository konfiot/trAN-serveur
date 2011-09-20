#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "transmission.h"

int gestionClients(CoupleClients clients){
    if (clients.dossier_fichier){
        transmission(clients.csock, clients.csock2);
    } else {
        dtransmission(clients.csock, clients.csock2);
    }
}
