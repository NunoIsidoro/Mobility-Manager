#include "clients.h"
#include "managers.h"
#include "headers.h"

void Login(ClientNode* clients, ManagerNode* managers, ClientNode** loggedClient, ManagerNode** loggedManager) {
	char nif[NIF_SIZE];

	do
	{
		system("cls");
		printf(" To exit enter 'x'.\n ");
		printf("Please enter your NIF: ");
		scanf("%s", nif);

		if (strcmp(nif, "x") == 0 || strcmp(nif, "X") == 0) {
			return;
		}

		*loggedManager = FindManagerByNif(managers, nif);
		*loggedClient = NULL;

		if (*loggedManager == NULL) {
			*loggedClient = FindClientByNif(clients, nif);
		}

		if (*loggedClient == NULL && *loggedManager == NULL) {
			system("cls");
			printf("Invalid NIF. Please try again.\n");
			system("pause");
		}


	} while (*loggedManager == NULL && *loggedClient == NULL);
}

