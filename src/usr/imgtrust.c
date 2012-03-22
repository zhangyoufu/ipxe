/*
 * Copyright (C) 2012 Michael Brown <mbrown@fensystems.co.uk>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

FILE_LICENCE ( GPL2_OR_LATER );

#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <ipxe/uaccess.h>
#include <ipxe/image.h>
#include <ipxe/cms.h>
#include <usr/imgtrust.h>

/** @file
 *
 * Image trust management
 *
 */

/**
 * Verify image using downloaded signature
 *
 * @v image		Image to verify
 * @v signature		Image containing signature
 * @v name		Required common name, or NULL to allow any name
 * @ret rc		Return status code
 */
int imgverify ( struct image *image, struct image *signature,
		const char *name ) {
	size_t len;
	void *data;
	struct cms_signature sig;
	time_t now;
	int rc;

	/* Mark image as untrusted */
	image_untrust ( image );

	/* Copy signature to internal memory */
	len = signature->len;
	data = malloc ( len );
	if ( ! data ) {
		rc = -ENOMEM;
		goto err_alloc;
	}
	copy_from_user ( data, signature->data, 0, len );

	/* Parse signature */
	if ( ( rc = cms_parse ( &sig, data, len ) ) != 0 )
		goto err_parse;

	/* Use signature to verify image */
	now = time ( NULL );
	if ( ( rc = cms_verify ( &sig, image->data, image->len,
				 name, now, NULL ) ) != 0 )
		goto err_verify;

	/* Mark image as trusted */
	image_trust ( image );

 err_verify:
 err_parse:
	free ( data );
 err_alloc:
	return rc;
}
