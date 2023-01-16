#include "client_list.h"

void add_client(struct client** head, struct client* client)
{
	client->next	       = NULL;
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
        if(to_delete !=NULL){
            to_delete -> next = NULL;
            free(to_delete);
        }
        to_delete = NULL;
        to_delete = list;
    }
}

int parse_client_list(struct client** head, char* message)
{
    char *buffer;
    buffer = strtok(message, ",\n");
    buffer = strtok(NULL, "\n");
    buffer = strtok(NULL, "\n");

    while(buffer != NULL)
    {
	if (strncmp(buffer, "ROUTING TABLE", 13)==0) {
	    break;
	}
    struct client *client = malloc(sizeof(struct client));
    client->next	  = NULL;

    buffer = strtok(NULL, ",");
    strcpy(client->common_name, buffer);
    buffer = strtok(NULL, ",");
    strcpy(client->address, buffer);
	buffer = strtok(NULL, ",");
	strcpy(client->bytes_received, buffer);
	buffer = strtok(NULL, ",");
	strcpy(client->bytes_sent, buffer);
	buffer = strtok(NULL, "\n");
	strcpy(client->connected_since, buffer);
	add_client(head, client);
	buffer = strtok(NULL, "\n");
    }
}

int print_client_list(struct client *list)
{
    struct client *temp = list;
    while (temp != NULL) {
	printf("%s %s %s %s %s\n", temp->common_name, temp->address, temp->bytes_sent, temp->bytes_received,
	       temp->connected_since);
	fflush(stdout);
	temp = temp->next;
    }
}