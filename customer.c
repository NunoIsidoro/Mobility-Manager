/*****************************************************************//**
 * \file   customer.c
 * \brief  
 * 
 * \author Nuno Fernandes
 * \date   March 2023
 *********************************************************************/
#include "customer.h"


void add_customer(Customer **customers, int *num_customers, Customer new_customer) {
    // Check if customer data is valid before adding it to the list
    if (!validate_customer_data(&new_customer)) {
        printf("Invalid customer data. Customer not added.\n");
        return;
    }

    // Allocate memory for the new list of customers
    Customer *new_list = realloc(*customers, (*num_customers + 1) * sizeof(Customer));
    if (new_list == NULL) {
        printf("Memory allocation failed. Customer not added.\n");
        return;
    }

    // Update the list and add the new customer
    *customers = new_list;
    (*customers)[*num_customers] = new_customer;
    (*num_customers)++;
}


int add_customer_to_file(const char *filename, Customer *new_customer) {
    if (!validate_customer_data(new_customer)) {
        return 0; // Return false if customer data is invalid
    }

    FILE *file;
    errno_t err = fopen_s(&file, filename, "ab");

    if (err != 0 || file == NULL) {
        return 0; // Return false if the file cannot be opened
    }

    fwrite(new_customer, sizeof(Customer), 1, file);
    fclose(file);

    return 1; // Return true if the customer has been added successfully
}

int validate_customer_data(Customer *new_customer) {
    // Validate the customer ID (must be a positive integer)
    if (new_customer->id <= 0) {
        return 0;
    }

    // Validate the customer name (must not be empty)
    if (strlen(new_customer->name) == 0) {
        return 0;
    }

    // Validate the customer NIF (must be a positive integer)
    if (new_customer->nif <= 0) {
        return 0;
    }

    // Validate the customer balance (must be a non-negative float)
    if (new_customer->balance < 0) {
        return 0;
    }

    return 1; // Return true if all data is valid
}

int load_customers_from_file(const char *filename, Customer **customers, int *num_customers) {
    FILE *file;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0 || file == NULL) {
        return 0; // Return false if the file cannot be opened
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *num_customers = file_size / sizeof(Customer);

    *customers = malloc(*num_customers * sizeof(Customer));
    if (*customers == NULL) {
        fclose(file);
        return 0; // Return false if memory allocation fails
    }

    fread(*customers, sizeof(Customer), *num_customers, file);
    fclose(file);

    return 1; // Return true if customers are loaded successfully
}


void list_customers(Customer *customers, int num_customers) {
    if (num_customers == 0) {
        printf("No customers to display.\n");
        return;
    }

    printf("\nList of Customers:\n");
    for (int i = 0; i < num_customers; i++) {
        printf("ID: %d\n", customers[i].id);
        printf("Name: %s\n", customers[i].name);
        printf("Address: %s\n", customers[i].address);
        printf("NIF: %d\n", customers[i].nif);
        printf("Balance: %.2f\n", customers[i].balance);
        printf("\n");
    }
}
