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
#include "color.h"
#include "exception.h"

#include <stdlib.h>
#include <math.h>

#define TRUNC_COLOR(r, g, b, a)			\
	r = (r < 0)?0:(r > 0xff)?0xff:r;	\
	g = (g < 0)?0:(g > 0xff)?0xff:g;	\
	b = (b < 0)?0:(b > 0xff)?0xff:b;	\
	a = (a < 0)?0:(a > 0xff)?0xff:a;	\

namespace jlwuit {

Color::Color(lwuit_color_t color)
{
	uint32_t value = 0x00000000;

	if (color == AliceBlue) {
		value = 0xfff0f8ff;
	} else if (color == AntiqueWhite) {
		value = 0xfffaebd7;
	} else if (color == Aqua) {
		value = 0xff00ffff;
	} else if (color == Aquamarine) {
		value = 0xff7fffd4;
	} else if (color == Azure) {
		value = 0xfff0ffff;
	} else if (color == Beige) {
		value = 0xfff5f5dc;
	} else if (color == Bisque) {
		value = 0xffffe4c4;
	} else if (color == Black) {
		value = 0xff000000;
	} else if (color == BlanchedAlmond) {
		value = 0xffffebcd;
	} else if (color == Blue) {
		value = 0xff0000ff;
	} else if (color == BlueViolet) {
		value = 0xff8a2be2;
	} else if (color == Brown) {
		value = 0xffa52a2a;
	} else if (color == BurlyWood) {
		value = 0xffdeb887;
	} else if (color == CadetBlue) {
		value = 0xff5f9ea0;
	} else if (color == Chartreuse) {
		value = 0xff7fff00;
	} else if (color == Chocolate) { 
		value = 0xffd2691e;
	} else if (color == Coral) {
		value = 0xffff7f50;
	} else if (color == CornflowerBlue) {
		value = 0xff6495ed;
	} else if (color == Cornsilk) {
		value = 0xfffff8dc;
	} else if (color == Crimson) {
		value = 0xffdc143c;
	} else if (color == Cyan) {
		value = 0xff00ffff;
	} else if (color == DarkBlue) {
		value = 0xff00008b;
	} else if (color == DarkCyan) {
		value = 0xff008b8b;
	} else if (color == DarkGoldenRod) {
		value = 0xffb8860b;
	} else if (color == DarkGray) {
		value = 0xffa9a9a9;
	} else if (color == DarkGrey) {
		value = 0xffa9a9a9;
	} else if (color == DarkGreen) {
		value = 0xff006400;
	} else if (color == DarkKhaki) {
		value = 0xffbdb76b;
	} else if (color == DarkMagenta) {
		value = 0xff8b008b;
	} else if (color == DarkOliveGreen) { 
		value = 0xff556b2f;
	} else if (color == DarkOrange) {
		value = 0xffff8c00;
	} else if (color == DarkOrchid) {
		value = 0xff9932cc;
	} else if (color == DarkRed) {
		value = 0xff8b0000;
	} else if (color == DarkSalmon) {
		value = 0xffe9967a;
	} else if (color == DarkSeaGreen) {
		value = 0xff8fbc8f;
	} else if (color == DarkSlateBlue) {
		value = 0xff483d8b;
	} else if (color == DarkSlateGray) {
		value = 0xff2f4f4f;
	} else if (color == DarkSlateGrey) {
		value = 0xff3f4f4f;
	} else if (color == DarkTurquoise) {
		value = 0xff00ced1;
	} else if (color == DarkViolet) {
		value = 0xff9400d3;
	} else if (color == DeepPink) {
		value = 0xffff1493;
	} else if (color == Deepskyblue) {
		value = 0xff00bf00;
	} else if (color == DimGray) {
		value = 0xff696969;
	} else if (color == DimGrey) {
		value = 0xff696969;
	} else if (color == DodgerBlue) {
		value = 0xff1e90ff;
	} else if (color == FireBrick) {
		value = 0xffb22222;
	} else if (color == FloralWhite) {
		value = 0xfffffaf0;
	} else if (color == ForestGreen) { 
		value = 0xff228b22;
	} else if (color == Fuchsia) {
		value = 0xffff00ff;
	} else if (color == Gainsboro) {
		value = 0xffdcdcdc;
	} else if (color == GhostWhite) {
		value = 0xfff8f8ff;
	} else if (color == Gold) {
		value = 0xffffd700;
	} else if (color == GoldenRod) {
		value = 0xffdaa520;
	} else if (color == Gray) {
		value = 0xff808080;
	} else if (color == Grey) {
		value = 0xff808080;
	} else if (color == Green) {
		value = 0xff008000;
	} else if (color == GreenYellow) {
		value = 0xffadff2f;
	} else if (color == HoneyDew) {
		value = 0xfff0fff0;
	} else if (color == HotPink) {
		value = 0xffff69b4;
	} else if (color == IndianRed) {
		value = 0xffcd5c5c;
	} else if (color == Indigo) {
		value = 0xff4b0082;
	} else if (color == Ivory) {
		value = 0xfffffff0;
	} else if (color == Khaki) {
		value = 0xfff0e68c;
	} else if (color == Lavender) {
		value = 0xffe6e6fa;
	} else if (color == kavenderBlush) { 
		value = 0xfffff0f5;
	} else if (color == LawnGreen) {
		value = 0xff7cfc00;
	} else if (color == LemonChiffon) {
		value = 0xfffffacd;
	} else if (color == LightBlue) {
		value = 0xffadd8e6;
	} else if (color == LightCoral) {
		value = 0xfff08080;
	} else if (color == LightCyan) {
		value = 0xffe0ffff;
	} else if (color == LightGoldenRodYellow) {
		value = 0xfffafad2;
	} else if (color == LightGray) {
		value = 0xffd3d3d3;
	} else if (color == LightGrey) {
		value = 0xffd3d3d3;
	} else if (color == LightGreen) {
		value = 0xff90ee90;
	} else if (color == LightPink) {
		value = 0xffffb6c1;
	} else if (color == LightSalmon) {
		value = 0xffffa07a;
	} else if (color == LightSeaGreen) {
		value = 0xff20b2aa;
	} else if (color == LightSkyBlue) {
		value = 0xff87cefa;
	} else if (color == LightSlateGray) {
		value = 0xff778899;
	} else if (color == LightSlateGrey) {
		value = 0xff778899;
	} else if (color == LightSteelBlue) {
		value = 0xffb0c4de;
	} else if (color == LightYellow) {
		value = 0xffffffe0;
	} else if (color == Lime) {
		value = 0xff00ff00;
	} else if (color == LimeGreen) { 
		value = 0xff32cd32;
	} else if (color == Linen) {
		value = 0xfffaf0e6;
	} else if (color == Magenta) {
		value = 0xffff00ff;
	} else if (color == Maroon) {
		value = 0xff800000;
	} else if (color == MediumAquaMarine) {
		value = 0xff6ccdaa;
	} else if (color == MediumBlue) {
		value = 0xff0000cd;
	} else if (color == MediumOrchid) {
		value = 0xffba55d3;
	} else if (color == MediumPurple) {
		value = 0xff9370d6;
	} else if (color == MediumSeaGreen) {
		value = 0xff3cb371;
	} else if (color == MediumSlateBlue) {
		value = 0xff7b68ee;
	} else if (color == MediumSpringGreen) {
		value = 0xff00fa9a;
	} else if (color == MediumTurquoise) {
		value = 0xff48d1cc;
	} else if (color == MediumVioletRed) {
		value = 0xffc71585;
	} else if (color == MidnightBlue) {
		value = 0xff191970;
	} else if (color == MintCream) {
		value = 0xfff5fffa;
	} else if (color == MistyRose) {
		value = 0xffffe4e1;
	} else if (color == Moccasin) {
		value = 0xffffe4b5;
	} else if (color == NavajoWhite) {
		value = 0xffffdead;
	} else if (color == Navy) {
		value = 0xff000080;
	} else if (color == OldLace) {
		value = 0xfffdf5e6;
	} else if (color == Olive) {
		value = 0xff808000;
	} else if (color == OliveDrab) {
		value = 0xff6b8e23;
	} else if (color == Orange) {
		value = 0xffffa500;
	} else if (color == OrangeRed) {
		value = 0xffff4500;
	} else if (color == Orchid) {
		value = 0xffda70d6;
	} else if (color == PaleGoldenRod) { 
		value = 0xffeee8aa;
	} else if (color == PaleGreen) {
		value = 0xff98fb98;
	} else if (color == PaleTurquoise) {
		value = 0xffafeeee;
	} else if (color == PaleVioletRed) {
		value = 0xffd87093;
	} else if (color == PapayaWhip) {
		value = 0xffffefd5;
	} else if (color == PeachPuff) {
		value = 0xffffdab9;
	} else if (color == Peru) {
		value = 0xffcd853f;
	} else if (color == Pink) {
		value = 0xffffc0cb;
	} else if (color == PowderBlue) {
		value = 0xffb0e0e6;
	} else if (color == Plum) {
		value = 0xffdda0dd;
	} else if (color == Purple) { 
		value = 0xff800080;
	} else if (color == Red) {
		value = 0xffff0000;
	} else if (color == RosyBrown) {
		value = 0xffbc8f8f;
	} else if (color == RoyalBlue) {
		value = 0xff4169e1;
	} else if (color == SaddlebBown) {
		value = 0xff8b4513;
	} else if (color == Salmon) {
		value = 0xfffa8072;
	} else if (color == SandyBrown) {
		value = 0xfff4a460;
	} else if (color == SeaGreen) {
		value = 0xff2e8b57;
	} else if (color == SeaShell) {
		value = 0xfffff5ee;
	} else if (color == Sienna) {
		value = 0xffa0522d;
	} else if (color == Silver) {
		value = 0xffc0c0c0;
	} else if (color == Skyblue) {
		value = 0xff87ceeb;
	} else if (color == StateBlue) {
		value = 0xff6a5acd;
	} else if (color == StateGray) {
		value = 0xff708090;
	} else if (color == StateGrey) {
		value = 0xff708090;
	} else if (color == Snow) {
		value = 0xfffffafa;
	} else if (color == SpringGreen) {
		value = 0xff00ff7f;
	} else if (color == SteelBlue) {
		value = 0xff4682b4;
	} else if (color == Tan) {
		value = 0xffd2b48c;
	} else if (color == Teal) {
		value = 0xff008080;
	} else if (color == Thistle) {
		value = 0xffd8bfd8;
	} else if (color == Tomato) {
		value = 0xffff6347;
	} else if (color == Turquoise) {
		value = 0xff40e0d0;
	} else if (color == Violet) {
		value = 0xffee82ee;
	} else if (color == Wheat) {
		value = 0xfff5deb3;
	} else if (color == White) {
		value = 0xffffffff;
	} else if (color == WhiteSmoke) { 
		value = 0xfff5f5f5;
	} else if (color == Yellow) {
		value = 0xffffff00;
	} else if (color == Yellowgreen) {
		value = 0xff9acd32;
	} else if (color == Transparent) { 
		value = 0x00000000;
	}

	_red = (value >> 0x10) & 0xff;
	_green = (value >> 0x08) & 0xff;
	_blue = (value >> 0x00) & 0xff;
	_alpha = (value >> 0x18) & 0xff;

	TRUNC_COLOR(_red, _green, _blue, _alpha);
}

Color::Color(uint32_t color)
{
	_red = (color >> 0x10) & 0xff;
	_green = (color >> 0x08) & 0xff;
	_blue = (color >> 0x00) & 0xff;
	_alpha = (color >> 0x18) & 0xff;

	TRUNC_COLOR(_red, _green, _blue, _alpha);
}

Color::Color(int red, int green, int blue, int alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;

	TRUNC_COLOR(_red, _green, _blue, _alpha);
}

Color::Color(double red, double green, double blue, double alpha)
{
	_red = (int)(red * 0xff);
	_green = (int)(green * 0xff);
	_blue = (int)(blue * 0xff);
	_alpha = (int)(alpha * 0xff);
	
	TRUNC_COLOR(_red, _green, _blue, _alpha);
}

Color::~Color()
{
}

Color Color::HSBtoRGB(double hue, double saturation, double brightness) 
{
	int red = 0, 
			green = 0, 
			blue = 0;

	if (saturation == 0) {
		red = green = blue = (int) (brightness * 255.0f + 0.5f);
	} else {
		double h = (hue - (double)floor(hue)) * 6.0f;
		double f = h - (double)floor(h);
		double p = brightness * (1.0f - saturation);
		double q = brightness * (1.0f - saturation * f);
		double t = brightness * (1.0f - (saturation * (1.0f - f)));

		switch ((int)h) {
			case 0:
				red = (int) (brightness * 255.0f + 0.5f);
				green = (int) (t * 255.0f + 0.5f);
				blue = (int) (p * 255.0f + 0.5f);
				break;
			case 1:
				red = (int) (q * 255.0f + 0.5f);
				green = (int) (brightness * 255.0f + 0.5f);
				blue = (int) (p * 255.0f + 0.5f);
				break;
			case 2:
				red = (int) (p * 255.0f + 0.5f);
				green = (int) (brightness * 255.0f + 0.5f);
				blue = (int) (t * 255.0f + 0.5f);
				break;
			case 3:
				red = (int) (p * 255.0f + 0.5f);
				green = (int) (q * 255.0f + 0.5f);
				blue = (int) (brightness * 255.0f + 0.5f);
				break;
			case 4:
				red = (int) (t * 255.0f + 0.5f);
				green = (int) (p * 255.0f + 0.5f);
				blue = (int) (brightness * 255.0f + 0.5f);
				break;
			case 5:
				red = (int) (brightness * 255.0f + 0.5f);
				green = (int) (p * 255.0f + 0.5f);
				blue = (int) (q * 255.0f + 0.5f);
				break;
		}
	}
	
	return Color(red, green, blue, 0xff);
}

void Color::RGBtoHSB(int red, int green, int blue, double *hsbvals) 
{
	if (hsbvals == NULL) {
		throw Exception("HSB parameter cannot be NULL");
	}

	double hue, 
				 saturation, 
				 brightness;

	int cmax = (red > green) ? red : green;
	if (blue > cmax) {
		cmax = blue;
	}
	
	int cmin = (red < green) ? red : green;
	if (blue < cmin) {
		cmin = blue;
	}

	brightness = ((double) cmax) / 255.0f;
	if (cmax != 0) {
		saturation = ((double) (cmax - cmin)) / ((double) cmax);
	} else {
		saturation = 0;
	}
	
	if (saturation == 0) {
		hue = 0;
	} else {
		double redc = ((double) (cmax - red)) / ((double) (cmax - cmin));
		double greenc = ((double) (cmax - green)) / ((double) (cmax - cmin));
		double bluec = ((double) (cmax - blue)) / ((double) (cmax - cmin));

		if (red == cmax) {
			hue = bluec - greenc;
		} else if (green == cmax) {
			hue = 2.0f + redc - bluec;
		} else {
			hue = 4.0f + greenc - redc;
		}

		hue = hue / 6.0f;
		if (hue < 0) {
			hue = hue + 1.0f;
		}
	}

	hsbvals[0] = hue;
	hsbvals[1] = saturation;
	hsbvals[2] = brightness;
}

Color Color::Darker(double factor)
{
	if (factor < 0.0 || factor > 1.0) {
		factor = 0.0;
	}

	factor = 1.0 - factor;

	return Color((int)(_red*factor), (int)(_green*factor), (int)(_blue*factor), _alpha);
}

Color Color::Brighter(double factor)
{
	if (factor < 0.0 || factor > 1.0) {
		factor = 0.0;
	}

	factor = 1.0 + factor;

	return Color((int)(_red*factor), (int)(_green*factor), (int)(_blue*factor), _alpha);
}

uint8_t Color::GetRed()
{
	return _red;
}

uint8_t Color::GetGreen()
{
	return _green;
}

uint8_t Color::GetBlue()
{
	return _blue;
}

uint8_t Color::GetAlpha()
{
	return _alpha;
}

void Color::SetRed(int red)
{
	_red = (red < 0)?0:(red > 0xff)?0xff:red;
}

void Color::SetGreen(int green)
{
	_green = (green < 0)?0:(green > 0xff)?0xff:green;
}

void Color::SetBlue(int blue)
{
	_blue = (blue < 0)?0:(blue > 0xff)?0xff:blue;
}

void Color::SetAlpha(int alpha)
{
	_alpha = (alpha < 0)?0:(alpha > 0xff)?0xff:alpha;
}

uint32_t Color::GetARGB()
{
	return (uint32_t)(_alpha << 0x18 | _red << 0x10 | _green << 0x08 | _blue << 0x00);
}

}

