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

	
// Creates a new client and returns a pointer to it.
// nif: NIF string (up to 9 characters)
// balance: client's balance
// name: client's name
// address: client's address
ClientNode *CreateClient(const char *nif, double balance, const char *name, const char *address);

// Adds a new client to the clients list.
// clients: a pointer to the clients list
// new_client: a pointer to the client to be added
// Returns 0 on success or -1 on failure.
int AddClient(ClientNode **clients, ClientNode *new_client);

// Removes a client from the clients list based on the provided NIF.
// clients: a pointer to the clients list
// nif: the NIF of the client to be removed
// Returns 0 on success or -1 on failure.
int RemoveClient(ClientNode **clients, const char *nif);

// Finds a client in the clients list based on the provided NIF.
// clients: the clients list
// nif: the NIF of the client to be found
// Returns a pointer to the found client or NULL if not found.
ClientNode *FindClient(ClientNode *clients, const char *nif);

// Deletes the entire clients list and frees the memory.
// clients: the clients list to be deleted
void DeleteClientList(ClientNode *clients);

// Saves the clients list to a binary file.
// clients: the clients list to be saved
// Returns 0 on success or -1 on failure.
int SaveClientsToBinaryFile(ClientNode *clients);

// Loads the clients list from a binary file.
// Returns a pointer to the loaded clients list or NULL if not found.
ClientNode *LoadClientsFromBinaryFile(ClientNode **existing_clients);

// Saves the clients list to a text file.
// clients: the clients list to be saved
// Returns 0 on success or -1 on failure.
int SaveClientsToTextFile(ClientNode *clients);

// Loads the clients list from a text file.
// Returns a pointer to the loaded clients list or NULL if not found.
ClientNode *LoadClientsFromTextFile(ClientNode **existing_clients);

#endif  // CLIENTS_H

