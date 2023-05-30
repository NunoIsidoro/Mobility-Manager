// clients.c
#include "clients.h"

#define MAX_LINE_LENGTH 256

ClientNode* AddClient(ClientNode* head, Client newClient) {
	ClientNode* newNode = (ClientNode*)malloc(sizeof(ClientNode));
	newNode->client = newClient;
	newNode->next = NULL;

	if (head == NULL || strcmp(newClient.name, head->client.name) < 0) {
		newNode->next = head;
		head = newNode;
	}
	else {
		ClientNode* current = head;
		while (current->next != NULL && strcmp(newClient.name, current->next->client.name) > 0) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}

	return head;
}

/**/
ClientNode* SortClients(ClientNode* head) {
	ClientNode* sorted = NULL;
	ClientNode* current = head;
	while (current != NULL) {
		ClientNode* next = current->next;
		sorted = AddClient(sorted, current->client);
		free(current);
		current = next;
	}
	return sorted;
}

ClientNode* LoadClientsFromTextFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return NULL;
	}

	ClientNode* head = NULL;
	Client newClient;
	while (fscanf(file, "%[^,],%lf,%[^,],%[^\n]\n", newClient.nif, &newClient.balance, newClient.name, newClient.address) == 4) {
		head = AddClient(head, newClient);
	}

	fclose(file);
	return head;
}

void SaveClientsToBinaryFile(ClientNode* head, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		return;
	}

	ClientNode* current = head;
	while (current != NULL) {
		fwrite(&(current->client), sizeof(Client), 1, file);
		current = current->next;
	}

	fclose(file);
}

ClientNode* LoadClientsFromBinaryFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		return NULL;
	}

	ClientNode* head = NULL;
	Client temp;

	while (fread(&temp, sizeof(Client), 1, file) == 1) {
		head = AddClient(head, temp);
	}

	fclose(file);
	return head;
}

ClientNode* LoadClients(const char* binFilename, const char* txtFilename) {
	ClientNode* head = LoadClientsFromBinaryFile(binFilename);

	if (head == NULL) {
		head = LoadClientsFromTextFile(txtFilename);
	}

	return head;
}

void FreeClients(ClientNode* head) {
	ClientNode* temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

ClientNode* DeleteClient(ClientNode* head, char* nif) {
	if (head == NULL) {
		return NULL;
	}

	if (strcmp(head->client.nif, nif) == 0) {
		ClientNode* nextNode = head->next;
		free(head);
		return nextNode;
	}

	ClientNode* current = head;
	while (current->next != NULL && strcmp(current->next->client.nif, nif) != 0) {
		current = current->next;
	}

	if (current->next == NULL) {
		return head;
	}

	ClientNode* nextNode = current->next->next;
	free(current->next);
	current->next = nextNode;
	return head;
}

void UpdateClient(ClientNode* head, char* nif, Client updatedClient) {
	ClientNode* current = head;
	while (current != NULL && strcmp(current->client.nif, nif) != 0) {
		current = current->next;
	}

	if (current != NULL) {
		current->client = updatedClient;
	}
}

ClientNode* FindClientByNif(ClientNode* head, char* nif) {
	ClientNode* current = head;
	while (current != NULL) {
		if (strcmp(current->client.nif, nif) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
