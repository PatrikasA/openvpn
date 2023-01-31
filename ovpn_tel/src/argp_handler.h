#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include <string.h>
#ifndef ARGP_HANDLER_H
#define ARGP_HANDLER_H

struct config{
	char address[50];
	unsigned int port;
	char server_name[50];
};

static struct argp_option options[] = { { "server_address", 'a', "server_address", 0, "Server address" },
					{ "server_port", 'p', "server_port", 0, "Server port" },
					{ "server_name", 's', "server_name", 0, "Server name" },
					{ 0 } };

error_t parse_opt(int key, char *arg, struct argp_state *state);
#endif