#include "mobility.h"

MobilityNode *create_mobility(int id, const char *type, float battery_level, float cost, const char *geocode) {
	// TODO implement this function
}

int add_mobility(MobilityNode **mobility_items, MobilityNode *new_mobility) {
	// TODO implement this function
}

int remove_mobility(MobilityNode **mobility_items, int id) {
	// TODO implement this function
}

MobilityNode *find_mobility(MobilityNode *mobility_items, int id) {
	// TODO implement this function
}

void delete_mobility_list(MobilityNode *mobility_items) {
	// TODO implement this function
}

int save_mobility_to_binary_file(MobilityNode *mobility_items) {
	// TODO implement this function
}

MobilityNode *load_mobility_from_binary_file(MobilityNode **existing_mobility_items) {
	// TODO implement this function
}

int save_mobility_to_text_file(MobilityNode *mobility_items) {
	// TODO implement this function
}

MobilityNode *load_mobility_from_text_file(MobilityNode **existing_mobility_items) {
	// TODO implement this function
}
