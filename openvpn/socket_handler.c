#include "socket_handler.h"

int sock;
struct sockaddr_in server_sock;


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
    char response[200];

    rc |= create_sock();
    configure_sock(&server_sock, config);
    rc |= connect_sock(&server_sock);

    rc |= recv(sock, response, 200, 0);
    return rc;
}

int send_request(char* request)
{
    int rc = 0;
    rc	   = send(sock, request, sizeof(request), 0);
    if(rc == -1)
    {
	    syslog(LOG_ERR, "Failed to send request to server");
	    return 1;
    }
    return 0;
}

int get_response(struct client** list)
{
    int rc = 0;
    char buffer[3000];
    rc = recv(sock, buffer, 3000, 0);
    parse_client_list(list, buffer);
}