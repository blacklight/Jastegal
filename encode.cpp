/*
 * encode.cpp
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

#include <iostream>
#include <string>
#include <vector>

#include "jastegal.h"

using namespace std;
using namespace cimg_library;

int steganoEncode (string inImg, string outImg, string fname)  {
	CImg<u8> img(inImg.c_str());
	string::iterator ch;
	string content = fileContent(fname);

	unsigned int i, j, k, cLen, size = (fname.empty()) ? content.size() : fileSize(fname);
	char *compressed = zCompress((char*) content.c_str(), size, cLen);

	cout << "Working...\n";

	if (!compressed)
		return 1;

	if ((unsigned int) (6*img.dimx()*img.dimy()) <= cLen)  {
		cerr << "Error: file " << fname << " is too long to be steganographied inside image " << inImg << endl;
		return 1;
	}

	u8 *buf = new u8[sizeof(unsigned int)];
	memcpy (buf, &size, sizeof(unsigned int));

	for (i=0; i < 6*sizeof(unsigned int); i+=6)  {
		unsigned int k = ((int) i/6);

		buf[k] = (
				((buf[k] & 0x03) << 6) |
				((buf[k] & 0x0c) << 2) |
				((buf[k] & 0x30) >> 2) |
				((buf[k] & 0xc0) >> 6));

		vector<u8> sizebits = bitsplit(buf[k]);
	
		for (j=0; j < sizebits.size(); j+=2)  {
			unsigned int index;
			u8 operand = (sizebits[j] << 1) | sizebits[j+1];

			switch (j)  {
				case 0: index = i  ; break;
				case 2: index = i+2; break;
				case 4: index = i+3; break;
				case 6: index = i+5; break;
			}

			img[index] = ((img[index] & 0xfc) | operand);
		}
	}

	//for (i=6*sizeof(unsigned int), ch = content.begin(); ch < content.end(); i+=6, ch++)  {
	for (i=6*sizeof(unsigned int), k=0; k < cLen; i+=6, k++)  {
		vector<u8> bits = bitsplit(compressed[k]);
		
		for (j=0; j < bits.size(); j+=2)  {
			unsigned int index;
			u8 operand = (bits[j] << 1) | bits[j+1];

			switch (j)  {
				case 0: index=i  ; break;
				case 2: index=i+2; break;
				case 4: index=i+3; break;
				case 6: index=i+5; break;
			}

			img[index] = (img[index] & 0xfc) | operand;
		}
	}

	img.save(outImg.c_str());
	img.clear();

	if (compressed)
		delete [] compressed;

	return 0;
}

