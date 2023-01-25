#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct client{
	char common_name[50];
	char address[30];
	char bytes_received[30];
	char bytes_sent[30];
	char connected_since[30];
	struct client *next;
};

int parse_client_list(struct client **head, char *message);
int print_client_list(struct client *list);
void delete_client_list(struct client *list);
#endif