/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Type definition
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef HARDWARE_H
#define HARDWARE_H

#include "TypeDefs.h"

#define ReaderTCP               1                            /**< Parametre pour utiliser un lecteur TCP/IP. */
#define ReaderCDC               2                            /**< Parametre pour utiliser un lecteur USB. */
#define ReaderPCSC              3                            /**< Parametre pour utiliser un lecteur PC/SC. */

#define DataMem                 512                         /**< Taille memoire. */

#define MAX_WAIT_READ_TO_BIT    1                           /**< temps max d'attente pour lecture (en ms). */
#define MAX_WAIT_READ           3000                        /**< temps max d'attente pour lecture (en ms). */

#define BlockingEnabled         FALSE                       /**< Utilisation des sockets bloquantes. */


/**
* \struct ReaderName
* \brief Objet contenant les informations du Reader
*
*/

typedef struct {
    uint8_t Type;			/*!< Type de peripherique */
    uint8_t device;			/*!< Port COM du peripherique */
    char IPReader[16];		/*!< Adresse IP du peripherique */
    SOCKET hSocket;         /*!< Information sur la socket */
    HANDLE g_hCOM;          /*!< Information sur le port COM */
    char version[40];       /*!< Version */
    uint8_t serial[11];     /*!< Numero de serie */
    char stack[30];         /*!< Pile logiciel */
}
ReaderName;

#endif /*HARDWARE_H*/
