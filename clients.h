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
ClientNode *create_client(const char *nif, double balance, const char *name, const char *address);

// Adds a new client to the clients list.
// clients: a pointer to the clients list
// new_client: a pointer to the client to be added
// Returns 0 on success or -1 on failure.
int add_client(ClientNode **clients, ClientNode *new_client);

// Removes a client from the clients list based on the provided NIF.
// clients: a pointer to the clients list
// nif: the NIF of the client to be removed
// Returns 0 on success or -1 on failure.
int remove_client(ClientNode **clients, const char *nif);

// Finds a client in the clients list based on the provided NIF.
// clients: the clients list
// nif: the NIF of the client to be found
// Returns a pointer to the found client or NULL if not found.
ClientNode *find_client(ClientNode *clients, const char *nif);

// Deletes the entire clients list and frees the memory.
// clients: the clients list to be deleted
void delete_client_list(ClientNode *clients);

// Saves the clients list to a binary file.
// clients: the clients list to be saved
// Returns 0 on success or -1 on failure.
int save_clients_to_binary_file(ClientNode *clients);

// Loads the clients list from a binary file.
// Returns a pointer to the loaded clients list or NULL if not found.
ClientNode *load_clients_from_binary_file(ClientNode **existing_clients);

// Saves the clients list to a text file.
// clients: the clients list to be saved
// Returns 0 on success or -1 on failure.
int save_clients_to_text_file(ClientNode *clients);

// Loads the clients list from a text file.
// Returns a pointer to the loaded clients list or NULL if not found.
ClientNode *load_clients_from_text_file(ClientNode **existing_clients);

#endif  // CLIENTS_H

