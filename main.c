#include "clients.h"
#include "headers.h"
#include "managers.h"
#include "mobility.h"
#include "utilis.h"
#include "locations.h"


int main() {

	// Load data from files
	ClientNode* clients = LoadClients(BIN_CLIENT_FILENAME, TXT_CLIENT_FILENAME);
	ManagerNode* managers = LoadManagers(BIN_MANAGER_FILENAME, TXT_MANAGER_FILENAME);
	MobilityNode* mobilities = LoadMobilities(BIN_MOBILITY_FILENAME, TXT_MOBILITY_FILENAME);
	LocationNode* locations = LoadLocationsFromTextFile(TXT_LOCATION_FILENAME);
	LocationNode* locations_surroundings = LoadLocationSurroundingsFromTextFile(TXT_LOCATION_SURROUNDINGS_FILENAME);

	ClientNode* loggedClient = NULL;
	ManagerNode* loggedManager = NULL;

	char userNIF[NIF_SIZE];
	Login(clients, managers, &loggedClient, &loggedManager);

	system("cls");

	if (loggedClient == NULL && loggedManager == NULL) {
		printf("Exiting...\n");
		return 0;
	}
	else if (loggedClient != NULL) {
		printf("Client logged in.\n");
		system("pause");
		ClientMenu(clients, &loggedClient, BIN_CLIENT_FILENAME);
	}
	else if (loggedManager != NULL) {
		printf("Manager logged in.\n");
		system("pause");
		ManagerMenu(managers, clients, &loggedManager);
	}

	FreeClients(clients);
	FreeManagers(managers);

	return 0;
}


