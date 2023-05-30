// managers.c
#include "managers.h"

#define MAX_LINE_LENGTH 256

ManagerNode* AddManager(ManagerNode* head, Manager newManager) {
	ManagerNode* newNode = (ManagerNode*)malloc(sizeof(ManagerNode));
	newNode->manager = newManager;
	newNode->next = NULL;

	if (head == NULL || strcmp(newManager.name, head->manager.name) < 0) {
		newNode->next = head;
		head = newNode;
	}
	else {
		ManagerNode* current = head;
		while (current->next != NULL && strcmp(newManager.name, current->next->manager.name) > 0) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}

	return head;
}

ManagerNode* LoadManagersFromTextFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return NULL;
	}

	ManagerNode* head = NULL;
	Manager newManager;

	while (fscanf(file, "%[^,],%[^,],%[^\n]\n", newManager.nif, newManager.name, newManager.departmentLocation) == 3) {
		head = AddManager(head, newManager);
	}

	fclose(file);
	return head;
}


ManagerNode* LoadManagersFromBinaryFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		return NULL;
	}

	ManagerNode* head = NULL;
	Manager temp;

	while (fread(&temp, sizeof(Manager), 1, file) == 1) {
		head = AddManager(head, temp);
	}

	fclose(file);
	return head;
}

ManagerNode* LoadManagers(const char* binFilename, const char* txtFilename) {
	ManagerNode* head = LoadManagersFromBinaryFile(binFilename);

	if (head == NULL) {
		head = LoadManagersFromTextFile(txtFilename);
	}

	return head;
}

// Libera a memória da lista de gestores
void FreeManagers(ManagerNode* head) {
	ManagerNode* temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

void SaveManagersToFile(const char* filename, ManagerNode* head) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		return;
	}

	ManagerNode* current = head;
	while (current != NULL) {
		fwrite(&(current->manager), sizeof(Manager), 1, file);
		current = current->next;
	}

	fclose(file);
}

ManagerNode* FindManagerByNif(ManagerNode* head, char* nif) {
	ManagerNode* current = head;
	while (current != NULL) {
		if (strcmp(current->manager.nif, nif) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}