/*****************************************************************//**
 * \file   managers.h
 * \brief  Header file for manager-related functions.
 * 
 * \author Nuno Fernandes
 * \date   April 2023
 *********************************************************************/
#ifndef MANAGERS_H
#define MANAGERS_H

#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Manager {
	char id[10];
	double salary;
	char *name;
	char *department;
} Manager;

typedef struct ManagerNode {
	Manager manager;
	struct ManagerNode *next;
} ManagerNode;

	
// Creates a new manager and returns a pointer to it.
// id: Manager's ID string (up to 9 characters)
// salary: Manager's salary
// name: Manager's name
// department: Manager's department
ManagerNode *create_manager(const char *id, double salary, const char *name, const char *department);

// Adds a new manager to the managers list.
// managers: a pointer to the managers list
// new_manager: a pointer to the manager to be added
// Returns 0 on success or -1 on failure.
int add_manager(ManagerNode **managers, ManagerNode *new_manager);

// Removes a manager from the managers list based on the provided ID.
// managers: a pointer to the managers list
// id: the ID of the manager to be removed
// Returns 0 on success or -1 on failure.
int remove_manager(ManagerNode **managers, const char *id);

// Finds a manager in the managers list based on the provided ID.
// managers: the managers list
// id: the ID of the manager to be found
// Returns a pointer to the found manager or NULL if not found.
ManagerNode *find_manager(ManagerNode *managers, const char *id);

// Deletes the entire managers list and frees the memory.
// managers: the managers list to be deleted
void delete_manager_list(ManagerNode *managers);

// Saves the managers list to a binary file.
// managers: the managers list to be saved
// Returns 0 on success or -1 on failure.
int save_managers_to_binary_file(ManagerNode *managers);

// Loads the managers list from a binary file.
// Returns a pointer to the loaded managers list or NULL if not found.
ManagerNode *load_managers_from_binary_file(ManagerNode **existing_managers);

// Saves the managers list to a text file.
// managers: the managers list to be saved
// Returns 0 on success or -1 on failure.
int save_managers_to_text_file(ManagerNode *managers);

// Loads the managers list from a text file.
// Returns a pointer to the loaded managers list or NULL if not found.
ManagerNode *load_managers_from_text_file(ManagerNode **existing_managers);

#endif  // MANAGERS_H
