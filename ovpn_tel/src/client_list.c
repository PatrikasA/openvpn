#include "client_list.h"

void add_client(struct client** head, struct client* client)
{
	client->next	    = NULL;
	struct client *temp = *head;
	if (temp == NULL) {
		*head = client;
		return;
	}
    while (temp->next != NULL) {
		temp = temp->next;
    }
    temp->next = client;
}

void delete_client_list(struct client *list)
{
    struct client *to_delete = list;
    while (list != NULL) {
		list = list->next;
		if (to_delete != NULL) {
			to_delete->next = NULL;
			free(to_delete);
		}
		to_delete = NULL;
		to_delete = list;
    }
}

int print_client_list(struct client *list)
{
    struct client *temp = list;
    while (temp != NULL) {
		printf(" %s %s %s %s\n", temp->address, temp->bytes_sent, temp->bytes_received,
		       temp->connected_since);
		fflush(stdout);
		temp = temp->next;
    }
}
