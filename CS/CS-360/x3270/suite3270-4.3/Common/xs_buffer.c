/*
 * Copyright (c) 1993-2015 Paul Mattes.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the names of Paul Mattes, Jeff Sparkes nor the names of their
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY PAUL MATTES "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL PAUL MATTES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *	xs_buffer.c
 *		Simplified version of asprintf/vsprintf.
 */

#include "globals.h"

#include "asprintf.h"
#include "utils.h"

/**
 * Local variation of vasprintf(). Returns the buffer instead of a count, and
 * crashes if it runs out of memory.
 *
 * @param[in] fmt	printf format string
 * @param[in] args	argument list
 *
 * @return malloc'd buffer, guaranteed not to be NULL. Must free() when done.
 */
char *
xs_vbuffer(const char *fmt, va_list args)
{
    char *r = NULL;
    int nw;

    nw = vasprintf(&r, fmt, args);
    if (nw < 0) {
	Error("xs_vbuffer: vasprintf failure");
    }
    if (r == NULL) {
	Error("Out of memory");
    }
    return r;
}

/**
 * Local variation of vsprintf(). Returns the buffer instead of a count, and
 * crashes if it runs out of memory.
 *
 * @param[in] fmt	printf format string
 *
 * @return malloc'd buffer, guaranteed not to be NULL. Must free() when done.
 */
char *
xs_buffer(const char *fmt, ...)
{
    va_list args;
    char *r;

    va_start(args, fmt);
    r = xs_vbuffer(fmt, args);
    va_end(args);
    return r;
}
