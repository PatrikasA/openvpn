#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <syslog.h>
#include "argp_handler.h"
#include "client_list.h"

int init_connection(struct config *config);
int get_response(struct client **list);
int send_request(char *request);