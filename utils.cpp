/*
 * utils.cpp
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
#include <fstream>

#include "jastegal.h"
using namespace std;

vector<u8> bitsplit (u8 data)  {
	unsigned int size = sizeof(data)*8;
	u8* bits = new u8[size+1];

	for (int i=size-1; i>=0; i--)
		bits[size-i-1] = (data & (1 << i)) >> i;

	vector<u8> v;
	v.assign(bits, bits+size);
	delete [] bits;
	return v;
}

unsigned int fileSize (string fname)  {
	ifstream in(fname.c_str());

	if (!in)
		return -1;

	in.seekg(0, ios::end);
	unsigned int size = in.tellg();
	in.close();
	return size;
}

string fileContent (string fname)  {
	if (!fname.empty())  {
		char *buf = NULL;
		ifstream in(fname.c_str());

		if (!in)
			return string("");

		unsigned int size = fileSize(fname);
		buf = new char[size];

		if (!buf)
			return string("");

		in.read(buf,size);
		in.close();
		return string(buf);
	} else {
		string content, line;

		while (getline(cin,line))
			content.append(line);

		return content;
	}
}

void printHelp (string arg)  {
	cerr << "Jastegal (Just Another Steganography Algorithm) v." << JASTEGAL_VERSION << endl
		<< "c0ded by BlackLight <blacklight@autistici.org>" << endl << endl
		<< "Usage: " << arg << " [-d|-e] <-i image file> [-o output image file] [-f file to be steganographied]" << endl << endl
		<< "-d:\t\tPerform a decoding from an image" << endl
		<< "-e:\t\tPerform an encoding to an image" << endl
		<< "-i:\t\tSpecify the input image to be processed. In case of decoding, the content of this file will be de-steganographied," << endl
		<< "\t\twhile in case of encoding this is the image to steganography from" << endl
		<< "-o:\t\tSpecify the output image. This parameter is mandatory in encoding phase, as it specifies the file name containing" << endl
		<< "\t\tthe image with the steganographied data" << endl
		<< "-f:\t\tSpecify, in encoding phase, the file containing data to be steganographied. If this option is not specified, the" << endl
		<< "\t\tdata will be gathered via stdin" << endl << endl
		<< "Examples:" << endl
		<< "\tjastegal -e -i input_image.png -o output_image.png -f file.txt" << endl
		<< "\tThis will encode the data in file.txt using input_image.png as image, and putting the output in output_image.png" << endl << endl
		<< "\tjastegal -d -i input_image.png" << endl
		<< "\tThis will decode the data in input_image.png to stdout" << endl;
}

