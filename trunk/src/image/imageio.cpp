/***************************************************************************
 *   Copyright (C) 2005 by Jeff Ferr                                       *
 *   root@sat                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "imageio.h"

#include <stdlib.h>

#define PNG_DEBUG 3
#include <png.h>

namespace jlwuit {

ImageIO::ImageIO(std::string image, lwuit_pixelformat_t pixelformat)
{
	_image = image;
	_pixelformat = pixelformat;
	_quality = 0;
	_compression_level = 0;
}

ImageIO::~ImageIO()
{
}

void ImageIO::SetQuality(int quality)
{
	_quality = quality;
}

int ImageIO::GetQuality()
{
	return _quality;
}

void ImageIO::SetCompressionLevel(int level)
{
	_compression_level = level;
}

int ImageIO::GetCompressionLevel()
{
	return _compression_level;
}

bool ImageIO::Encode(uint32_t *rgb, int width, int height)
{
	png_byte color_type = PNG_COLOR_TYPE_RGBA;
	png_byte bit_depth = 8;

	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep * row_pointers;

	// create file 
	FILE *fp = fopen(_image.c_str(), "wb");
	if (!fp) {
		printf("[write_png_file] File %s could not be opened for writing", _image.c_str());

		return false;
	}

	// initialize stuff 
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr) {
		printf("[write_png_file] png_create_write_struct failed");

		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		printf("[write_png_file] png_create_info_struct failed");

		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Error during init_io");

		return false;
	}

	png_init_io(png_ptr, fp);

	// write header 
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Error during writing header");

		return false;
	}

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	// write bytes 
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Error during writing bytes");

		return false;
	}

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (int y=0; y<height; y++)
		row_pointers[y] = (png_byte*)malloc(info_ptr->rowbytes);

	for (int y=0; y<height; y++) {
		uint32_t *ptr = (uint32_t *)(row_pointers[y]);

		for (int x=0; x<width; x++) {
			uint32_t pixel = rgb[y*width+x] & 0xf8f8f8f8;
			uint32_t p1 = (pixel&0xff000000),
							 p2 = (pixel&0x00ff0000)>>16,
							 p3 = (pixel&0x0000ff00),
							 p4 = (pixel&0x000000ff)<<16;

			*(ptr + x) = p1 | p2 | p3 | p4;
		}
	}

	png_write_image(png_ptr, row_pointers);

	// end write 
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Error during end of write");

		return false;
	}

	png_write_end(png_ptr, NULL);

	// cleanup heap allocation 
	for (int y=0; y<height; y++)
		free(row_pointers[y]);
	free(row_pointers);

	fclose(fp);

	return true;
}

}
