// clients.c
#include "clients.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BIN_FILENAME "Data/clients.bin"
#define TXT_FILENAME "Data/clients.txt"
#define MAX_LINE_LEN 1024

/**
 * \brief Creates a new client node and initializes its fields
 *
 * This function creates a new ClientNode object, allocates memory for it, and initializes
 * its fields with the given parameters. If memory allocation fails at any point, the
 * function prints an error message and exits the program.
 *
 * \param nif A string representing the client's tax identification number (NIF)
 * \param balance A double representing the client's initial account balance
 * \param name A string representing the client's name
 * \param address A string representing the client's address
 * \return A pointer to the newly created ClientNode object
 * \author Nuno Fernandes
 */
ClientNode *create_client(const char *nif, double balance, const char *name, const char *address) {
	ClientNode *new_client = (ClientNode *) malloc(sizeof(ClientNode));
	if (!new_client) {
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}

	strncpy_s(new_client->client.nif, 10, nif, _TRUNCATE);
	new_client->client.balance = balance;
	
	new_client->client.name = _strdup(name);
	
	new_client->client.address = _strdup(address);
	 
	new_client->next = NULL;

	return new_client;
}

/**
 * \brief Adds a new client node to the client list and saves the list to a binary file
 *
 * This function takes a pointer to a ClientNode pointer (representing the head of the list) and a new
 * ClientNode object to be added. It adds the new client node to the end of the list, then saves the
 * updated list to a binary file. If an error occurs while saving the list to the binary file, an error
 * message is printed and the function returns -1.
 *
 * \param clients A double pointer to the head of the client list
 * \param new_client A pointer to the new ClientNode object to be added to the list
 * \return 0 on successful addition and saving, -1 if an error occurs while saving to the binary file
 * \author Nuno Fernandes
 */
int add_client(ClientNode **clients, ClientNode *new_client) {

	if (!*clients) {
		*clients = new_client;
	} else {
		ClientNode *current = *clients;
		while (current->next) {
			current = current->next;
		}
		current->next = new_client;
	}

	if (save_clients_to_binary_file(*clients) != 0) {
		printf("Error: Failed to save clients to binary file.\n");
		return -1;
	}

	return 0;
}

/**
 * \brief Removes a client node from the client list based on the NIF and saves the list to a binary file
 *
 * This function searches for a client node in the list with the specified NIF, removes it from the list,
 * and saves the updated list to a binary file. If the list is empty, the function returns -1. If an error
 * occurs while saving the list to the binary file, an error message is printed and the function returns -1.
 *
 * \param clients A double pointer to the head of the client list
 * \param nif A string representing the client's tax identification number (NIF) to be removed
 * \return 0 on successful removal and saving, -1 if the client is not found or an error occurs while saving to the binary file
 * \author Nuno Fernandes
 */
int remove_client(ClientNode **clients, const char *nif) {
	if (!*clients) return -1;

	ClientNode *current = *clients;
	ClientNode *prev = NULL;

	while (current) {
		if (strcmp(current->client.nif, nif) == 0) {
			if (prev) {
				prev->next = current->next;
			} else {
				*clients = current->next;
			}

			free(current->client.name);
			free(current->client.address);
			free(current);

			if (save_clients_to_binary_file(*clients) != 0) {
				printf("Error: Failed to save clients to binary file.\n");
				return -1;
			}

			return 0;
		}

		prev = current;
		current = current->next;
	}

	return -1;
}


/**
 * \brief Searches for a client node in the client list based on the NIF
 *
 * This function iterates through the client list to find a client node with the specified NIF.
 * If the client node is found, the function returns a pointer to the node. If the client node is
 * not found or the list is empty, the function returns NULL.
 *
 * \param clients A pointer to the head of the client list
 * \param nif A string representing the client's tax identification number (NIF) to search for
 * \return A pointer to the found ClientNode object if it exists, NULL if the client is not found or the list is empty
 * \author Nuno Fernandes
 */
ClientNode *find_client(ClientNode *clients, const char *nif) {
	ClientNode *current = clients;
	while (current) {
		if (strcmp(current->client.nif, nif) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

/**
 * \brief Deletes the entire client list and frees the memory
 *
 * This function iterates through the client list and deallocates memory for each client node,
 * including the name and address fields. It then sets the current node pointer to the next node
 * in the list until the entire list is deleted.
 *
 * \param clients A pointer to the head of the client list
 * \author Nuno Fernandes
 */
void delete_client_list(ClientNode *clients) {
	ClientNode *current = clients;
	ClientNode *next;

	while (current) {
		next = current->next;
		free(current->client.name);
		free(current->client.address);
		free(current);
		current = next;
	}
}

/**
 * \brief Saves the client list to a binary file
 *
 * This function opens the specified binary file for writing and saves the client list to the file.
 * It iterates through the client list, writing each client node's data to the file. If there is
 * an error opening the binary file for writing, the function prints an error message and returns -1.
 *
 * \param clients A pointer to the head of the client list
 * \return 0 on successful saving, -1 if there is an error opening the binary file for writing
 * \author Nuno Fernandes
 */
int save_clients_to_binary_file(ClientNode *clients) {
	FILE *fp;
	errno_t err = fopen_s(&fp, BIN_FILENAME, "wb");
	if (err) {
		printf("Error: Failed to open binary file for writing.\n");
		return -1;
	}


	ClientNode *current = clients;
	while (current) {
		fwrite(&current->client, sizeof(Client), 1, fp);
		current = current->next;
	}

	fclose(fp);
	return 0;
}

//ClientNode *load_clients_from_binary_file() {
//	FILE *fp;
//	errno_t err = fopen_s(&fp, BIN_FILENAME, "rb");
//
//	if (err) {
//		printf("Warning: Binary file not found. Attempting to load from text file.\n");
//		return load_clients_from_text_file();
//	}
//
//	ClientNode *clients = NULL;
//
//	// Verificar se o arquivo não está vazio
//	fseek(fp, 0L, SEEK_END);
//	int file_size = ftell(fp);
//	fseek(fp, 0L, SEEK_SET);
//	if (file_size == 0) {
//		fclose(fp);
//		return load_clients_from_text_file();
//	}
//
//	// Ler os dados do arquivo e adicionar à lista encadeada
//	Client client;
//	while (fread(&client, sizeof(Client), 1, fp)) {
//		ClientNode *new_node = create_client(client.nif, client.balance, client.name, client.address);
//		add_client(&clients, new_node);
//	}
//
//	fclose(fp);
//	return clients;
//}

/**
 * \brief Loads the client list from a binary file or falls back to a text file
 *
 * This function attempts to open the specified binary file for reading. If the file is not found,
 * it prints a warning message and attempts to load the client list from a text file. If an existing
 * client list is provided, it deletes the list before loading the new one. The function reads the
 * client data from the file and creates a new client list, adding each client node to the list.
 *
 * \param existing_clients A double pointer to the head of an existing client list, which will be deleted before loading the new list
 * \return A pointer to the head of the newly loaded client list
 * \author Nuno Fernandes
 */
ClientNode *load_clients_from_binary_file(ClientNode **existing_clients) {
	FILE *fp;
	errno_t err = fopen_s(&fp, BIN_FILENAME, "rb");

	if (err) {
		printf("Warning: Binary file not found. Attempting to load from text file.\n");
		return load_clients_from_text_file(existing_clients);
	}

	if (*existing_clients) {
		delete_client_list(*existing_clients);
	}

	ClientNode *clients = NULL;

	// Check if the file is empty
	fseek(fp, 0L, SEEK_END);
	int file_size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	if (file_size == 0) {
		fclose(fp);
		return load_clients_from_text_file(existing_clients);
	}

	// Read data from the file and add to the linked list
	Client client;
	while (fread(&client, sizeof(Client), 1, fp)) {
		ClientNode *new_node = create_client(client.nif, client.balance, client.name, client.address);
		add_client(&clients, new_node);
	}

	fclose(fp);
	return clients;
}

/**
 * \brief Saves the client list to a text file
 *
 * This function opens the specified text file for writing and saves the client list to the file.
 * It iterates through the client list, writing each client node's data to the file in a formatted
 * manner. If there is an error opening the text file for writing, the function prints an error
 * message and returns -1.
 *
 * \param clients A pointer to the head of the client list
 * \return 0 on successful saving, -1 if there is an error opening the text file for writing
 * \author Nuno Fernandes
 */
int save_clients_to_text_file(ClientNode *clients) {
	FILE *fp;
	errno_t err = fopen_s(&fp, TXT_FILENAME, "w");
	if (err) {
		printf("Error: Failed to open text file for writing.\n");
		return -1;
	}

	ClientNode *current = clients;
	while (current) {
		fprintf(fp, "%s,%.2lf,%s,%s\n", current->client.nif, current->client.balance, current->client.name, current->client.address);
		current = current->next;
	}

	fclose(fp);
	return 0;
}


//ClientNode *load_clients_from_text_file() {
//	FILE *fp;
//	errno_t err = fopen_s(&fp, TXT_FILENAME, "r");
//	if (err) {
//		printf("Error: Text file not found.\n");
//		return NULL;
//	}
//
//	ClientNode *clients = NULL;
//	char buffer[MAX_LINE_LEN];
//
//	while (fgets(buffer, MAX_LINE_LEN, fp)) {
//		char *context = NULL;
//		char *nif_str = strtok_s(buffer, ",", &context);
//		char *balance_str = strtok_s(NULL, ",", &context);
//		char *name = strtok_s(NULL, ",", &context);
//		char *address = strtok_s(NULL, ",", &context);
//		if (nif_str && balance_str && name && address) {
//			double balance = atof(balance_str);
//			ClientNode *new_node = create_client(nif_str, balance, name, address);
//			add_client(&clients, new_node);
//		}
//	}
//
//	fclose(fp);
//	save_clients_to_binary_file(clients); // Salvar os clientes em um arquivo binário
//	return clients;
//}

/**
 * \brief Loads the client list from a text file
 *
 * This function opens the specified text file for reading and loads the client list from the file.
 * If an existing client list is provided, it deletes the list before loading the new one. The function
 * reads the client data from the file and creates a new client list, adding each client node to the list.
 * After loading the clients, it also saves the client list to a binary file.
 *
 * \param existing_clients A double pointer to the head of an existing client list, which will be deleted before loading the new list
 * \return A pointer to the head of the newly loaded client list
 * \author Nuno Fernandes
 */
ClientNode *load_clients_from_text_file(ClientNode **existing_clients) {
	FILE *fp;
	errno_t err = fopen_s(&fp, TXT_FILENAME, "r");
	if (err) {
		printf("Error: Text file not found.\n");
		return NULL;
	}

	if (*existing_clients) {
		delete_client_list(*existing_clients);
	}

	ClientNode *clients = NULL;
	char buffer[MAX_LINE_LEN];

	while (fgets(buffer, MAX_LINE_LEN, fp)) {
		char *context = NULL;
		char *nif_str = strtok_s(buffer, ",", &context);
		char *balance_str = strtok_s(NULL, ",", &context);
		char *name = strtok_s(NULL, ",", &context);
		char *address = strtok_s(NULL, ",", &context);
		if (nif_str && balance_str && name && address) {
			double balance = atof(balance_str);
			ClientNode *new_node = create_client(nif_str, balance, name, address);
			add_client(&clients, new_node);
		}
	}

	fclose(fp);
	save_clients_to_binary_file(clients); // Save clients to a binary file
	return clients;
}
