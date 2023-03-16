#include "headers.h"
#include "customer.h"
#include "manager.h"
#include "mobility.h"

int main() {
    int num_customers = 0;
    Customer *customers = NULL;

    const char *customer_filename = "Data/customers.bin";

    // Load customers from the binary file
    if (load_customers_from_file(customer_filename, &customers, &num_customers)) {
        printf("Customers loaded successfully.\n");
    } else {
        printf("Failed to load customers from file.\n");
    }

    int option;
    do {
        printf("\nMenu:\n");
        printf("1. Add customer\n");
        printf("2. List customers\n");
        printf("0. Exit\n");
        printf("Enter your option: ");
        scanf_s("%d", &option);

        switch (option) {
            case 1: {
                Customer new_customer;
                printf("Enter customer ID: ");
                scanf_s("%d", &new_customer.id);
                printf("Enter customer name: ");
                scanf_s(" %[^\n]", new_customer.name, sizeof(new_customer.name));
                printf("Enter customer address: ");
                scanf_s(" %[^\n]", new_customer.address, sizeof(new_customer.address));
                printf("Enter customer NIF: ");
                scanf_s("%d", &new_customer.nif);
                printf("Enter customer balance: ");
                scanf_s("%f", &new_customer.balance);

                add_customer(&customers, &num_customers, new_customer);

                if (add_customer_to_file(customer_filename, &new_customer)) {
                    printf("Customer added and saved to file successfully.\n");
                } else {
                    printf("Failed to save customer to file.\n");
                }
                break;
            }
            case 2: {
                list_customers(customers, num_customers);
                break;
            }
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

    // Free the allocated memory for customers
    free(customers);

    return 0;
}