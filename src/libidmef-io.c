/*****
*
* Copyright (C) 2001-2016 CS-SI. All Rights Reserved.
* Author: Yoann Vandoorselaere <yoann.v@libidmef-ids.com>
*
* This file is part of the LibIdmef library.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*****/

#include "config.h"
#include "libmissing.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/ioctl.h>

#include "libidmef-inttypes.h"

#ifdef HAVE_SYS_FILIO_H
# include <sys/filio.h>
#endif


#include "libidmef-log.h"
#include "libidmef-io.h"
#include "common.h"


#define LIBIDMEF_ERROR_SOURCE_DEFAULT LIBIDMEF_ERROR_SOURCE_IO
#include "libidmef-error.h"


#define CHUNK_SIZE 1024

#ifndef MIN
# define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

struct libidmef_io {

        int fd;
        void *fd_ptr;

        size_t size;
        size_t rindex;

        int (*close)(libidmef_io_t *pio);
        ssize_t (*read)(libidmef_io_t *pio, void *buf, size_t count);
        ssize_t (*write)(libidmef_io_t *pio, const void *buf, size_t count);
        ssize_t (*pending)(libidmef_io_t *pio);
};



/*
 * Buffer IO functions.
 */
static ssize_t buffer_read(libidmef_io_t *pio, void *buf, size_t count)
{
        if ( pio->size - pio->rindex == 0 )
                return 0;

        count = MIN(count, pio->size - pio->rindex);

        memcpy(buf, (unsigned char *) pio->fd_ptr + pio->rindex, count);
        pio->rindex += count;

        return count;
}



static ssize_t buffer_write(libidmef_io_t *pio, const void *buf, size_t count)
{
        unsigned char *new;

        if ( pio->size + count <= pio->size )
                return -1;

        new = _libidmef_realloc(pio->fd_ptr, pio->size + count);
        if ( ! new )
                return libidmef_error_from_errno(errno);

        memcpy(new + pio->size, buf, count);

        pio->fd_ptr = new;
        pio->size += count;

        return count;
}



static int buffer_close(libidmef_io_t *pio)
{
        if ( pio->fd_ptr ) {
                free(pio->fd_ptr);
                pio->fd_ptr = NULL;
                pio->size = pio->rindex = 0;
        }

        return 0;
}



static ssize_t buffer_pending(libidmef_io_t *pio)
{
        return pio->size - pio->rindex;
}




/*
 * System IO functions.
 */
static ssize_t sys_read(libidmef_io_t *pio, void *buf, size_t count)
{
        ssize_t ret;

        do {
                ret = read(pio->fd, buf, count);
        } while ( ret < 0 && errno == EINTR );

        if ( ret == 0 )
                return libidmef_error(LIBIDMEF_ERROR_EOF);

        if ( ret < 0 ) {
#ifdef ECONNRESET
                if ( errno == ECONNRESET )
                        return libidmef_error(LIBIDMEF_ERROR_EOF);
#endif
                return libidmef_error_from_errno(errno);
        }

        return ret;
}



static ssize_t sys_write(libidmef_io_t *pio, const void *buf, size_t count)
{
        ssize_t ret;

        do {
                ret = write(pio->fd, buf, count);
        } while ( ret < 0 && errno == EINTR );

        if ( ret < 0 )
                return libidmef_error_from_errno(errno);

        return ret;
}



static int sys_close(libidmef_io_t *pio)
{
        int ret;

        do {
                ret = close(pio->fd);
        } while ( ret < 0 && errno == EINTR );

        return (ret >= 0) ? ret : libidmef_error_from_errno(errno);
}



static ssize_t sys_pending(libidmef_io_t *pio)
{
        long ret = 0;

        if ( ioctl(pio->fd, FIONREAD, &ret) < 0 )
                return libidmef_error_from_errno(errno);

        return ret;
}




/*
 * Buffered IO functions.
 */
static ssize_t file_read(libidmef_io_t *pio, void *buf, size_t count)
{
        FILE *fd;
        size_t ret;

        /*
         * ferror / clearerror can be macro that might dereference fd_ptr.
         */
        fd = pio->fd_ptr;
        libidmef_return_val_if_fail(fd, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        ret = fread(buf, count, 1, fd);
        if ( ret <= 0 ) {
                ret = ferror(fd) ? libidmef_error_from_errno(errno) : libidmef_error(LIBIDMEF_ERROR_EOF);
                clearerr(fd);
                return ret;
        }

        /*
         * fread return the number of *item* read.
         */
        return count;
}



static ssize_t file_write(libidmef_io_t *pio, const void *buf, size_t count)
{
        size_t ret;

        libidmef_return_val_if_fail(pio->fd_ptr, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        ret = fwrite(buf, count, 1, pio->fd_ptr);
        if ( ret <= 0 )
                return ret;

        /*
         * fwrite return the number of *item* written.
         */
        return count;
}



static int file_close(libidmef_io_t *pio)
{
        libidmef_return_val_if_fail(pio->fd_ptr, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        return fclose(pio->fd_ptr);
}



static ssize_t file_pending(libidmef_io_t *pio)
{
#ifdef ENOTSUP
        return libidmef_error_from_errno(ENOTSUP);
#else
        return libidmef_error(LIBIDMEF_ERROR_GENERIC);
#endif
}




/*
 * Forward data from one fd to another using copy.
 */
static ssize_t copy_forward(libidmef_io_t *dst, libidmef_io_t *src, size_t count)
{
        int ret;
        size_t scount;
        unsigned char buf[8192];

        scount = count;

        while ( count ) {

                ret = (count < sizeof(buf)) ? count : sizeof(buf);

                ret = libidmef_io_read(src, buf, ret);
                if ( ret <= 0 )
                        return ret;

                count -= ret;

                ret = libidmef_io_write(dst, buf, ret);
                if ( ret < 0 )
                        return ret;
        }

        return scount;
}





/**
 * libidmef_io_forward:
 * @src: Pointer to a #libidmef_io_t object.
 * @dst: Pointer to a #libidmef_io_t object.
 * @count: Number of byte to forward from @src to @dst.
 *
 * libidmef_io_forward() attempts to transfer up to @count bytes from
 * the file descriptor identified by @src into the file descriptor
 * identified by @dst.
 *
 * Returns: If the transfer was successful, the number of bytes written
 * to @dst is returned.  On error, -1 is returned, and errno is set appropriately.
 */
ssize_t libidmef_io_forward(libidmef_io_t *dst, libidmef_io_t *src, size_t count)
{
        libidmef_return_val_if_fail(dst, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(src, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        return copy_forward(dst, src, count);
}




/**
 * libidmef_io_read:
 * @pio: Pointer to a #libidmef_io_t object.
 * @buf: Pointer to the buffer to store data into.
 * @count: Number of bytes to read.
 *
 * libidmef_io_read() attempts to read up to @count bytes from the
 * file descriptor identified by @pio into the buffer starting at @buf.
 *
 * If @count is zero, libidmef_io_read() returns zero and has no other
 * results. If @count is greater than SSIZE_MAX, the result is unspecified.
 *
 * The case where the read function would be interrupted by a signal is
 * handled internally. So you don't have to check for EINTR.
 *
 * Returns: On success, the number of bytes read is returned (zero
 * indicates end of file). It is not an error if this number is smaller
 * than the number of bytes requested; this may happen for example because
 * fewer bytes are actually available right now or because read() was
 * interrupted by a signal.
 *
 * On error, a negative value is returned. In this case it is left unspecified
 * whether the file position (if any) changes.
 */
ssize_t libidmef_io_read(libidmef_io_t *pio, void *buf, size_t count)
{
        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(pio->read, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(buf, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        return pio->read(pio, buf, count);
}




/**
 * libidmef_io_read_wait:
 * @pio: Pointer to a #libidmef_io_t object.
 * @buf: Pointer to the buffer to store data into.
 * @count: Number of bytes to read.
 *
 * libidmef_io_read_wait() attempts to read up to @count bytes from the
 * file descriptor identified by @pio into the buffer starting at @buf.
 *
 * If @count is zero, libidmef_io_read() returns zero and has no other
 * results. If @count is greater than SSIZE_MAX, the result is unspecified.
 *
 * The case where the read function would be interrupted by a signal is
 * handled internally. So you don't have to check for EINTR.
 *
 * libidmef_io_read_wait() always return the number of bytes requested.
 * Be carefull that this function is blocking.
 *
 * Returns: On success, the number of bytes read is returned (zero
 * indicates end of file).
 *
 * On error, -1 is returned, and errno is set appropriately. In this
 * case it is left unspecified whether the file position (if any) changes.
 */
ssize_t libidmef_io_read_wait(libidmef_io_t *pio, void *buf, size_t count)
{
        ssize_t ret;
        size_t n = 0;
        struct pollfd pfd;
        unsigned char *in = buf;

        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(buf, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        pfd.fd = libidmef_io_get_fd(pio);
        pfd.events = POLLIN;

        do {
                ret = poll(&pfd, 1, -1);
                if ( ret < 0 )
                        return libidmef_error_from_errno(errno);

                if ( ! (pfd.revents & POLLIN) )
                        return libidmef_error_verbose(LIBIDMEF_ERROR_GENERIC, "expected POLLIN event");

                ret = libidmef_io_read(pio, &in[n], count - n);
                if ( ret < 0 )
                        return ret;

                n += (size_t) ret;

        } while ( n != count );

        return (ssize_t) n;
}



/**
 * libidmef_io_read_delimited:
 * @pio: Pointer to a #libidmef_io_t object.
 * @buf: Pointer to the address of a buffer to store address of data into.
 *
 * libidmef_io_read_delimited() read message written by libidmef_write_delimited().
 * Theses messages are sents along with the len of the message.
 *
 * Uppon return the @buf argument is updated to point on a newly allocated
 * buffer containing the data read. The @count argument is set to the number of
 * bytes the message was containing.
 *
 * The case where the read function would be interrupted by a signal is
 * handled internally. So you don't have to check for EINTR.
 *
 * Returns: On success, the number of bytes read is returned (zero
 * indicates end of file).
 *
 * On error, -1 is returned, and errno is set appropriately. In this
 * case it is left unspecified whether the file position (if any) changes.
 */
ssize_t libidmef_io_read_delimited(libidmef_io_t *pio, unsigned char **buf)
{
        ssize_t ret;
        size_t count;
        uint16_t msglen;

        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        ret = libidmef_io_read_wait(pio, &msglen, sizeof(msglen));
        if ( ret <= 0 )
                return ret;

        count = ntohs(msglen);

        *buf = malloc(count);
        if ( ! *buf )
                return libidmef_error_from_errno(errno);

        ret = libidmef_io_read_wait(pio, *buf, count);
        if ( ret < 0 )
                return ret;

        return count;
}




/**
 * libidmef_io_write:
 * @pio: Pointer to a #libidmef_io_t object.
 * @buf: Pointer to the buffer to write data from.
 * @count: Number of bytes to write.
 *
 * libidmef_io_write() writes up to @count bytes to the file descriptor
 * identified by @pio from the buffer starting at @buf. POSIX requires
 * that a read() which can be proved to occur after a write() has returned
 * returns the new data. Note that not all file systems are POSIX conforming.
 *
 * The case where the write() function would be interrupted by a signal is
 * handled internally. So you don't have to check for EINTR.
 *
 * Returns: On success, the number of bytes written are returned (zero
 * indicates nothing was written). On error, -1 is returned, and errno
 * is set appropriately. If @count is zero and the file descriptor refers
 * to a regular file, 0 will be returned without causing any other effect.
 * For a special file, the results are not portable.
 */
ssize_t libidmef_io_write(libidmef_io_t *pio, const void *buf, size_t count)
{
        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(pio->write, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(buf, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        return pio->write(pio, buf, count);
}



/**
 * libidmef_io_write_delimited:
 * @pio: Pointer to a #libidmef_io_t object.
 * @buf: Pointer to the buffer to write data from.
 * @count: Number of bytes to write.
 *
 * libidmef_io_write_delimited() writes up to @count bytes to the file descriptor
 * identified by @pio from the buffer starting at @buf. POSIX requires
 * that a read() which can be proved to occur after a write() has returned
 * returns the new data. Note that not all file systems are POSIX conforming.
 *
 * libidmef_io_write_delimited() also write the len of the data to be sent.
 * which allow libidmef_io_read_delimited() to safely know if it got all the
 * data a given write contain.
 *
 * The case where the write() function would be interrupted by a signal is
 * handled internally. So you don't have to check for EINTR.
 *
 * Returns: On success, the number of bytes written are returned (zero
 * indicates nothing was written). On error, -1 is returned, and errno
 * is set appropriately.
 */
ssize_t libidmef_io_write_delimited(libidmef_io_t *pio, const void *buf, uint16_t count)
{
        int ret;
        uint16_t nlen;

        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(buf, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        nlen = htons(count);

        ret = libidmef_io_write(pio, &nlen, sizeof(nlen));
        if ( ret <= 0 )
                return ret;

        ret = libidmef_io_write(pio, buf, count);
        if ( ret <= 0 )
                return ret;

        return count;
}




/**
 * libidmef_io_close:
 * @pio: Pointer to a #libidmef_io_t object.
 *
 * libidmef_io_close() closes the file descriptor indentified by @pio,
 *
 * The case where the close() function would be interrupted by a signal is
 * handled internally. So you don't have to check for EINTR.
 *
 * However, and especially when the underlaying layer is TLS, libidmef_io_close()
 * might return error. If this happen, you should continue calling the function
 * until it return zero.
 *
 * Returns: zero on success, or -1 if an error occurred.
 */
int libidmef_io_close(libidmef_io_t *pio)
{
        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        libidmef_return_val_if_fail(pio->close, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        return pio->close(pio);
}




/**
 * libidmef_io_new:
 * @ret: Pointer where to store the created #libidmef_io_t object.
 *
 * Create a new libidmef IO object.
 *
 * Returns: 0 on success, or a negative value if an error occur.
 */
int libidmef_io_new(libidmef_io_t **ret)
{
        *ret = calloc(1, sizeof(**ret));
        if ( ! *ret )
                return libidmef_error_from_errno(errno);

        return 0;
}



/**
 * libidmef_io_set_file_io:
 * @pio: A pointer on the #libidmef_io_t object.
 * @fd: File descriptor identifying a file.
 *
 * Setup the @pio object to work with file I/O function.
 * The @pio object is then associated with @fd.
 */
void libidmef_io_set_file_io(libidmef_io_t *pio, FILE *fdptr)
{
        libidmef_return_if_fail(pio);
        libidmef_return_if_fail(fdptr);

        pio->fd = fileno(fdptr);
        pio->fd_ptr = fdptr;
        pio->read = file_read;
        pio->write = file_write;
        pio->close = file_close;
        pio->pending = file_pending;
}





/**
 * libidmef_io_set_sys_io:
 * @pio: A pointer on the #libidmef_io_t object.
 * @fd: A file descriptor.
 *
 * Setup the @pio object to work with system based I/O function.
 * The @pio object is then associated with @fd.
 */
void libidmef_io_set_sys_io(libidmef_io_t *pio, int fd)
{
        libidmef_return_if_fail(pio);

        pio->fd = fd;
        pio->fd_ptr = NULL;
        pio->read = sys_read;
        pio->write = sys_write;
        pio->close = sys_close;
        pio->pending = sys_pending;
}



int libidmef_io_set_buffer_io(libidmef_io_t *pio)
{
        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));

        pio->fd_ptr = NULL;
        pio->size = pio->rindex = 0;

        pio->read = buffer_read;
        pio->write = buffer_write;
        pio->close = buffer_close;
        pio->pending = buffer_pending;

        return 0;
}



/**
 * libidmef_io_get_fd:
 * @pio: A pointer on a #libidmef_io_t object.
 *
 * Returns: The FD associated with this object.
 */
int libidmef_io_get_fd(libidmef_io_t *pio)
{
        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        return pio->fd;
}



/**
 * libidmef_io_get_fdptr:
 * @pio: A pointer on a #libidmef_io_t object.
 *
 * Returns: Pointer associated with this object (file, tls, buffer, or NULL).
 */
void *libidmef_io_get_fdptr(libidmef_io_t *pio)
{
        libidmef_return_val_if_fail(pio, NULL);
        return pio->fd_ptr;
}



/**
 * libidmef_io_destroy:
 * @pio: Pointer to a #libidmef_io_t object.
 *
 * Destroy the @pio object.
 */
void libidmef_io_destroy(libidmef_io_t *pio)
{
        libidmef_return_if_fail(pio);
        free(pio);
}




/**
 * libidmef_io_pending:
 * @pio: Pointer to a #libidmef_io_t object.
 *
 * libidmef_io_pending return the number of bytes waiting to
 * be read on an TLS or socket fd.
 *
 * Returns: Number of byte waiting to be read on @pio, or -1
 * if @pio is not of type TLS or socket.
 */
ssize_t libidmef_io_pending(libidmef_io_t *pio)
{
        libidmef_return_val_if_fail(pio, libidmef_error(LIBIDMEF_ERROR_ASSERTION));
        return pio->pending(pio);
}




/**
 * libidmef_io_is_error_fatal:
 * @pio: Pointer to a #libidmef_io_t object.
 * @error: Error returned by one of the #libidmef_io_t function.
 *
 * Check whether the returned error is fatal, or not.
 *
 * Returns: TRUE if error is fatal, FALSE if it is not.
 */
libidmef_bool_t libidmef_io_is_error_fatal(libidmef_io_t *pio, int error)
{
        libidmef_error_code_t code;

        libidmef_return_val_if_fail(pio, FALSE);

        if ( ! error )
                return FALSE;

        code = libidmef_error_get_code(error);
        if ( code == LIBIDMEF_ERROR_EAGAIN || code == LIBIDMEF_ERROR_EINTR || code == LIBIDMEF_ERROR_TLS_WARNING_ALERT )
                return FALSE;

        return TRUE;
}



/**
 * libidmef_io_set_write_callback:
 * @pio: Pointer to a #libidmef_io_t object.
 * @write: Callback function to be called on libidmef_io_write().
 *
 * Set an user defined write callback function to be called on
 * libidmef_io_write().
 */
void libidmef_io_set_write_callback(libidmef_io_t *pio, ssize_t (*write)(libidmef_io_t *io, const void *buf, size_t count))
{
        pio->write = write;
}


/**
 * libidmef_io_set_read_callback:
 * @pio: Pointer to a #libidmef_io_t object.
 * @read: Callback function to be called on libidmef_io_read().
 *
 * Set an user defined read callback function to be called on
 * libidmef_io_read().
 */
void libidmef_io_set_read_callback(libidmef_io_t *pio, ssize_t (*read)(libidmef_io_t *io, void *buf, size_t count))
{
        pio->read = read;
}



/**
 * libidmef_io_set_pending_callback:
 * @pio: Pointer to a #libidmef_io_t object.
 * @pending: Callback function to be called on libidmef_io_pending().
 *
 * Set an user defined read callback function to be called on
 * libidmef_io_pending().
 */
void libidmef_io_set_pending_callback(libidmef_io_t *pio, ssize_t (*pending)(libidmef_io_t *io))
{
        pio->pending = pending;
}



/**
 * libidmef_io_set_fdptr:
 * @pio: Pointer to a #libidmef_io_t object.
 * @ptr: Pointer to user defined data.
 *
 * Set an user defined pointer that might be retrieved using
 * libidmef_io_get_fdptr().
 */
void libidmef_io_set_fdptr(libidmef_io_t *pio, void *ptr)
{
        pio->fd_ptr = ptr;
}
