/*****************************************************************//**
 * \file   mobility.h
 * \brief  Header file for mobility-related functions.
 * 
 * \author Nuno Fernandes
 * \date   April 2023
 *********************************************************************/
#ifndef MOBILITY_H
#define MOBILITY_H

#include "headers.h"

typedef struct Mobility {
	int id;
	char type[50];
	float battery_level;
	float cost;
	char geocode[20];
} Mobility;

typedef struct MobilityNode {
	Mobility mobility;
	struct MobilityNode *next;
} MobilityNode;

// Creates a new mobility item and returns a pointer to it.
// id: ID integer
// type: mobility type string (up to 49 characters)
// battery_level: mobility item's battery level
// cost: mobility item's cost
// geocode: mobility item's geocode (up to 19 characters)
MobilityNode *create_mobility(int id, const char *type, float battery_level, float cost, const char *geocode);

// Adds a new mobility item to the mobility list.
// mobility_items: a pointer to the mobility list
// new_mobility: a pointer to the mobility item to be added
// Returns 0 on success or -1 on failure.
int add_mobility(MobilityNode **mobility_items, MobilityNode *new_mobility);

// Removes a mobility item from the mobility list based on the provided ID.
// mobility_items: a pointer to the mobility list
// id: the ID of the mobility item to be removed
// Returns 0 on success or -1 on failure.
int remove_mobility(MobilityNode **mobility_items, int id);

// Finds a mobility item in the mobility list based on the provided ID.
// mobility_items: the mobility list
// id: the ID of the mobility item to be found
// Returns a pointer to the found mobility item or NULL if not found.
MobilityNode *find_mobility(MobilityNode *mobility_items, int id);

// Deletes the entire mobility list and frees the memory.
// mobility_items: the mobility list to be deleted
void delete_mobility_list(MobilityNode *mobility_items);

// Saves the mobility list to a binary file.
// mobility_items: the mobility list to be saved
// Returns 0 on success or -1 on failure.
int save_mobility_to_binary_file(MobilityNode *mobility_items);

// Loads the mobility list from a binary file.
// Returns a pointer to the loaded mobility list or NULL if not found.
MobilityNode *load_mobility_from_binary_file(MobilityNode **existing_mobility_items);

// Saves the mobility list to a text file.
// mobility_items: the mobility list to be saved
// Returns 0 on success or -1 on failure.
int save_mobility_to_text_file(MobilityNode *mobility_items);

// Loads the mobility list from a text file.
// Returns a pointer to the loaded mobility list or NULL if not found.
MobilityNode *load_mobility_from_text_file(MobilityNode **existing_mobility_items);

#endif  // MOBILITY_H
