#include "argp_handler.h"

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct config *config = state->input;
	switch (key) {
	case 'a':
		strcpy(config->address, arg);
		break;
	case 'p':
		config->port = strtoul(arg, 0L, 10);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}