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
	printf(" %s %s %s %s\n", temp->address, temp->bytes_sent, temp->bytes_received,
	       temp->connected_since);
	fflush(stdout);
	temp = temp->next;
    }
}


// int client_list_to_json(struct client *list)
// {
//     char client_string[1000];
//     strcat(client_string, "{clients: [ ");

//     struct client *current = list;

//     while(list != NULL)
//     {
// 	char current_client[100];
// 	sprintf(current_client,
// 		"{\ncommon_name: %s,\naddress: %s,\nbytes_received: %s,\nbytes_sent: %s,\nconnected_since: %s\n}");
// 	if (current->next != NULL)
// 	    strcat(current_client, ",\n");

// 	strcat(client_string, current_client);
//     }
// 	strcat(client_string, "]\n}");

// }