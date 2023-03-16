#include "clients.h"
#include "headers.h"

int main() {
    // Carregar os clientes do arquivo binário ou do arquivo de texto
    ClientNode *clients = load_clients_from_binary_file();
    if (!clients) {
        printf("No clients found. Creating a new list.\n");
        clients = NULL;
    }

    // Menu principal
    int option;
    do {
        printf("\n=== CLIENTS ===\n");
        printf("1. Add client\n");
        printf("2. Remove client\n");
        printf("3. Update client\n");
        printf("4. List clients\n");
        printf("5. Quit\n");
        printf("Enter option: ");
        scanf_s("%d", &option);
        fflush(stdin);  // Limpar o buffer do teclado

        switch (option) {
            case 1: {
                char nif[10], name[100], address[200];
                double balance;
                printf("\nEnter client NIF: ");
                scanf_s("%9s", nif, _countof(nif));
                printf("Enter client name: ");
                scanf_s("%s", name, _countof(name));
                printf("Enter client address: ");
                scanf_s("%s", address, _countof(address));
                printf("Enter initial balance: ");
                scanf_s("%lf", &balance);

                ClientNode *new_client = create_client(nif, balance, name, address);
                if (add_client(&clients, new_client)) {
                    printf("\nError: Failed to add client. Invalid or duplicate NIF.\n");
                } else {
                    printf("\nClient added successfully.\n");
                    save_clients_to_binary_file(clients);
                }
                break;
            }

            case 2: {
                char nif[10];
                printf("\nEnter client NIF: ");
                scanf_s("%9s", nif, _countof(nif));

                if (remove_client(&clients, nif)) {
                    printf("\nError: Client not found.\n");
                } else {
                    printf("\nClient removed successfully.\n");
                    save_clients_to_binary_file(clients);
                }
                break;
            }

            case 3: {
                char nif[10], name[100], address[200];
                double balance;
                printf("\nEnter client NIF: ");
                scanf_s("%9s", nif, _countof(nif));

                ClientNode *client = find_client(clients, nif);
                if (!client) {
                    printf("\nError: Client not found.\n");
                    break;
                }

                printf("Enter new name (or press Enter to keep current name): ");
                scanf_s("%99s", name, _countof(name));
                if (strlen(name) > 0) {
                    free(client->client.name);
                    client->client.name = _strdup(name);
                }

                printf("Enter new address (or press Enter to keep current address): ");
                scanf_s("%199s", address, _countof(address));
                if (strlen(address) > 0) {
                    free(client->client.address);
                    client->client.address = _strdup(address);
                }

                                printf("Enter new balance (or enter 0 to keep current balance): ");
                scanf_s("%lf", &balance);
                if (balance != 0) {
                    client->client.balance = balance;
                }

                printf("\nClient updated successfully.\n");
                save_clients_to_binary_file(clients);
                break;
            }

            case 4: {
                printf("\n=== CLIENT LIST ===\n");
                ClientNode *current = clients;

                if (!current) {
                    printf("No clients found.\n");
                } else {
                    while (current) {
                        printf("NIF: %s\n", current->client.nif);
                        printf("Name: %s\n", current->client.name);
                        printf("Address: %s\n", current->client.address);
                        printf("Balance: %.2f\n", current->client.balance);
                        printf("\n");
                        current = current->next;
                    }
                }
                break;
            }

            case 5: {
                printf("\nQuitting...\n");
                break;
            }

            default: {
                printf("\nError: Invalid option.\n");
                break;
            }
        }
    } while (option != 5);

    // Salvar os clientes no arquivo binário e liberar a memória da lista
    save_clients_to_binary_file(clients);
    delete_client_list(clients);

    return 0;
}
