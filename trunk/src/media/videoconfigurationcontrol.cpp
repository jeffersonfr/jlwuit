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
#include "videoconfigurationcontrol.h"

namespace jlwuit {

VideoConfigurationControl::VideoConfigurationControl():
	Control(LMC_VIDEO_CONFIGURATION)
{
}
		
VideoConfigurationControl::~VideoConfigurationControl()
{
}

void VideoConfigurationControl::SetAspectRatio(lwuit_aspect_ratio_t t)
{
}

void VideoConfigurationControl::SetContentMode(lwuit_video_mode_t t)
{
}

void VideoConfigurationControl::SetVideoFormatHD(lwuit_hd_video_format_t vf)
{
}

void VideoConfigurationControl::SetVideoFormatSD(lwuit_sd_video_format_t vf)
{
}

void VideoConfigurationControl::SetContrast(int value)
{
}

void VideoConfigurationControl::SetSaturation(int value)
{
}

void VideoConfigurationControl::SetHUE(int value)
{
}

void VideoConfigurationControl::SetBrightness(int value)
{
}

void VideoConfigurationControl::SetSharpness(int value)
{
}

lwuit_aspect_ratio_t VideoConfigurationControl::GetAspectRatio()
{
	return LAR_16x9;
}

lwuit_video_mode_t VideoConfigurationControl::GetContentMode()
{
	return LVM_FULL;
}

lwuit_hd_video_format_t VideoConfigurationControl::GetVideoFormatHD()
{
	return LHVF_1080i;
}

lwuit_sd_video_format_t VideoConfigurationControl::GetVideoFormatSD()
{
	return LSVF_PAL_M;
}

int VideoConfigurationControl::GetContrast()
{
	return 0;
}

int VideoConfigurationControl::GetSaturation()
{
	return 0;
}

int VideoConfigurationControl::GetHUE()
{
	return 0;
}

int VideoConfigurationControl::GetBrightness()
{
	return 0;
}

int VideoConfigurationControl::GetSharpness()
{
	return 0;
}

}
