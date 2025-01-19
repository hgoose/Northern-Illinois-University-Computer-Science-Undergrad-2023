/*
 * Copyright (c) 2018, 2021-2022 Paul Mattes.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the names of Paul Mattes nor the names of his contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
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
 *	base64_test.c
 *		Base64 encoding tests.
 */

#include "globals.h"

#include <assert.h>

#include "base64.h"
#include "sa_malloc.h"

int
main(int argc, char *argv[])
{
    char *s[] = {
	"foobar",
	"x",
	"xy",
	"xyz",
	"abcãd",
	"username:password",
	"Bzz Bzz Bzz",
	NULL };
    int i;
    bool verbose = 0;

    if (argc > 1 && !strcmp(argv[1], "-v")) {
	verbose = true;
    }

    for (i = 0; s[i] != NULL; i++) {
	char *b = base64_encode(s[i]);
	char *e = base64_decode(b);

	if (verbose) {
	    printf("'%s' -> '%s' -> '%s'\n", s[i], b, e);
	}
	assert (!strcmp(s[i], e));
	Free(b);
	Free(e);
    }

    assert(base64_decode("a=b") == NULL);
    assert(base64_decode("a===") == NULL);
    assert(base64_decode("[") == NULL);

    sa_malloc_leak_check();

    printf("PASS\n");
    return 0;
}
