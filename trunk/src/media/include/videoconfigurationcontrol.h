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
#ifndef LWUIT_VIDEOCONFIGURATIONCONTROL_H
#define LWUIT_VIDEOCONFIGURATIONCONTROL_H

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

class VideoConfigurationControl : public Control {

	public:
		/**
		 * \brief
		 *
		 */
		VideoConfigurationControl();

		/**
		 * \brief Destrutor virtual.
		 *
		 */
		virtual ~VideoConfigurationControl();

		/**
		 * \brief Define a razão de aspecto a ser utilizada
		 *
		 * \param ar Razão de aspecto a ser utilizada
		 */
		virtual void SetAspectRatio(lwuit_aspect_ratio_t t);

		/**
		 * \brief Define o tipo de adaptação de tela a ser utilizada. O resultado final da adaptação
		 * dependerá do formato da mídia reproduzida e da razão de aspecto da tela que exibe o vídeo
		 *
		 * \param cm Tipo da adaptação de tela a ser empregada
		 */
		virtual void SetContentMode(lwuit_video_mode_t t);

		/**
		 * \brief Define o formato de vídeo a ser utilizado na saída HD
		 *
		 * \param vf Formato de vídeo HD a ser utilizado 
		 */
		virtual void SetVideoFormatHD(lwuit_hd_video_format_t vf);

		/**
		 * \brief Define o formato de vídeo a ser utilizado na saída SD
		 *
		 * \param vf Formato de vídeo SD
		 */
		virtual void SetVideoFormatSD(lwuit_sd_video_format_t vf);

		/**
		 * \brief Define o valor da configuração de constraste. A faixa de
		 * valores válidos é [0-100]
		 *
		 * \param value Valor da configuração de constraste
		 */
		virtual void SetContrast(int value);

		/**
		 * \brief Define o valor da configuração de saturação. A faixa de
		 * valores válidos é [0-100]
		 *
		 * \param value Valor da configuração de saturação
		 */
		virtual void SetSaturation(int value);

		/**
		 * \brief Define o valor da configuração de matiz. A faixa de
		 * valores válidos é [0-100]
		 *
		 * \param value Valor da configuração de matiz
		 */
		virtual void SetHUE(int value);

		/**
		 * \brief Define o valor da configuração de brilho. A faixa de
		 * valores válidos é [0-100]
		 *
		 * \param value Valor da configuração de brilho
		 */
		virtual void SetBrightness(int value);

		/**
		 * \brief Define o valor da configuração de nitidez. A faixa de
		 * valores válidos é [0-100]
		 *
		 * \param value Valor da configuração de nitidez
		 */
		virtual void SetSharpness(int value);

		/**
		 * \brief Informa a razão de aspecto definida
		 *
		 * \return Razão de aspecto
		 */
		virtual lwuit_aspect_ratio_t GetAspectRatio();

		/**
		 * \brief Informa a adaptação de tela definida
		 *
		 * \return Adaptação de tela
		 */
		virtual lwuit_video_mode_t GetContentMode();

		/**
		 * \brief Informa o formato de vídeo definido para a saída HD
		 *
		 * \return Formato de vídeo HD
		 */
		virtual lwuit_hd_video_format_t GetVideoFormatHD();

		/**
		 * \brief Informar o formato de vídeo definido para a saída SD
		 *
		 * \return Formato de vídeo SD
		 */
		virtual lwuit_sd_video_format_t GetVideoFormatSD();

		/**
		 * \brief Informa o valor da configuração de constraste
		 *
		 * \return Valor da configuração constraste
		 */
		virtual int GetContrast();

		/**
		 * \brief Informa o valor da configuração de saturação
		 *
		 * \return Valor da configuração saturação
		 */
		virtual int GetSaturation();

		/**
		 * \brief Informa o valor da configuração de matiz
		 *
		 * \return Valor da configuração matiz
		 */
		virtual int GetHUE();

		/**
		 * \brief Informa o valor da configuração de brilho
		 *
		 * \return Valor da configuração brilho
		 */
		virtual int GetBrightness();

		/**
		 * \brief Informa o valor da configuração de nitidez
		 *
		 * \return Valor da configuração de nitidez
		 */
		virtual int GetSharpness();

};

}

#endif 
