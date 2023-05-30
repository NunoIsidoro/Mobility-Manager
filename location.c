#include "locations.h"
#include "headers.h"
#include "mobility.h"


LocationNode* AddLocation(LocationNode* head, Location newLocation) {
	LocationNode* newNode = (LocationNode*)malloc(sizeof(LocationNode));
	newNode->location = newLocation;
	newNode->next = head;
	return newNode;
}

LocationSurroundingsNode* AddLocationSurroundings(LocationSurroundingsNode* head, LocationSurroundings newLocationSurroundings) {
	LocationSurroundingsNode* newNode = (LocationSurroundingsNode*)malloc(sizeof(LocationSurroundingsNode));
	newNode->locationSurroundings = newLocationSurroundings;
	newNode->next = head;
	return newNode;
}

LocationNode* LoadLocationsFromTextFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return NULL;
	}

	LocationNode* head = NULL;
	Location location;

	while (fscanf(file, "%d,%[^,],%[^\n]\n", &location.id, location.district, location.geocode) == 3) {
		head = AddLocation(head, location);
	}

	fclose(file);
	return head;
}



LocationSurroundingsNode* LoadLocationSurroundingsFromTextFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return NULL;
	}

	LocationSurroundingsNode* head = NULL;
	LocationSurroundings locationSurroundings;

	while (fscanf(file, "%d,%d,%d\n", &locationSurroundings.originId, &locationSurroundings.destinationId, &locationSurroundings.distance) == 3) {
		head = AddLocationSurroundings(head, locationSurroundings);
	}

	fclose(file);
	return head;
}

void PrintLocationSurroundings(LocationSurroundingsNode* head) {
	LocationSurroundingsNode* current = head;

	while (current != NULL) {
		printf("O distrito %d está conectado ao distrito %d com uma distância de %d km\n",
			current->locationSurroundings.originId,
			current->locationSurroundings.destinationId,
			current->locationSurroundings.distance);

		current = current->next;
	}
}

LocationNode* FindLocationById(LocationNode* head, int id) {
	LocationNode* current = head;
	while (current != NULL) {
		if (current->location.id == id) {
			return current;
		}
		current = current->next;
	}
	return NULL;  // ID não encontrado
}

int minDistance(int a, int b) { return (a < b) ? a : b; }

int firstUnvisited(int* visited, int numDistricts) {
	for (int i = 0; i < numDistricts; i++)
		if (!visited[i])
			return i;
	return -1;
}

void findPath(int** graph, int* visited, int currPos, int numDistricts, int count, int cost, int* answer) {
	if (count == numDistricts && graph[currPos][0]) {
		*answer = min(*answer, cost + graph[currPos][0]);
		return;
	}

	for (int i = 0; i < numDistricts; i++) {
		if (!visited[i] && graph[currPos][i]) {
			visited[i] = 1;
			findPath(graph, visited, i, numDistricts, count + 1, cost + graph[currPos][i], answer);
			visited[i] = 0;
		}
	}
}

int** ConvertToAdjacencyMatrix(LocationSurroundingsNode* head, int numDistricts) {
	// Alocar espaço para a matriz
	int** matrix = (int**)malloc(numDistricts * sizeof(int*));
	for (int i = 0; i < numDistricts; i++) {
		matrix[i] = (int*)malloc(numDistricts * sizeof(int));
		// Inicializar todos os valores como infinito
		for (int j = 0; j < numDistricts; j++) {
			matrix[i][j] = INT_MAX;
		}
	}

	// Preencher a matriz com as distâncias reais
	LocationSurroundingsNode* current = head;
	while (current != NULL) {
		int origin = current->locationSurroundings.originId;
		int destination = current->locationSurroundings.destinationId;
		int distance = current->locationSurroundings.distance;

		// Subtrair 1 porque os IDs começam em 1, mas os índices de matriz começam em 0
		matrix[origin - 1][destination - 1] = distance;

		current = current->next;
	}

	return matrix;
}


int* FindShortestPath(LocationSurroundingsNode* graph, int startLocation, int numDistricts) {
	int** adjacencyMatrix = ConvertToAdjacencyMatrix(graph, numDistricts);

	int* visited = calloc(numDistricts, sizeof(int));
	visited[0] = 1;

	int answer = INT_MAX;
	findPath(adjacencyMatrix, visited, 0, numDistricts, 1, 0, &answer);

	free(visited);
	for (int i = 0; i < numDistricts; i++)
		free(adjacencyMatrix[i]);
	free(adjacencyMatrix);

	return answer;
}

void ChargeVehiclesOnRoute(MobilityNode* head, int numDistricts) {

	MobilityNode* truck = FindMobilityByType(head, 5);
	for (int i = 0; i < numDistricts; i++) {
		int district_id = truck->mobility.locationId;
		MobilityNode* current = head;
		while (current != NULL) {
			if (current->mobility.locationId == district_id &&
				(current->mobility.type == Bicycles || current->mobility.type == Scooters) &&
				current->mobility.battery_level < 50) {
				int weight_to_load = current->mobility.vehicleWeight;
				if (truck->mobility.maxTransportWeight - weight_to_load >= 0) {
					truck->mobility.maxTransportWeight -= weight_to_load;
					current->mobility.battery_level = 100;
				}
				else {
					break;
				}
			}
			current = current->next;
		}
	}
}

int GetNumDistricts(LocationNode* head) {
	int count = 0;
	LocationNode* current = head;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}


void FastestRoute(LocationSurroundingsNode* graph, int startLocation, MobilityNode* vehicles) {
	int numDistricts = GetNumDistricts(graph);
	int* route = FindShortestPath(graph, startLocation, numDistricts);
	ChargeVehiclesOnRoute(vehicles, numDistricts);
	free(route);
}
