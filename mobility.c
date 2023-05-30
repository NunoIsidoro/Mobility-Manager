#include "mobility.h"
#include "headers.h"

MobilityNode* AddMobility(MobilityNode* head, Mobility newMobility) {
	MobilityNode* newNode = (MobilityNode*)malloc(sizeof(MobilityNode));
	newNode->mobility = newMobility;
	newNode->next = NULL;

	if (head == NULL) {
		head = newNode;
	}
	else {
		MobilityNode* current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	return head;
}

MobilityNode* DeleteMobility(MobilityNode* head, int id) {
	if (head == NULL) {
		return NULL;
	}

	if (head->mobility.id == id) {
		MobilityNode* tempNode = head;
		head = head->next;
		free(tempNode);
		return head;
	}

	MobilityNode* current = head;
	while (current->next != NULL && current->next->mobility.id != id) {
		current = current->next;
	}

	if (current->next != NULL) {
		MobilityNode* tempNode = current->next;
		current->next = current->next->next;
		free(tempNode);
	}

	return head;
}

void UpdateMobility(MobilityNode* head, int id, Mobility updatedMobility) {
	MobilityNode* current = head;
	while (current != NULL) {
		if (current->mobility.id == id) {
			current->mobility = updatedMobility;
			return;
		}
		current = current->next;
	}
}

MobilityNode* FindMobilityById(MobilityNode* head, int id) {
	MobilityNode* current = head;
	while (current != NULL) {
		if (current->mobility.id == id) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

// find mobility by type truck
MobilityNode* FindMobilityByType(MobilityNode* head, VehicleType type) {
	MobilityNode* current = head;
	while (current != NULL) {
		if (current->mobility.type == type) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}



MobilityNode* LoadMobilitiesFromTextFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return NULL;
	}

	MobilityNode* head = NULL;
	Mobility newMobility;
	while (fscanf(file, "%d,%d,%f,%f,%f,%f,%d,%d,%s,%s\n", &newMobility.id, &newMobility.type,
		&newMobility.battery_level, &newMobility.cost, &newMobility.batteryCapacity,
		&newMobility.energyCostWPerKm, &newMobility.vehicleWeight, &newMobility.maxTransportWeight,
		&newMobility.locationId) == 9) {
		head = AddMobility(head, newMobility);
	}

	fclose(file);
	return head;
}

void SaveMobilitiesToBinaryFile(MobilityNode* head, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		return;
	}

	MobilityNode* current = head;
	while (current != NULL) {
		fwrite(&(current->mobility), sizeof(Mobility), 1, file);
		current = current->next;
	}

	fclose(file);
}

MobilityNode* LoadMobilitiesFromBinaryFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		return NULL;
	}

	MobilityNode* head = NULL;
	Mobility tempMobility;

	while (fread(&tempMobility, sizeof(Mobility), 1, file)) {
		head = AddMobility(head, tempMobility);
	}

	fclose(file);
	return head;
}

MobilityNode* LoadMobilities(const char* binFilename, const char* txtFilename) {
	MobilityNode* head = LoadMobilitiesFromBinaryFile(binFilename);
	if (head == NULL) {
		head = LoadMobilitiesFromTextFile(txtFilename);
	}
	return head;
}

void FreeMobilities(MobilityNode* head) {
	MobilityNode* current = head;
	while (head != NULL) {
		current = head;
		head = head->next;
		free(current);
	}
}
