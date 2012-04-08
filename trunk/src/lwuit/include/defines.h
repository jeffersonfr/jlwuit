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
#ifndef LWUIT_UTILITY_H
#define LWUIT_UTILITY_H

namespace jlwuit {

enum lwuit_pixelformat_t {
	LPF_UNKNOWN,	// 0x00000000	unknown or unspecified format
	LPF_ARGB1555,	// 16 bit ARGB (2 byte, alpha 1@15, red 5@10, green 5@5, blue 5@0)
	LPF_RGB16,		// 16 bit RGB (2 byte, red 5@11, green 6@5, blue 5@0)
	LPF_RGB24,		// 24 bit RGB (3 byte, red 8@16, green 8@8, blue 8@0)
	LPF_RGB32,		// 24 bit RGB (4 byte, nothing@24, red 8@16, green 8@8, blue 8@0)
	LPF_ARGB,			// 32 bit ARGB (4 byte, alpha 8@24, red 8@16, green 8@8, blue 8@0)
	LPF_A8,				// 	8 bit alpha (1 byte, alpha 8@0), e.g. anti-aliased glyphs
	LPF_YUY2,			// 16 bit YUV (4 byte/ 2 pixel, macropixel contains CbYCrY [31:0])
	LPF_RGB332,		// 	8 bit RGB (1 byte, red 3@5, green 3@2, blue 2@0)
	LPF_UYVY,			// 16 bit YUV (4 byte/ 2 pixel, macropixel contains YCbYCr [31:0])
	LPF_I420,			// 12 bit YUV (8 bit Y plane followed by 8 bit quarter size U/V planes)
	LPF_YV12,			// 12 bit YUV (8 bit Y plane followed by 8 bit quarter size V/U planes)
	LPF_LUT8,			// 	8 bit LUT (8 bit color and alpha lookup from palette)
	LPF_ALUT44,		// 	8 bit ALUT (1 byte, alpha 4@4, color lookup 4@0)
	LPF_AiRGB,		// 32 bit ARGB (4 byte, inv. alpha 8@24, red 8@16, green 8@8, blue 8@0)
	LPF_A1,				// 	1 bit alpha (1 byte/ 8 pixel, most significant bit used first)
	LPF_NV12,			// 12 bit YUV (8 bit Y plane followed by one 16 bit quarter size Cb|Cr [7:0|7:0] plane)
	LPF_NV16,			// 16 bit YUV (8 bit Y plane followed by one 16 bit half width Cb|Cr [7:0|7:0] plane)
	LPF_ARGB2554,	// 16 bit ARGB (2 byte, alpha 2@14, red 5@9, green 5@4, blue 4@0)
	LPF_ARGB4444,	// 16 bit ARGB (2 byte, alpha 4@12, red 4@8, green 4@4, blue 4@0)
	LPF_RGBA4444,	// 16 bit RGBA (2 byte, red 4@12, green 4@8, blue 4@4, alpha 4@0)
	LPF_NV21,			// 12 bit YUV (8 bit Y plane followed by one 16 bit quarter size Cr|Cb [7:0|7:0] plane)
	LPF_AYUV,			// 32 bit AYUV (4 byte, alpha 8@24, Y 8@16, Cb 8@8, Cr 8@0)
	LPF_A4,				// 	4 bit alpha (1 byte/ 2 pixel, more significant nibble used first)
	LPF_ARGB1666,	// 	1 bit alpha (3 byte/ alpha 1@18, red 6@12, green 6@6, blue 6@0)
	LPF_ARGB6666,	// 	6 bit alpha (3 byte/ alpha 6@18, red 6@12, green 6@6, blue 6@0)
	LPF_RGB18,		// 	6 bit RGB (3 byte/ red 6@12, green 6@6, blue 6@0)
	LPF_LUT2,			// 	2 bit LUT (1 byte/ 4 pixel, 2 bit color and alpha lookup from palette)
	LPF_RGB444,		// 16 bit RGB (2 byte, nothing @12, red 4@8, green 4@4, blue 4@0)
	LPF_RGB555,		// 16 bit RGB (2 byte, nothing @15, red 5@10, green 5@5, blue 5@0)
	LPF_BGR555,		// 16 bit BGR (2 byte, nothing @15, blue 5@10, green 5@5, red 5@0)
	LPF_RGBA5551,	// 16 bit RGBA (2 byte, red 5@11, green 5@6, blue 5@1, alpha 1@0)
	LPF_AVYU,			// 32 bit AVYU 4:4:4 (4 byte, alpha 8@24, Cr 8@16, Y 8@8, Cb 8@0)
	LPF_VYU,			// 
};

/**
 * \brief
 *
 */
enum lwuit_font_attributes_t {
	LFA_NORMAL,
	LFA_ITALIC,
	LFA_BOLD
};

/**
 * \brief
 *
 */
enum lwuit_horizontal_align_t {
	LHA_LEFT,
	LHA_CENTER,
	LHA_RIGHT,
	LHA_JUSTIFY
};

/**
 * \brief
 *
 */
enum lwuit_vertical_align_t {
	LVA_TOP,
	LVA_CENTER,
	LVA_BOTTOM,
	LVA_JUSTIFY
};

/**
 * \brief
 *
 */
struct lwuit_point_t {
	int x;
	int y;
};

/**
 * \brief
 *
 */
struct lwuit_size_t {
	int width;
	int height;
};

/**
 * \brief
 *
 */
struct lwuit_region_t {
	int x;
	int y;
	int width;
	int height;
};

/**
 * \brief
 *
 */
struct lwuit_margin_t {
	int left;
	int right;
	int top;
	int bottom;
};

}

#endif
