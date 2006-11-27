/*
* ========== Copyright Header Begin ==========================================
*
* Hypervisor Software File: prom_init.c
* 
* Copyright (c) 2006 Sun Microsystems, Inc. All Rights Reserved.
* 
*  - Do no alter or remove copyright notices
* 
*  - Redistribution and use of this software in source and binary forms, with 
*    or without modification, are permitted provided that the following 
*    conditions are met: 
* 
*  - Redistribution of source code must retain the above copyright notice, 
*    this list of conditions and the following disclaimer.
* 
*  - Redistribution in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution. 
* 
*    Neither the name of Sun Microsystems, Inc. or the names of contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
*     This software is provided "AS IS," without a warranty of any kind. 
* ALL EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, 
* INCLUDING ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN 
* MICROSYSTEMS, INC. ("SUN") AND ITS LICENSORS SHALL NOT BE LIABLE FOR 
* ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR 
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL SUN 
* OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR 
* FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE 
* DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
* ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF 
* SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* 
* You acknowledge that this software is not designed, licensed or
* intended for use in the design, construction, operation or maintenance of
* any nuclear facility. 
* 
* ========== Copyright Header End ============================================
*/
/*
 * Copyright (c) 2000-2003 Sun Microsystems, Inc.
 * All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"@(#)prom_init.c	1.1	00/08/07 SMI"

#include <sys/promif.h>
#include <sys/promimpl.h>

static void prom_fatal_error(const char *errormsg);

/*
 * This is the string we use to print out "panic" level messages.
 */
#define	PROMIF_CLNTNAMELEN	16
char	promif_clntname[PROMIF_CLNTNAMELEN];

/*
 * Every standalone that wants to use this library must call
 * prom_init() before any of the other routines can be called.
 */
void
prom_init(char *pgmname, void *p1275cif)
{

	/*
	 * Validate and register address of the client interface handler
	 */
	if (p1275_cif_init(p1275cif) == NULL)
		prom_fatal_error("promif: No interface!");

	/*
	 * Initialize the "clientname" string with the string we've
	 * been handed by the standalone
	 */
	(void) prom_strncpy(promif_clntname, "standalone-program",
			    PROMIF_CLNTNAMELEN - 1);
	promif_clntname[PROMIF_CLNTNAMELEN - 1] = '\0';
}

/*
 * Cant get to the prom interface. Try to cause a trap by
 * dividing by zero, leaving the message in %i0
 */
static void
prom_fatal_error(const char *errormsg)
{
	volatile int	zero = 0;
	volatile int	i = 1;

	i = i / zero;
	/*NOTREACHED*/
}
