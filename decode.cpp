/*
 * decode.cpp
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

#include <CImg.h>

#include <string>
#include "jastegal.h"

using namespace std;
using namespace cimg_library;

string steganoDecode (string inImg)  {
	CImg<u8> img(inImg.c_str());
	rgb header[8];
	string content;
	unsigned int uLen, size = 0;

	for (unsigned int i=0; i < 8; i++)  {
		header[i].r = img[3*i];
		header[i].g = img[3*i + 1];
		header[i].b = img[3*i + 2];
	}

	for (unsigned int i=0; i < 8; i++)  {
		size |= ((header[i].r & 0x3) << (i*4));
		size |= ((header[i].b & 0x3) << ((i*4)+2));
	}
	
	for (unsigned int i=6*sizeof(unsigned int); i < 6*(size + sizeof(unsigned int)); i+=6)  {
		rgb couple[2];
		u8 buf = 0;

		for (unsigned int j=0; j<2; j++)  {
			couple[j].r = img[i + 3*j];
			couple[j].g = img[i + 3*j + 1];
			couple[j].b = img[i + 3*j + 2];
		}

		buf = 
			( ((couple[0].r & 0x3) << 6) |
			  ((couple[0].b & 0x3) << 4) |
			  ((couple[1].r & 0x3) << 2) |
			  ((couple[1].b & 0x3)) );

		content += buf;
	}

	char *uncompressed = zUncompress((char*) content.c_str(), size, uLen);

	if (!uncompressed)
		return string("");

	return string(uncompressed);
}

