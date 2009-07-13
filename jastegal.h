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

#ifndef __JASTEGAL_H
#define __JASTEGAL_H

#ifndef __cplusplus
#error  "You need a C++ compiler to compile Jastegal"
#endif

#include <string>
#include <vector>

#define JASTEGAL_VERSION   "0.1b"

typedef unsigned char u8;
typedef enum  { undef, encode, decode } action;

typedef struct  {
	u8 r;
	u8 g;
	u8 b;
} rgb;

int steganoEncode (std::string inImg, std::string outImg, std::string fname = "");

std::string steganoDecode (std::string inImg);

std::vector<u8> bitsplit (u8 data);

unsigned int fileSize (std::string fname);

std::string fileContent (std::string fname);

void printHelp (std::string arg);

char* zCompress (char* uncompressed, unsigned int uLen, unsigned int &cLen);

char* zUncompress (char* compressed, unsigned int cLen, unsigned int &uLen);

#endif

