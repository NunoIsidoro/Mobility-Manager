
#include "managers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

ManagerNode *create_manager(const char *id, double salary, const char *name, const char *department) {
	ManagerNode *new_manager = malloc(sizeof(ManagerNode));
	if (new_manager == NULL) {
		return NULL; // Allocation failed
	}
	strncpy_s(new_manager->manager.id, sizeof(new_manager->manager.id), id, _TRUNCATE);
	new_manager->manager.salary = salary;
	new_manager->manager.name = _strdup(name);
	new_manager->manager.department = _strdup(department);
	new_manager->next = NULL;
	return new_manager;
}

int add_manager(ManagerNode **managers, ManagerNode *new_manager) {
	if (managers == NULL || new_manager == NULL) {
		return -1; // Invalid arguments
	}
	new_manager->next = *managers;
	*managers = new_manager;
	return 0;
}

int remove_manager(ManagerNode **managers, const char *id) {
	if (managers == NULL || *managers == NULL || id == NULL) {
		return -1; // Invalid arguments
	}
	ManagerNode *current = *managers;
	ManagerNode *previous = NULL;
	while (current != NULL) {
		if (strcmp(current->manager.id, id) == 0) {
			if (previous == NULL) {
				*managers = current->next; // Removing the head of the list
			} else {
				previous->next = current->next;
			}
			free(current->manager.name);
			free(current->manager.department);
			free(current);
			return 0;
		}
		previous = current;
		current = current->next;
	}
	return -1; // Manager not found
}

ManagerNode *find_manager(ManagerNode *managers, const char *id) {
	while (managers != NULL) {
		if (strcmp(managers->manager.id, id) == 0) {
			return managers;
		}
		managers = managers->next;
	}
	return NULL; // Manager not found
}

void delete_manager_list(ManagerNode *managers) {
	ManagerNode *next;
	while (managers != NULL) {
		next = managers->next;
		free(managers->manager.name);
		free(managers->manager.department);
		free(managers);
		managers = next;
	}
}

int save_managers_to_binary_file(ManagerNode *managers) {
	// TODO implement this function 
}

ManagerNode *load_managers_from_binary_file(ManagerNode **existing_managers) {
	// TODO implement this function
}

int save_managers_to_text_file(ManagerNode *managers) {
	// TODO implement this function
}

ManagerNode *load_managers_from_text_file(ManagerNode **existing_managers) {
	// TODO implement this function
}
