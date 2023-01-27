#include "socket_handler.h"

int sock;
struct sockaddr_in server_sock;
FILE *in;

int create_sock()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
	    syslog(LOG_ERR, "Failed to create unix socket");
	    return 1;
    }
    return 0;
}

void configure_sock(struct sockaddr_in *server_sock, struct config* config)
{
    server_sock->sin_addr.s_addr = inet_addr(config->address);
    server_sock->sin_family	 = AF_INET;
    server_sock->sin_port	 = htons(config->port);
}

int connect_sock(struct sockaddr_in* server_sock)
{
    int rc = 0;
    rc	   = connect(sock, (struct sockaddr *)server_sock, sizeof(*server_sock));
    if(rc)
    {
	    syslog(LOG_ERR, "Failed to connect to openvpn server: %d",rc);
	    return 1;
    }
	    syslog(LOG_INFO, "Connected to openvpn server");
    return 0;
}

int init_connection(struct config* config)
{
    int rc = 0;
    rc |= create_sock();
    configure_sock(&server_sock, config);
    rc |= connect_sock(&server_sock);
    in = fdopen(sock,"r+");
    return rc;
}

int send_request(char* request)
{
    int rc = 0;
    rc	   = send(sock, request, strlen(request), 0);
    if(rc == -1)
    {
	    syslog(LOG_ERR, "Failed to send request to server");
	    return 1;
    }
    return 0;
}

int parse_client_list(struct client** head)
{
    char* response = malloc(sizeof(char)*200);
    unsigned int len = 200;
    getline(&response, &len, in);
    ssize_t chars_read = -1;
    while (chars_read != 0) {
	    if (!strncmp(response, "Common Name,Real Address,Bytes Received,Bytes Sent,Connected Since",66)) {
		    chars_read = getline(&response, &len, in);
		    while (strncmp(response, "ROUTING TABLE", 13)) {
			    struct client *client = malloc(sizeof(struct client));
			    client->next	  = NULL;
			    char *buffer;
			    buffer = strtok(response, ",");
			    strcpy(client->common_name, buffer);
			    buffer = strtok(NULL, ",");
			    strcpy(client->address, buffer);
			    buffer = strtok(NULL, ",");
			    strcpy(client->bytes_received, buffer);
			    buffer = strtok(NULL, ",");
			    strcpy(client->bytes_sent, buffer);
			    buffer = strtok(NULL, "\r\n");
			    strcpy(client->connected_since, buffer);
			    add_client(head, client);
		        chars_read = getline(&response, &len, in);
		    }
	    return 0;
	    }
    chars_read= getline(&response, &len, in);
    }
    free(response);
}
