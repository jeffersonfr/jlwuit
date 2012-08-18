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
#ifndef LWUIT_LHEIMAGEFILTER_H
#define LWUIT_LHEIMAGEFILTER_H

#include "filter.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class LHEImageFilter : public Filter {

	private:
		/** \brief */
		int _factor;
		/** \brief */
		int _domain;

	public:
		/**
		 * \brief
		 *
		 */
		LHEImageFilter(int factor = 1);

		/**
		 * \brief
		 *
		 */
		virtual ~LHEImageFilter();

		/**
		 * \brief
		 *
		 */
		virtual void SetFactor(int factor);

		/**
		 * \brief
		 *
		 */
		virtual int GetFactor();

		/**
		 * \brief
		 *
		 */
		virtual void SetDomain(int domain);

		/**
		 * \brief
		 *
		 */
		virtual int GetDomain();

		/**
		 * \brief
		 *
		 */
		virtual bool Transform(uint8_t *data, int width, int height);

};

}

#endif