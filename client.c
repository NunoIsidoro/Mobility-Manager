// clients.c
#include "clients.h"

#define BIN_FILENAME "Data/clients.bin"
#define TXT_FILENAME "Data/clients.txt"
#define MAX_LINE_LEN 1024

ClientNode *create_client(const char *nif, double balance, const char *name, const char *address) {
	ClientNode *new_client = (ClientNode *) malloc(sizeof(ClientNode));
	if (!new_client) {
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}

	strncpy_s(new_client->client.nif, 10, nif, _TRUNCATE);
	new_client->client.balance = balance;
	new_client->client.name = _strdup(name);
	 if (!new_client->client.name) {
		printf("Error: Memory allocation failed for name.\n");
		free(new_client);
		exit(1);
	}
	new_client->client.address = _strdup(address);
	 if (!new_client->client.address) {
		printf("Error: Memory allocation failed for address.\n");
		free(new_client->client.name);
		free(new_client);
		exit(1);
	}
	new_client->next = NULL;

	return new_client;
}


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

ClientNode *load_clients_from_binary_file() {
	FILE *fp;
	errno_t err = fopen_s(&fp, BIN_FILENAME, "rb");

	if (err) {
		printf("Warning: Binary file not found. Attempting to load from text file.\n");
		return load_clients_from_text_file();
	}

	ClientNode *clients = NULL;

	// Verificar se o arquivo não está vazio
	fseek(fp, 0L, SEEK_END);
	int file_size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	if (file_size == 0) {
		fclose(fp);
		return load_clients_from_text_file();
	}

	// Ler os dados do arquivo e adicionar à lista encadeada
	Client client;
	while (fread(&client, sizeof(Client), 1, fp)) {
		ClientNode *new_node = create_client(client.nif, client.balance, client.name, client.address);
		add_client(&clients, new_node);
	}

	fclose(fp);
	return clients;
}


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


ClientNode *load_clients_from_text_file() {
	FILE *fp;
	errno_t err = fopen_s(&fp, TXT_FILENAME, "r");
	if (err) {
		printf("Error: Text file not found.\n");
		return NULL;
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
	save_clients_to_binary_file(clients); // Salvar os clientes em um arquivo binário
	return clients;
}