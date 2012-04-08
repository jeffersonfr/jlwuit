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
#ifndef LWUIT_COLOR_H
#define LWUIT_COLOR_H

#include <stdint.h>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Color {
	
	public:
		enum lwuit_color_t {
			AliceBlue,
			AntiqueWhite,
			Aqua,
			Aquamarine,
			Azure,
			Beige,
			Bisque,
			Black,
			BlanchedAlmond,
			Blue,
			BlueViolet,
			Brown,
			BurlyWood,
			CadetBlue,
			Chartreuse,
			Chocolate,
			Coral,
			CornflowerBlue,
			Cornsilk,
			Crimson,
			Cyan,
			DarkBlue,
			DarkCyan,
			DarkGoldenRod,
			DarkGray,
			DarkGrey,
			DarkGreen,
			DarkKhaki,
			DarkMagenta,
			DarkOliveGreen,
			DarkOrange,
			DarkOrchid,
			DarkRed,
			DarkSalmon,
			DarkSeaGreen,
			DarkSlateBlue,
			DarkSlateGray,
			DarkSlateGrey,
			DarkTurquoise,
			DarkViolet,
			DeepPink,
			Deepskyblue,
			DimGray,
			DimGrey,
			DodgerBlue,
			FireBrick,
			FloralWhite,
			ForestGreen,
			Fuchsia,
			Gainsboro,
			GhostWhite,
			Gold,
			GoldenRod,
			Gray,
			Grey,
			Green,
			GreenYellow,
			HoneyDew,
			HotPink,
			IndianRed,
			Indigo,
			Ivory,
			Khaki,
			Lavender,
			kavenderBlush,
			LawnGreen,
			LemonChiffon,
			LightBlue,
			LightCoral,
			LightCyan,
			LightGoldenRodYellow,
			LightGray,
			LightGrey,
			LightGreen,
			LightPink,
			LightSalmon,
			LightSeaGreen,
			LightSkyBlue,
			LightSlateGray,
			LightSlateGrey,
			LightSteelBlue,
			LightYellow,
			Lime,
			LimeGreen,
			Linen,
			Magenta,
			Maroon,
			MediumAquaMarine,
			MediumBlue,
			MediumOrchid,
			MediumPurple,
			MediumSeaGreen,
			MediumSlateBlue,
			MediumSpringGreen,
			MediumTurquoise,
			MediumVioletRed,
			MidnightBlue,
			MintCream,
			MistyRose,
			Moccasin,
			NavajoWhite,
			Navy,
			OldLace,
			Olive,
			OliveDrab,
			Orange,
			OrangeRed,
			Orchid,
			PaleGoldenRod,
			PaleGreen,
			PaleTurquoise,
			PaleVioletRed,
			PapayaWhip,
			PeachPuff,
			Peru,
			Pink,
			PowderBlue,
			Plum,
			Purple,
			Red,
			RosyBrown,
			RoyalBlue,
			SaddlebBown,
			Salmon,
			SandyBrown,
			SeaGreen,
			SeaShell,
			Sienna,
			Silver,
			Skyblue,
			StateBlue,
			StateGray,
			StateGrey,
			Snow,
			SpringGreen,
			SteelBlue,
			Tan,
			Teal,
			Thistle,
			Tomato,
			Turquoise,
			Violet,
			Wheat,
			White,
			WhiteSmoke,
			Yellow,
			Yellowgreen,
			Transparent
		};

	private:
		int _red,
				_green,
				_blue,
				_alpha;

	public:
		/**
		 * \brief
		 *
		 */
		Color(lwuit_color_t color);

		/**
		 * \brief
		 *
		 */
		Color(uint32_t color = 0xff000000);
		
		/**
		 * \brief Creates an ARGB color with the specified red, green, blue, and alpha values in the range (0 - 255).
		 *
		 */
		Color(int r, int g, int b, int a = 0xff);
		
		/**
		 * \brief Creates an ARGB color with the specified red, green, blue, and alpha values in the range (0.0 - 1.0).
		 *
		 */
		Color(double r, double g, double b, double a = 1.0);
		
		/**
		 * \brief
		 *
		 */
		virtual ~Color();

    /**
     * \brief Converts the components of a color, as specified by the HSB model, to an equivalent set of values for the 
		 * default RGB model. 
     * <p>
     * The <code>saturation</code> and <code>brightness</code> components should be doubleing-point values between zero 
		 * and one (numbers in the range 0.0-1.0).  The <code>hue</code> component can be any doubleing-point number.  The floor 
		 * of this number is subtracted from it to create a fraction between 0 and 1.  This fractional number is then multiplied 
		 * by 360 to produce the hue angle in the HSB color model.
     * <p>
     * The integer that is returned by <code>HSBtoRGB</code> encodes the value of a color in bits 0-23 of an integer value 
		 * that is the same format used by the method {@link #getRGB() <code>getRGB</code>}. This integer can be supplied as an 
		 * argument to the <code>Color</code> constructor that takes a single integer argument. 
		 *
     * \param hue the hue component of the color
     * \param saturation the saturation of the color
     * \param brightness the brightness of the color
		 *
     * \return the RGB value of the color with the indicated hue, saturation, and brightness.
     */
    static Color HSBtoRGB(double hue, double saturation, double brightness);

    /**
     * Converts the components of a color, as specified by the default RGB model, to an equivalent set of values for hue, saturation, 
		 * and brightness that are the three components of the HSB model. 
     * <p>
     * If the <code>hsbvals</code> argument is <code>null</code>, then a new array is allocated to return the result. Otherwise, the 
		 * method returns the array <code>hsbvals</code>, with the values put into that array. 
		 *
     * \param r the red component of the color
     * \param g the green component of the color
     * \param b the blue component of the color
     * \param hsbvals the array used to return the three HSB values, or <code>null</code>
		 *
     * \return an array of three elements containing the hue, saturation, and brightness (in that order), of the color with  the indicated 
		 * 		red, green, and blue components.
     */
    static void RGBtoHSB(int red, int green, int blue, double *hsbvals);

		/**
		 * \brief
		 *
		 */
		virtual Color Darker(double factor);
		
		/**
		 * \brief
		 *
		 */
		virtual Color Brighter(double factor);

		/**
		 * \brief
		 *
		 */
		virtual uint8_t GetRed();
		
		/**
		 * \brief
		 *
		 */
		virtual uint8_t GetGreen();
		
		/**
		 * \brief
		 *
		 */
		virtual uint8_t GetBlue();
		
		/**
		 * \brief
		 *
		 */
		virtual uint8_t GetAlpha();
		
		/**
		 * \brief
		 *
		 */
		virtual void SetRed(int red);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetGreen(int green);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetBlue(int blue);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetAlpha(int alpha);
		
		/**
		 * \brief
		 *
		 */
		virtual uint32_t GetARGB();

};

}

#endif 

