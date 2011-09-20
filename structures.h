/* 
 * File:   structures.h
 * Author: TOUSSAINT
 *
 * Created on 19 septembre 2011, 08:19
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "socket.h"

typedef struct {
    SOCKET csock;
    SOCKET csock2;
    int dossier_fichier;
} CoupleClients;

#ifdef	__cplusplus
}
#endif

#endif	/* STRUCTURES_H */

