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

MobilityNode *create_mobility(int id, const char *type, float battery_level, float cost, const char *geocode);
int add_mobility(MobilityNode **mobility_items, MobilityNode *new_mobility);
int remove_mobility(MobilityNode **mobility_items, int id);
MobilityNode *find_mobility(MobilityNode *mobility_items, int id);
void delete_mobility_list(MobilityNode *mobility_items);
int save_mobility_to_binary_file(MobilityNode *mobility_items);
MobilityNode *load_mobility_from_binary_file(MobilityNode **existing_mobility_items);
int save_mobility_to_text_file(MobilityNode *mobility_items);
MobilityNode *load_mobility_from_text_file(MobilityNode **existing_mobility_items);

#endif  // MOBILITY_H
