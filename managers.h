/**
 * @file   managers.h
 * @brief  This file includes functions and data types related to the manager system.
 *
 * @author Nuno Fernandes
 * @date   April 2023
 */

#ifndef MANAGERS_H
#define MANAGERS_H

#pragma once
#pragma warning(disable : 4996)

#include "headers.h"
#include "clients.h"

 /**
  * @brief Struct that represents a manager.
  */
typedef struct Manager {
	char nif[10];                       /**< Manager's Tax Identification Number (NIF). */
	char name[MIN_LENGHT];              /**< Manager's name. */
	char departmentLocation[MIN_LENGHT]; /**< Department location of the manager. */
} Manager;

/**
 * @brief Node for linked list of Manager struct.
 */
typedef struct ManagerNode {
	Manager manager;              /**< Manager data for the node. */
	struct ManagerNode* next;     /**< Pointer to the next node in the list. */
} ManagerNode;

/**
 * @brief Adds a new manager node to the list.
 *
 * @param head The head of the list.
 * @param newManager The new Manager data to be added.
 * @return A pointer to the new head of the list.
 */
ManagerNode* AddManager(ManagerNode* head, Manager newManager);

/**
 * @brief Loads manager data from a text file into a linked list.
 *
 * @param filename The name of the text file.
 * @return A pointer to the head of the created list.
 */
ManagerNode* LoadManagersFromTextFile(const char* filename);

/**
 * @brief Loads manager data from a binary file into a linked list.
 *
 * @param filename The name of the binary file.
 * @return A pointer to the head of the created list.
 */
ManagerNode* LoadManagersFromBinaryFile(const char* filename);

/**
 * @brief Loads manager data from both a text and a binary file into a linked list.
 *
 * @param binFilename The name of the binary file.
 * @param txtFilename The name of the text file.
 * @return A pointer to the head of the created list.
 */
ManagerNode* LoadManagers(const char* binFilename, const char* txtFilename);

/**
 * @brief Frees the memory occupied by the list of managers.
 *
 * @param head The head of the list.
 */
void FreeManagers(ManagerNode* head);

/**
 * @brief Saves manager data from a list into a file.
 *
 * @param filename The name of the file.
 * @param head The head of the list.
 */
void SaveManagersToFile(const char* filename, ManagerNode* head);

/**
 * @brief Finds a manager node in the list by its NIF.
 *
 * @param head The head of the list.
 * @param nif The NIF of the Manager data to be found.
 * @return A pointer to the found Manager node. If not found, returns NULL.
 */
ManagerNode* FindManagerByNif(ManagerNode* head, char* nif);

/**
 * @brief Displays the manager menu.
 *
 * @param managers The list of managers.
 * @param clients The list of clients.
 */
void ManagerMenu(ManagerNode* managers, ClientNode* clients);

/**
 * @brief Prints the information of all managers in the list.
 *
 * @param head The head of the list.
 */
void PrintAllManagers(ManagerNode* head);

#endif  // MANAGERS_H
