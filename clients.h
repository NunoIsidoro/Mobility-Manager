/**
 * @file   clients.h
 * @brief  This file includes functions and data types related to the client system.
 * @author Nuno Fernandes
 * @date   March 2023
 */

#ifndef CLIENTS_H
#define CLIENTS_H

#pragma once
#pragma warning(disable:4996)

#include "headers.h"

#define NIF_SIZE 10  /**< NIF size constant. */

 /**
  * @brief Struct that represents a client.
  */
typedef struct Client {
	char nif[NIF_SIZE];               /**< Client's NIF. */
	double balance;                   /**< Client's balance. */
	char name[MIN_LENGHT];            /**< Client's name. */
	char address[MAX_LENGHT];         /**< Client's address. */
} Client;

/**
 * @brief Node for linked list of Client struct.
 */
typedef struct ClientNode {
	Client client;                    /**< Client data for the node. */
	struct ClientNode* next;          /**< Pointer to the next node in the list. */
} ClientNode;

/**
 * @brief Adds a new client node to the list.
 *
 * @param head The head of the list.
 * @param newClient The new Client data to be added.
 * @return A pointer to the new head of the list.
 */
ClientNode* AddClient(ClientNode* head, Client newClient);

/**
 * @brief Sorts the client nodes in the list.
 *
 * @param head The head of the list.
 * @return A pointer to the new head of the sorted list.
 */
ClientNode* SortClients(ClientNode* head);

/**
 * @brief Loads client data from a text file into a linked list.
 *
 * @param filename The name of the text file.
 * @return A pointer to the head of the created list.
 */
ClientNode* LoadClientsFromTextFile(const char* filename);

/**
 * @brief Loads client data from a binary file into a linked list.
 *
 * @param filename The name of the binary file.
 * @return A pointer to the head of the created list.
 */
ClientNode* LoadClientsFromBinaryFile(const char* filename);

/**
 * @brief Loads client data either from a binary or a text file into a linked list.
 *
 * @param binFilename The name of the binary file.
 * @param txtFilename The name of the text file.
 * @return A pointer to the head of the created list.
 */
ClientNode* LoadClients(const char* binFilename, const char* txtFilename);

/**
 * @brief Frees all the memory allocated for the linked list of Client.
 *
 * @param head The head of the list.
 */
void FreeClients(ClientNode* head);

/**
 * @brief Deletes a client node from the list.
 *
 * @param head The head of the list.
 * @param nif The NIF of the Client data to be deleted.
 * @return A pointer to the new head of the list.
 */
ClientNode* DeleteClient(ClientNode* head, char* nif);

/**
 * @brief Updates a client node in the list.
 *
 * @param head The head of the list.
 * @param nif The NIF of the Client data to be updated.
 * @param updatedClient The updated Client data.
 */
void UpdateClient(ClientNode* head, char* nif, Client updatedClient);

/**
 * @brief Finds a client node in the list by its NIF.
 *
 * @param head The head of the list.
 * @param nif The NIF of the Client data to be found.
 * @return A pointer to the found Client node. If not found, returns NULL.
 */
ClientNode* FindClientByNif(ClientNode* head, char* nif);

/**
 * @brief Displays the client menu.
 *
 * @param clients The list of clients.
 * @param loggedClient The client that is currently logged in.
 * @param binFilename The name of the binary file.
 */
void ClientMenu(ClientNode* clients, ClientNode** loggedClient, const char* binFilename);

/**
 * @brief Prints the information of a specific client.
 *
 * @param client The client whose information will be printed.
 */
void PrintClientInfo(ClientNode** client);

/**
 * @brief Prints the information of all clients in the list.
 *
 * @param head The head of the list.
 */
void PrintAllClients(ClientNode* head);

/**
 * @brief Updates the information of a specific client.
 *
 * @param loggedClient The client whose information will be updated.
 * @param head The head of the list.
 * @param binFilename The name of the binary file.
 */
void UpdateClientInfo(ClientNode** loggedClient, ClientNode* head, const char* binFilename);

#endif  // CLIENTS_H
