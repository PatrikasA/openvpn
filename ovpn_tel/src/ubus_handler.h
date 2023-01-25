#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include <json-c/json.h>
#include <syslog.h>
#include "client_list.h"

static const struct ubus_method ovpn_methods[] = { UBUS_METHOD_NOARG("get", ovpn_get) };

struct ubus_object_type ovpn_object_type = UBUS_OBJECT_TYPE("ovpnserver", ovpn_methods);

static struct ubus_object ovpn_object = (struct ubus_object){
	.name = "ovpnserver",
	.type = &ovpn_object_type,
	.methods = ovpn_methods,
	.n_methods = ARRAY_SIZE(ovpn_methods),
	};