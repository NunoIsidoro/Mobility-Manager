#ifndef MOBILITY_H
#define MOBILITY_H

#include "headers.h"

typedef struct {
    int id;
    char type[50];
    float battery_level;
    float cost;
    char geocode[20];
} Mobility;

void add_mobility(Mobility *mobilities, int *num_mobilities, Mobility new_mobility);

#endif // MOBILITY_H
