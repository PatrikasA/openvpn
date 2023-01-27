#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "argp_handler.h"
#include "ubus_handler.h"

static int ovpn_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg);

const struct ubus_method ovpn_methods[] = { UBUS_METHOD_NOARG("get", ovpn_get) };


int main(int argc, char *argv[])
{
	struct argp argp = { options, parse_opt, "", "" };
	char server_name[60];
	int rc = 0;
	struct ubus_context *ctx;
	struct config config = { .address = "192.168.1.1", .port = 7505, .server_name="local" };
	argp_parse(&argp, argc, argv, 0, 0, &config);
	sprintf(server_name, "openvpn.%s", config.server_name);
	struct ubus_object_type ovpn_object_type = UBUS_OBJECT_TYPE(server_name, ovpn_methods);
	struct ubus_object ovpn_object = (struct ubus_object){
	.name = server_name,
	.type = &ovpn_object_type,
	.methods = ovpn_methods,
	.n_methods = ARRAY_SIZE(ovpn_methods),
	};
	uloop_init();
	ctx = ubus_connect(NULL);
	if (!ctx) {
		fprintf(stderr, "Failed to connect to ubus\n");
		return -1;
	}
	ubus_add_uloop(ctx);
	ubus_add_object(ctx, &ovpn_object);
	rc = init_connection(&config);
	uloop_run();
	ubus_free(ctx);
	uloop_done();
}
