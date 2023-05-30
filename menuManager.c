#include "managers.h"
#include "clients.h"


void ManagerMenu(ManagerNode* managers, ClientNode* clients) {
	int choice;
	do {
		printf("\nManager Menu:\n");
		printf("1. View Managers\n");
		printf("2. Add Manager\n");
		printf("3. Update Manager\n");
		printf("4. Delete Manager\n");
		printf("5. View Clients\n");
		printf("6. Add Client\n");
		printf("7. Update Client\n");
		printf("8. Delete Client\n");
		printf("9. Log out\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		// You would call the appropriate function based on the choice here.
		// For example, if choice is 1, call PrintAllManagers(managers);

		switch (choice) {
		case 1:
			PrintAllManagers(managers);
			break;
		default:
			printf("Invalid choice.\n");
			break;
		}
	} while (choice != 9);
}

// Imprime todos os gestores
void PrintAllManagers(ManagerNode* head) {
	ManagerNode* current = head;
	while (current != NULL) {
		printf("NIF: %s, Nome: %s, Departamento: %s\n",
			current->manager.nif, current->manager.name, current->manager.departmentLocation);
		current = current->next;
	}
}