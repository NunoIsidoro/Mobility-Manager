/**
 * @file   mobility.h
 * @brief  This file includes functions and data types related to the mobility system.
 * @author Nuno Fernandes
 * @date   April 2023
 */

#ifndef MOBILITY_H
#define MOBILITY_H

#include "headers.h"

 /**
  * @brief Types of vehicles.
  */
typedef enum {
	Bicycles,    /**< Bicycles as vehicle type. */
	Scooters,    /**< Scooters as vehicle type. */
	Trucks,      /**< Trucks as vehicle type. */
	Other        /**< Other types of vehicles. */

} VehicleType;

/**
 * @brief Struct that represents a mobility vehicle.
 */
typedef struct Mobility {
	int id;                          /**< Unique identifier for the vehicle. */
	VehicleType type;                /**< Type of the vehicle. */
	float battery_level;             /**< Current battery level of the vehicle. */
	float cost;                      /**< Cost of the vehicle. */
	float batteryCapacity;           /**< Capacity of the vehicle's battery. */
	float energyCostWPerKm;          /**< Energy cost per kilometer. */
	int vehicleWeight;               /**< Weight of the vehicle. */
	int maxTransportWeight;          /**< Maximum weight that the vehicle can transport. */
	int locationId;                  /**< Identifier for the vehicle's location. */
} Mobility;

/**
 * @brief Node for linked list of Mobility struct.
 */
typedef struct MobilityNode {
	Mobility mobility;              /**< Mobility data for the node. */
	struct MobilityNode* next;      /**< Pointer to the next node in the list. */
} MobilityNode;

/**
 * @brief Adds a new mobility node to the list.
 *
 * @param head The head of the list.
 * @param newMobility The new Mobility data to be added.
 * @return A pointer to the new head of the list.
 */
MobilityNode* AddMobility(MobilityNode* head, Mobility newMobility);

/**
 * @brief Deletes a mobility node from the list.
 *
 * @param head The head of the list.
 * @param id The ID of the Mobility data to be deleted.
 * @return A pointer to the new head of the list.
 */
MobilityNode* DeleteMobility(MobilityNode* head, int id);

/**
 * @brief Updates a mobility node in the list.
 *
 * @param head The head of the list.
 * @param id The ID of the Mobility data to be updated.
 * @param updatedMobility The updated Mobility data.
 */
void UpdateMobility(MobilityNode* head, int id, Mobility updatedMobility);

/**
 * @brief Finds a mobility node in the list by its ID.
 *
 * @param head The head of the list.
 * @param id The ID of the Mobility data to be found.
 * @return A pointer to the found Mobility node. If not found, returns NULL.
 */
MobilityNode* FindMobilityById(MobilityNode* head, int id);

/**
 * @brief Finds a mobility node in the list by its vehicle type.
 *
 * @param head The head of the list.
 * @param type The VehicleType of the Mobility data to be found.
 * @return A pointer to the found Mobility node. If not found, returns NULL.
 */
MobilityNode* FindMobilityByType(MobilityNode* head, VehicleType type);

/**
 * @brief Loads mobility data from a text file into a linked list.
 *
 * @param filename The name of the text file.
 * @return A pointer to the head of the created list.
 */
MobilityNode* LoadMobilitiesFromTextFile(const char* filename);

/**
 * @brief Saves mobility data from a linked list into a binary file.
 *
 * @param head The head of the list.
 * @param filename The name of the binary file.
 */
void SaveMobilitiesToBinaryFile(MobilityNode* head, const char* filename);

/**
 * @brief Loads mobility data from a binary file into a linked list.
 *
 * @param filename The name of the binary file.
 * @return A pointer to the head of the created list.
 */
MobilityNode* LoadMobilitiesFromBinaryFile(const char* filename);

/**
 * @brief Loads mobility data either from a binary or a text file into a linked list.
 *
 * @param binFilename The name of the binary file.
 * @param txtFilename The name of the text file.
 * @return A pointer to the head of the created list.
 */
MobilityNode* LoadMobilities(const char* binFilename, const char* txtFilename);

/**
 * @brief Frees all the memory allocated for the linked list of Mobility.
 *
 * @param head The head of the list.
 */
void FreeMobilities(MobilityNode* head);

#endif  // MOBILITY_H
