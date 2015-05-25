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
#ifndef LWUIT_USEREVENTLISTENER_H
#define LWUIT_USEREVENTLISTENER_H

#include "userevent.h"

#include <vector>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class UserEventListener {

	private:
		/** \brief */
		std::vector<lwuit_key_symbol_t> _keys;

	protected:
		/**
		 * \brief
		 *
		 */
		UserEventListener();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~UserEventListener();

		/** 
		 * \brief Este método adiciona um determinado código a este ouvinte. Ao ser registrado na 
		 * interface <i>IInputManager</i>, este ouvinte recebera eventos referentes aos códigos 
		 * adicionados através deste método.
		 *
		 */
		virtual void Add(lwuit_key_symbol_t key);

		/** 
		 * \brief Atraves deste mÃ©todo pode-se adicionar todas as teclas numéricas de uma só vez. 
		 * KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9.
		 *
		 */
		virtual void AddAllNumerics();

		/** 
		 * \brief Remove as teclas numéricas.
		 *
		 */
		virtual void RemoveAllNumerics();

		/** 
		 * \brief Este método adiciona as teclas de seta KEY_CURSOR_LEFT, KEY_CURSOR_RIGHT, 
		 * KEY_CURSOR_UP, KEY_CURSOR_DOWN.
		 *
		 */
		virtual void AddAllArrows();

		/** 
		 * \brief Remove as teclas direcionais.
		 *
		 */
		virtual void RemoveAllArrows();

		/** 
		 * \brief Adiciona todas as teclas coloridas KEY_RED, KEY_GREEN, KEY_YELLOW, KEY_BLUE.
		 *
		 */
		virtual void AddAllColors();

		/** 
		 * \brief Remove as teclas coloridas.
		 *
		 */
		virtual void RemoveAllColors();

		/** 
		 * \brief Adiciona as teclas multimídia KEY_PLAY, KEY_STOP, KEY_EJECT, KEY_REWIND, 
		 * KEY_RECORD.
		 *
		 */
		virtual void AddAllMultimedia();

		/** 
		 * \brief Remove as teclas multimídia.
		 *
		 */
		virtual void RemoveAllMultimedia();

		/** 
		 * \brief Remove todas as teclas previamente adicionadas.
		 *
		 * \return Este mÃ©todo retorna o nÃºmero de teclas que estavam previamente cadastradas.
		 */
		virtual void RemoveAll();

		/** 
		 * \brief Retorna a lista contendo todos os codigos adicionados para este ouvinte.
		 *
		 * \return
		 */
		virtual std::vector<lwuit_key_symbol_t> GetKeys();

		/**
		 * \brief
		 *
		 */
		virtual bool IsMatch(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyDown(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyUp(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyLongPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMousePress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseRelease(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseLongPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseClick(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseMove(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseOver(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseOut(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseWheel(UserEvent *event);

};

}

#endif
