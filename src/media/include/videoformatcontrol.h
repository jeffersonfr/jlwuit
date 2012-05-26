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
#ifndef LWUIT_VIDEOFORMATCONTROL_H
#define LWUIT_VIDEOFORMATCONTROL_H

#include "control.h"

namespace jlwuit {

/** 
 * \brief 
 *
 */
enum lwuit_aspect_ratio_t {
	LAR_1x1,
	LAR_2x3,
	LAR_4x3,
	LAR_16x9
};

/** 
 * \brief Tipos de adaptações de tela suportados:
 *
 * content_mode_zoom: Indica que o vídeo deve ser cortado (clipping) para adaptar a tela
 * content_mode_box: Indica que barras devem ser utilizadas para adaptação (letterbox ou pillar box) 
 * content_mode_panscan: Indica que o método PanScan deve ser utilizado (se as informações estiverem presentes no fluxo)
 * content_mode_full: Indica que o vídeo deve ser esticado (stretching) de forma linear para se adaptar à tela
 * content_mode_full: Indica que o vídeo deve ser esticado, porém de forma não-linear (as bordas podem ser mais esticadas que a parte central)
 * */
enum lwuit_video_mode_t {
	LVM_ZOOM,
	LVM_BOX,
	LVM_PANSCAN,
	LVM_FULL,
	LVM_FULL_NONLINEAR
};

/** 
 * \brief 
 *
 */
enum lwuit_sd_video_format_t {
	LSVF_NTSC,
	LSVF_NTSC_JAPAN,
	LSVF_PAL_M,
	LSVF_PAL_N,
	LSVF_PAL_NC,
	LSVF_PAL_B,
	LSVF_PAL_B1,
	LSVF_PAL_D,
	LSVF_PAL_D1,
	LSVF_PAL_G,
	LSVF_PAL_H,
	LSVF_PAL_K,
	LSVF_PAL_I,
	LSVF_SECAM
};

/** 
 * \brief
 *
 */
enum lwuit_hd_video_format_t {
	LHVF_480p,
	LHVF_576p,
	LHVF_720p,
	LHVF_1080i,
	LHVF_1080p
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class VideoFormatControl : public Control {

	public:
		/**
		 * \brief
		 *
		 */
		VideoFormatControl();

		/**
		 * \brief Destructor.
		 *
		 */
		virtual ~VideoFormatControl();

		/**
		 * \brief Define media's aspect ratio.
		 *
		 * \param t
		 */
		virtual void SetAspectRatio(lwuit_aspect_ratio_t t);

		/**
		 * \brief Define the video mode. The final result will depend from content mode and aspect ratio.
		 *
		 * \param t
		 */
		virtual void SetContentMode(lwuit_video_mode_t t);

		/**
		 * \brief Define the high definition format of media.
		 *
		 * \param t
		 */
		virtual void SetVideoFormatHD(lwuit_hd_video_format_t vf);

		/**
		 * \brief Define the standard definition format of media.
		 *
		 * \param t
		 */
		virtual void SetVideoFormatSD(lwuit_sd_video_format_t vf);

		/**
		 * \brief Define a value to contrast. The value must is between [0..100].
		 *
		 * \param value 
		 */
		virtual void SetContrast(int value);

		/**
		 * \brief Define a value to saturation. The value must is between [0..100].
		 *
		 * \param value 
		 */
		virtual void SetSaturation(int value);

		/**
		 * \brief Define a value to HUE. The value must is between [0..100].
		 *
		 * \param value 
		 */
		virtual void SetHUE(int value);

		/**
		 * \brief Define a value to brightness. The value must is between [0..100].
		 *
		 * \param value 
		 */
		virtual void SetBrightness(int value);

		/**
		 * \brief Define a value to sharpness. The value must is between [0..100].
		 *
		 * \param value
		 */
		virtual void SetSharpness(int value);

		/**
		 * \brief Returns the aspect ratio.
		 *
		 * \return 
		 */
		virtual lwuit_aspect_ratio_t GetAspectRatio();

		/**
		 * \brief Returns the content mode.
		 *
		 * \return 
		 */
		virtual lwuit_video_mode_t GetContentMode();

		/**
		 * \brief Returns high definition format.
		 *
		 * \return 
		 */
		virtual lwuit_hd_video_format_t GetVideoFormatHD();

		/**
		 * \brief Returns standard definition format.
		 *
		 * \return 
		 */
		virtual lwuit_sd_video_format_t GetVideoFormatSD();

		/**
		 * \brief Returns the contrast.
		 *
		 * \return 
		 */
		virtual int GetContrast();

		/**
		 * \brief Returns de saturation.
		 *
		 * \return 
		 */
		virtual int GetSaturation();

		/**
		 * \brief Returns the HUE.
		 *
		 * \return 
		 */
		virtual int GetHUE();

		/**
		 * \brief Returns the brightness.
		 *
		 * \return 
		 */
		virtual int GetBrightness();

		/**
		 * \brief Returns the sharpness.
		 *
		 * \return 
		 */
		virtual int GetSharpness();

};

}

#endif 
