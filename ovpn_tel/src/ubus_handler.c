#include "ubus_handler.h"

extern const struct blobmsg_policy disconnect_policy[];

int ovpn_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
	struct client *clients		= NULL;
	send_request("status\n");
	sleep(0.5);
	parse_client_list(&clients);
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

int ovpn_disconnect(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
			   const char *method, struct blob_attr *msg)
{
	char message[128];
	struct blob_attr *tb[1];
	struct blob_buf b = {};
	blobmsg_parse(disconnect_policy, 1, tb, blob_data(msg), blob_len(msg));
	if(!tb[0])
		return UBUS_STATUS_INVALID_ARGUMENT;
	char *address = blobmsg_get_string(tb[0]);
	blob_buf_init(&b, 0);
	sprintf(message, "kill %s\n", address);
	send_request(message);
}