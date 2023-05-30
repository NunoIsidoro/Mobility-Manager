/**
 * @file   locations.h
 * @brief  This file includes functions and data types related to the location system.
 *
 * @author Nuno Fernandes
 * @date   May 2023
 */

#ifndef LOCATIONS_H
#define LOCATIONS_H

#pragma once
#pragma warning(disable : 4996)

#include "headers.h"
#include "mobility.h"

 /**
  * @brief Struct that represents a location.
  */
typedef struct Location {
	int id;                       /**< Unique identifier for the location. */
	char district[MIN_LENGHT];    /**< District of the location. */
	char geocode[MAX_LENGHT];     /**< Geocode of the location. */
} Location;

/**
 * @brief Node for linked list of Location struct.
 */
typedef struct LocationNode {
	Location location;              /**< Location data for the node. */
	struct LocationNode* next;      /**< Pointer to the next node in the list. */
} LocationNode;

/**
 * @brief Struct that represents the surroundings of a location.
 */
typedef struct LocationSurroundings {
	int originId;                   /**< ID of the origin location. */
	int destinationId;              /**< ID of the destination location. */
	int distance;                   /**< Distance from origin to destination. */
} LocationSurroundings;

/**
 * @brief Node for linked list of LocationSurroundings struct.
 */
typedef struct LocationSurroundingsNode {
	LocationSurroundings locationSurroundings; /**< Surroundings data for the node. */
	struct LocationSurroundingsNode* next;     /**< Pointer to the next node in the list. */
} LocationSurroundingsNode;

/**
 * @brief Adds a new location node to the list.
 *
 * @param head The head of the list.
 * @param newLocation The new Location data to be added.
 * @return A pointer to the new head of the list.
 */
LocationNode* AddLocation(LocationNode* head, Location newLocation);

/**
 * @brief Adds a new location surroundings node to the list.
 *
 * @param head The head of the list.
 * @param newLocationSurroundings The new LocationSurroundings data to be added.
 * @return A pointer to the new head of the list.
 */
LocationSurroundingsNode* AddLocationSurroundings(LocationSurroundingsNode* head, LocationSurroundings newLocationSurroundings);

/**
 * @brief Loads location data from a text file into a linked list.
 *
 * @param filename The name of the text file.
 * @return A pointer to the head of the created list.
 */
LocationNode* LoadLocationsFromTextFile(const char* filename);

/**
 * @brief Loads location surroundings data from a text file into a linked list.
 *
 * @param filename The name of the text file.
 * @return A pointer to the head of the created list.
 */
LocationSurroundingsNode* LoadLocationSurroundingsFromTextFile(const char* filename);

/**
 * @brief Prints the information of all location surroundings in the list.
 *
 * @param head The head of the list.
 */
void PrintLocationSurroundings(LocationSurroundingsNode* head);

/**
 * @brief Finds a location node in the list by its ID.
 *
 * @param head The head of the list.
 * @param id The ID of the Location data to be found.
 * @return A pointer to the found Location node. If not found, returns NULL.
 */
LocationNode* FindLocationById(LocationNode* head, int id);

/**
 * @brief Compares two distances and returns the smallest one.
 *
 * @param a The first distance.
 * @param b The second distance.
 * @return The smallest distance.
 */
int MinDistance(int a, int b);

/**
 * @brief Returns the first unvisited district.
 *
 * @param visited Array of visited status for each district.
 * @param num_districts The total number of districts.
 * @return The first unvisited district. If all are visited, returns -1.
 */
int FirstUnvisited(int* visited, int num_districts);

/**
 * @brief Finds a path in the graph.
 *
 * @param graph The adjacency matrix of the graph.
 * @param visited Array of visited status for each node.
 * @param currPos The current position in the graph.
 * @param num_districts The total number of districts.
 * @param count The current count of visited nodes.
 * @param cost The current cost of the path.
 * @param answer Pointer to the minimal cost found so far.
 */
void FindPath(int** graph, int* visited, int currPos, int num_districts, int count, int cost, int* answer);

/**
 * @brief Finds the shortest path in the graph from a start location.
 *
 * @param graph The linked list of location surroundings.
 * @param start_location The start location id.
 * @param num_districts The total number of districts.
 * @return A pointer to the array containing the shortest path.
 */
int* FindShortestPath(LocationSurroundingsNode* graph, int start_location, int num_districts);

/**
 * @brief Charges vehicles on the route.
 *
 * @param head The head of the mobility list.
 * @param num_districts The total number of districts.
 */
void ChargeVehiclesOnRoute(MobilityNode* head, int num_districts);

/**
 * @brief Gets the number of districts.
 *
 * @param head The head of the location list.
 * @return The number of districts.
 */
int GetNumDistricts(LocationNode* head);

/**
 * @brief Finds the fastest route from a start location.
 *
 * @param graph The linked list of location surroundings.
 * @param start_location The start location id.
 * @param vehicles The head of the mobility list.
 */
void FastestRoute(LocationSurroundingsNode* graph, int start_location, MobilityNode* vehicles);

/**
 * @brief Converts a linked list of LocationSurroundings into an adjacency matrix.
 *
 * @param head The head of the location surroundings list.
 * @param numDistricts The total number of districts.
 * @return A pointer to the adjacency matrix.
 */
int** ConvertToAdjacencyMatrix(LocationSurroundingsNode* head, int numDistricts);

#endif  // LOCATIONS_H

