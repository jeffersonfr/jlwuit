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
#include "videoformatcontrol.h"

namespace jlwuit {

VideoFormatControl::VideoFormatControl():
	Control("video.format")
{
}
		
VideoFormatControl::~VideoFormatControl()
{
}

void VideoFormatControl::SetAspectRatio(lwuit_aspect_ratio_t t)
{
}

void VideoFormatControl::SetContentMode(lwuit_video_mode_t t)
{
}

void VideoFormatControl::SetVideoFormatHD(lwuit_hd_video_format_t vf)
{
}

void VideoFormatControl::SetVideoFormatSD(lwuit_sd_video_format_t vf)
{
}

void VideoFormatControl::SetContrast(int value)
{
}

void VideoFormatControl::SetSaturation(int value)
{
}

void VideoFormatControl::SetHUE(int value)
{
}

void VideoFormatControl::SetBrightness(int value)
{
}

void VideoFormatControl::SetSharpness(int value)
{
}

lwuit_aspect_ratio_t VideoFormatControl::GetAspectRatio()
{
	return LAR_16x9;
}

lwuit_video_mode_t VideoFormatControl::GetContentMode()
{
	return LVM_FULL;
}

lwuit_hd_video_format_t VideoFormatControl::GetVideoFormatHD()
{
	return LHVF_1080i;
}

lwuit_sd_video_format_t VideoFormatControl::GetVideoFormatSD()
{
	return LSVF_PAL_M;
}

int VideoFormatControl::GetContrast()
{
	return 0;
}

int VideoFormatControl::GetSaturation()
{
	return 0;
}

int VideoFormatControl::GetHUE()
{
	return 0;
}

int VideoFormatControl::GetBrightness()
{
	return 0;
}

int VideoFormatControl::GetSharpness()
{
	return 0;
}

}
