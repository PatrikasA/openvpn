#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "client_list.h"
#include "socket_handler.h"


volatile sig_atomic_t daemonize = 1;

void sig_handler(int signo)
{
    signal(SIGINT, NULL);
    syslog(LOG_ALERT, "Received signal: %d\n", signo);
    daemonize = 0;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
	int rc		     = 0;
	struct config config   = { .address = "192.168.1.1", .port = 7505 };
	argp_parse(&argp, argc, argv, 0, 0, &config);
	    struct client *clients = malloc(sizeof(struct client));
	    clients->next	   = NULL;
	rc = init_connection(&config);

    while(daemonize)
    {
	    rc = send_request("status\n");
	    sleep(1);
	    rc = get_response(&clients);
	    print_client_list(clients);
	    sleep(4);
	    //delete_client_list(clients);
    }
}