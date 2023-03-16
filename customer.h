/*****************************************************************//**
 * \file   customer.h
 * \brief  
 * 
 * \author Nuno Fernandes
 * \date   March 2023
 *********************************************************************/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "headers.h"

typedef struct {
    int id;
    char name[50];
    char address[100];
    int nif;
    float balance;
} Customer;


void add_customer(Customer **customers, int *num_customers, Customer new_customer);
int add_customer_to_file(const char *filename, Customer *new_customer);
int validate_customer_data(Customer *new_customer);
int load_customers_from_file(const char *filename, Customer **customers, int *num_customers);
void list_customers(Customer *customers, int num_customers);



#endif // CUSTOMER_H

