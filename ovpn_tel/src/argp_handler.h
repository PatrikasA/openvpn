#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include <string.h>

error_t parse_opt(int key, char *arg, struct argp_state *state);

struct config{
	char address[50];
	unsigned int port;
};

static struct argp_option options[] = { { "server_address", 'a', "server_address", 0, "Server address" },
					{ "server_port", 'p', "server_port", 0, "Server port" },
					{ 0 } };

static struct argp argp = { options, parse_opt, "", "" };