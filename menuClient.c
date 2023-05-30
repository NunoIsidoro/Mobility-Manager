#include "clients.h"

void ClientMenu(ClientNode* clients, ClientNode** loggedClient, const char* binFilename) {
	int choice;
	do {
		system("cls");
		printf("\nClient Menu:\n");
		printf("1. View My Information\n");
		printf("2. Update My Information\n");
		printf("3. Log out\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			PrintClientInfo(loggedClient);
			system("pause");
			break;
		case 2:

			UpdateClientInfo(loggedClient, clients, binFilename);
			system("pause");
			break;
		case 3:
			break;
		default:
			printf("Invalid choice.\n");
			break;
		}
	} while (choice != 3);
}


void PrintAllClients(ClientNode* head) {
	ClientNode* current = head;
	while (current != NULL) {
		printf("NIF: %s, Saldo: %.2lf, Nome: %s, Morada: %s\n",
			current->client.nif, current->client.balance, current->client.name, current->client.address);
		current = current->next;
	}

}

void PrintClientInfo(ClientNode** client) {
	system("cls");

	if (client == NULL || *client == NULL) {
		printf("Invalid client.\n");
		return;
	}

	printf("\nClient Information:\n\n");
	printf("Name: %s\n", (*client)->client.name);
	printf("NIF: %s\n", (*client)->client.nif);
	printf("Balance: %.2lf\n", (*client)->client.balance);
	printf("Address: %s\n\n", (*client)->client.address);

}

void UpdateClientInfo(ClientNode** loggedClient, ClientNode* head, const char* binFilename) {
	system("cls");
	if (loggedClient == NULL || *loggedClient == NULL) {
		printf("Invalid client.\n");
		return;
	}
	printf("\nClient Information:\n\n");
	PrintClientInfo(loggedClient);

	printf("\nEnter new client information:\n");
	Client updatedClient;
	printf("Enter new name: ");
	scanf("%s", updatedClient.name);
	printf("Enter new NIF: ");
	scanf("%s", updatedClient.nif);
	printf("Enter new balance: ");
	scanf("%lf", &updatedClient.balance);
	printf("Enter new address: ");
	scanf("%s", updatedClient.address);

	(*loggedClient)->client = updatedClient;

	SaveClientsToBinaryFile(head, binFilename);
}

