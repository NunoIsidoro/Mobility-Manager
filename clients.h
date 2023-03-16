/*****************************************************************//**
 * \file   clients.h
 * \brief  
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

ClientNode *create_client(const char *nif, double balance, const char *name, const char *address);
int add_client(ClientNode **clients, ClientNode *new_client);
int remove_client(ClientNode **clients, const char *nif);
ClientNode *find_client(ClientNode *clients, const char *nif);
void delete_client_list(ClientNode *clients);
int save_clients_to_binary_file(ClientNode *clients);
ClientNode *load_clients_from_binary_file();
int save_clients_to_text_file(ClientNode *clients);
ClientNode *load_clients_from_text_file();

#endif  // CLIENTS_H
