#include "config.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <gettext.h>
#include <errno.h>

#include "libidmef-log.h"
#include "libidmef-error.h"

#include "code-to-errno.h"
#include "code-from-errno.h"


#define LIBIDMEF_ERROR_CODE_DIM     65536
#define LIBIDMEF_ERROR_SOURCE_DIM     256

#define LIBIDMEF_ERROR_SOURCE_SHIFT    23
#define LIBIDMEF_ERROR_VERBOSE_SHIFT   22

#define LIBIDMEF_ERROR_CODE_MASK       (LIBIDMEF_ERROR_CODE_DIM - 1)
#define LIBIDMEF_ERROR_SOURCE_MASK     (LIBIDMEF_ERROR_SOURCE_DIM - 1)
#define LIBIDMEF_ERROR_VERBOSE_MASK    (1)


/**
 * libidmef_error_make:
 * @source: Error source.
 * @code: Error code.
 *
 * Create a new #libidmef_error_t error using @source and @code.
 *
 * Returns: The created #libidmef_error_t integer.
 */
libidmef_error_t libidmef_error_make(libidmef_error_source_t source, libidmef_error_code_t code)
{
        return (code == LIBIDMEF_ERROR_NO_ERROR) ? code : -((source << LIBIDMEF_ERROR_SOURCE_SHIFT) | code);
}


/**
 * libidmef_error_make_from_errno:
 * @source: Error source.
 * @err: errno value.
 *
 * Create a new #libidmef_error_t error using @source and @errno.
 *
 * Returns: The created #libidmef_error_t integer.
 */
libidmef_error_t libidmef_error_make_from_errno(libidmef_error_source_t source, int err)
{
        libidmef_error_code_t code = libidmef_error_code_from_errno(err);
        return libidmef_error_make(source, code);
}



/**
 * libidmef_error_verbose_make_v:
 * @source: Error source.
 * @code: Error code.
 * @fmt: Format string.
 * @ap: Argument list.
 *
 * Create a new error using @source and @code, using the detailed error message
 * specified within @fmt.
 *
 * Returns: The created #libidmef_error_t integer.
 */
libidmef_error_t libidmef_error_verbose_make_v(libidmef_error_source_t source,
                                             libidmef_error_code_t code, const char *fmt, va_list ap)
{
        int ret;

        ret = libidmef_error_make(source, code);
        ret = -ret;
        ret |= (1 << LIBIDMEF_ERROR_VERBOSE_SHIFT);

        return -ret;
}



/**
 * libidmef_error_verbose_make:
 * @source: Error source.
 * @code: Error code.
 * @fmt: Format string.
 * @...: Argument list.
 *
 * Create a new error using @source and @code, using the detailed error message
 * specified within @fmt.
 *
 * Returns: The created #libidmef_error_t integer.
 */
libidmef_error_t libidmef_error_verbose_make(libidmef_error_source_t source,
                                           libidmef_error_code_t code, const char *fmt, ...)
{
        int ret;
        va_list ap;

        va_start(ap, fmt);
        ret = libidmef_error_verbose_make_v(source, code, fmt, ap);
        va_end(ap);

        return ret;
}


/**
 * libidmef_error_get_code:
 * @error: A #libidmef_error_t return value.
 *
 * Returns: the #libidmef_code_t code contained within the @libidmef_error_t integer.
 */
libidmef_error_code_t libidmef_error_get_code(libidmef_error_t error)
{
        error = -error;
        return (libidmef_error_code_t) (error & LIBIDMEF_ERROR_CODE_MASK);
}


/**
 * libidmef_error_get_source:
 * @error: A #libidmef_error_t return value.
 *
 * Returns: the #libidmef_source_t source contained within the @libidmef_error_t integer.
 */
libidmef_error_source_t libidmef_error_get_source(libidmef_error_t error)
{
        error = -error;
        return (libidmef_error_source_t) ((error >> LIBIDMEF_ERROR_SOURCE_SHIFT) & LIBIDMEF_ERROR_SOURCE_MASK);
}


/**
 * libidmef_error_is_verbose:
 * @error: A #libidmef_error_t return value.
 *
 * Returns: #LIBIDMEF_BOOL_TRUE if there is a detailed message for this error, #LIBIDMEF_BOOL_FALSE otherwise.
 */
libidmef_bool_t libidmef_error_is_verbose(libidmef_error_t error)
{
        error = -error;
        return ((error >> LIBIDMEF_ERROR_VERBOSE_SHIFT) & LIBIDMEF_ERROR_VERBOSE_MASK) ? LIBIDMEF_BOOL_TRUE : LIBIDMEF_BOOL_FALSE;
}


/**
 * libidmef_error_code_from_errno:
 * @err: errno value.
 *
 * Returns: the #libidmef_error_code_t value corresponding to @err.
 */
libidmef_error_code_t libidmef_error_code_from_errno(int err)
{
        int idx;

        if ( ! err )
                return LIBIDMEF_ERROR_NO_ERROR;

        idx = errno_to_idx(err);
        if ( idx < 0 )
                return LIBIDMEF_ERROR_UNKNOWN_ERRNO;

        return LIBIDMEF_ERROR_SYSTEM_ERROR | err_code_from_index[idx];
}


/**
 * libidmef_error_code_to_errno:
 * @code: Error code.
 *
 * Returns: the errno value corresponding to @code.
 */
int libidmef_error_code_to_errno(libidmef_error_code_t code)
{
        if ( ! (code & LIBIDMEF_ERROR_SYSTEM_ERROR) )
                return 0;

        code &= ~LIBIDMEF_ERROR_SYSTEM_ERROR;

        if ( code < sizeof(err_code_to_errno) / sizeof(err_code_to_errno[0]) )
                return err_code_to_errno[code];
        else
                return 0;
}



/**
 * libidmef_perror:
 * @error: A #libidmef_error_t return value.
 * @fmt: Format string.
 * @...: Argument list.
 *
 * Print the error to stderr, or to syslog() in case stderr is unavailable.
 */
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
