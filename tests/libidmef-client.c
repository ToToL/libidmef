#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libidmef.h"


int main(int argc, char **argv)
{
        int ret;
        libidmef_client_t *client;

        assert(libidmef_init(&argc, argv) == 0);
        assert(libidmef_client_new(&client, "Client that does not exist") == 0);
        assert((ret = libidmef_client_start(client)) < 0);
        assert(libidmef_error_get_code(ret) == LIBIDMEF_ERROR_PROFILE);

        libidmef_client_destroy(client, LIBIDMEF_CLIENT_EXIT_STATUS_FAILURE);
        libidmef_deinit();

        return 0;
}
