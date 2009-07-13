/*
 * jastegal.cpp
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
#include <unistd.h>

#include "jastegal.h"

using namespace std;
using namespace cimg_library;

int main (int argc, char **argv)  {
	int ch;
	string inImg, outImg, fname;
	action act = undef;

	while ((ch=getopt(argc,argv,"edi:o:f:"))>0)  {
		switch (ch)  {
			case 'i':
				inImg = string(optarg);
				break;
			
			case 'o':
				outImg = string(optarg);
				break;

			case 'd':
				if (act != undef)  {
					cerr << "Error: you can use a flag between -d (decode) and -e (encode) a time\n\n";
					printHelp(argv[0]);
					return 1;
				}

				act = decode;
				break;

			case 'e':
				if (act == decode)  {
					cerr << "Error: you can use a flag between -d (decode) and -e (encode) a time\n\n";
					printHelp(argv[0]);
					return 1;
				}

				act = encode;
				break;

			case 'f':
				fname = string(optarg);
				break;
		}
	}

	if (act == undef)  {
		cerr << "Error: you must specify an action between decoding (-d) and encoding (-e)\n\n";
		printHelp(argv[0]);
		return 1;
	}

	if (inImg.empty())  {
		printHelp(argv[0]);
		return 1;
	}

	if (act == encode)  {
		if (outImg.empty())  {
			cerr << "Error: you must specify a file name for the output image using -o option when encoding\n\n";
			printHelp(argv[0]);
			return 1;
		}

		if (fname.empty())
			cout << "Enter the input message to be steganographied [CTRL+D to end]:\n";

		if (steganoEncode (inImg, outImg, fname))  {
			cerr << "There was an unrecoverable error while processing the image. Exiting...\n";
			return 1;
		}

		cout << "The steganographied output was successfully written to " << outImg << endl;
	} else {
		cout << steganoDecode(inImg) << endl;
	}

	return 0;
}

