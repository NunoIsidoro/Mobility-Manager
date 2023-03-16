#ifndef MANAGER_H
#define MANAGER_H

#include "headers.h"

typedef struct {
    int id;
    char name[50];
    char username[50];
    char password[50];
} Manager;

void add_manager(Manager *managers, int *num_managers, Manager new_manager);

#endif // MANAGER_H
