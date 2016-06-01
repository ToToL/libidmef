#include <stdio.h>
#include <stdarg.h>

#include "libidmef-log.h"
#include "libidmef-error.h"


void libidmef_perror(libidmef_error_t error, const char *fmt, ...)
{
	va_list ap;
	char buf[1024];
        
	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

        if ( libidmef_error_get_source(error) )
                libidmef_log(LIBIDMEF_LOG_WARN, "%s: %s: %s.\n", libidmef_strsource(error), buf, libidmef_strerror(error));
        else
                libidmef_log(LIBIDMEF_LOG_WARN, "%s: %s.\n", buf, libidmef_strerror(error));
}
