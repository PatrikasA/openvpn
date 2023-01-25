#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include <json-c/json.h>
#include "client_list.h"
#include "socket_handler.h"
//#include "ubus_handler.h"

static int ovpn_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg);

static const struct ubus_method ovpn_methods[] = { UBUS_METHOD_NOARG("get", ovpn_get) };

struct ubus_object_type ovpn_object_type = UBUS_OBJECT_TYPE("ovpnserver", ovpn_methods);

static struct ubus_object ovpn_object = (struct ubus_object){
	.name = "ovpnserver",
	.type = &ovpn_object_type,
	.methods = ovpn_methods,
	.n_methods = ARRAY_SIZE(ovpn_methods),
	};

static int ovpn_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
	struct client *clients		= NULL;
	send_request("status\n");
	sleep(0.5);
	get_response(&clients);
	struct blob_buf b = {};
	blob_buf_init(&b, 0);
	struct client *current = clients;
	void *array = blobmsg_open_nested(&b, "clients", true);

	while (current != NULL) {
		void* json = blobmsg_open_nested(&b, NULL, false);
		blobmsg_add_string(&b, "common_name", current->common_name);
		blobmsg_add_string(&b, "address", current->address);
		blobmsg_add_string(&b, "bytes_received", current->bytes_received);
		blobmsg_add_string(&b, "bytes_sent", current->bytes_sent);
		blobmsg_add_string(&b, "connected_since", current->connected_since);
		blobmsg_close_table(&b, json);
		current = current->next;
	}
	blobmsg_close_array(&b, array);
	ubus_send_reply(ctx, req, b.head);
	blob_buf_free(&b);
	delete_client_list(clients);
	return 0;
}

int main(int argc, char *argv[])
{
	int rc		     = 0;
	struct ubus_context *ctx;
	uloop_init();
	ctx = ubus_connect(NULL);
	if (!ctx) {
		fprintf(stderr, "Failed to connect to ubus\n");
		return -1;
	}
	ubus_add_uloop(ctx);
	ubus_add_object(ctx, &ovpn_object);
	struct config config = { .address = "192.168.1.1", .port = 7505 };
	argp_parse(&argp, argc, argv, 0, 0, &config);
	rc = init_connection(&config);
	uloop_run();
	ubus_free(ctx);
	uloop_done();
}
