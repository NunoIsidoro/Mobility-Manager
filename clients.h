/*****************************************************************//**
 * \file   clients.h
 * \brief  Header file for client-related functions.
 * 
 * \author Nuno Fernandes
 * \date   March 2023
 *********************************************************************/
#ifndef CLIENTS_H
#define CLIENTS_H

#include "headers.h"

typedef struct Client {
	char nif[10];
	double balance;
	char *name;
	char *address;
} Client;

typedef struct ClientNode {
	Client client;
	struct ClientNode *next;
} ClientNode;


ClientNode *CreateClient(const char *nif, double balance, const char *name, const char *address);
int AddClient(ClientNode **clients, ClientNode *new_client);
int RemoveClient(ClientNode **clients, const char *nif);
ClientNode *FindClient(ClientNode *clients, const char *nif);
void DeleteClientList(ClientNode *clients);
int SaveClientsToBinaryFile(ClientNode *clients);
ClientNode *LoadClientsFromBinaryFile(ClientNode **existing_clients);
int SaveClientsToTextFile(ClientNode *clients);
ClientNode *LoadClientsFromTextFile(ClientNode **existing_clients);

#endif  // CLIENTS_H

