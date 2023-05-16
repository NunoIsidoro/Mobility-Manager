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

	
ManagerNode *CreateManager(const char *id, double salary, const char *name, const char *department);
int AddManager(ManagerNode **managers, ManagerNode *new_manager);
int RemoveManager(ManagerNode **managers, const char *id);
ManagerNode *FindManager(ManagerNode *managers, const char *id);
void DeleteManagerList(ManagerNode *managers);
int SaveManagersToBinaryFile(ManagerNode *managers);
ManagerNode *LoadManagersFromBinaryFile(ManagerNode **existing_managers);
int SaveManagersToTextFile(ManagerNode *managers);
ManagerNode *LoadManagersFromTextFile(ManagerNode **existing_managers);

#endif  // MANAGERS_H
