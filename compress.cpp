/*
 * jastegal.h
 *
 * The files in this directory and elsewhere which refer to this LICENCE
 * file are part of Jastegal (Just Another Steganography algorithm)
 *
 * Copyright (C) 2009 BlackLight
 *
 * Jastegal is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 or (at your option) any later 
 * version.
 *
 * Jastegal is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Jastegal; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * As a special exception, if other files instantiate templates or use
 * macros or inline functions from these files, or you compile these
 * files and link them with other works to produce a work based on these
 * files, these files do not by themselves cause the resulting work to be
 * covered by the GNU General Public License. However the source code for
 * these files must still be made available in accordance with section (3)
 * of the GNU General Public License.
 *
 * This exception does not invalidate any other reasons why a work based on
 * this file might be covered by the GNU General Public License.
 */

#include <iostream>
#include <string>
#include <zlib.h>

using namespace std;

char* zCompress (char* uncompressed, unsigned int uLen, unsigned int &cLen)  {
	char *compressed = new char[uLen+10];

	if (!compressed)
		return NULL;

	if (compress((Bytef*) compressed, (uLongf*) &cLen, (Bytef*) uncompressed, uLen) < 0)
		return NULL;

	return compressed;
}

char* zUncompress (char* compressed, unsigned int cLen, unsigned int &uLen)  {
	uLen = cLen;
	int ret = 4;
	char *uncompressed = NULL;

	while ((uLen < 4000000) && (ret != Z_OK))  {
		if (uncompressed)
			delete [] uncompressed;

		uncompressed = new char[uLen+10];

		if (!uncompressed)
			return NULL;

		ret = uncompress((Bytef*) uncompressed, (uLongf*) &uLen, (Bytef*) compressed, cLen);

		if (ret == Z_MEM_ERROR || ret == Z_BUF_ERROR)
			return NULL;

		if (ret != Z_OK)
			uLen *= 2;
	}

	return uncompressed;
}

