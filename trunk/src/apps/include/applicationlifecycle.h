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
#ifndef LWUIT_APPLICATIONLIFECYCLE_H
#define LWUIT_APPLICATIONLIFECYCLE_H

#include <stdint.h>

class ApplicationLifeCycle {

	protected:
		/**
		 * \brief
		 *
		 */
		ApplicationLifeCycle()
		{
		}

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~ApplicationLifeCycle()
		{
		}

		/*
		 * \brief Called to initialize the application. To achieve better perfomance, applications 
		 * should perform heavy initialization procedures here instead of in the constructor method. 
		 * The application manager can instantiate an application to perform other actions instead 
		 * of place it in fully execution.
		 *
		   After this method call, the application is in the <i>initialized</i> state.
		 */
		virtual void Start()
		{
		}
		
		/*
		 * \brief Pauses the application. The application in a paused state must stop providing
	   *  services and should release all shared resources.
		 *
		 * This method is called only when the application is in the initialized state.
		 */
		virtual void Pause()
		{
		}
		
		/*
		 * \brief Restart the execution of a paused application. The application will pass from
		 * the paused state to the initialized state.
		 *
		 */
		virtual void Resume()
		{
		}
		
		/*
		 * \brief Ends the application execution. Compliant implementations should release resources,
		 * save any data in persistent storage and delete itself from memory.
		 *
		 * To notify the end of the application's execution, a compliant implementation must call 
		 * method notifyDestroy of ResidentContext within this method call.
		 *        
		 */
		virtual void Destroy()
		{
		}

};

#define APPLICATIONLIFECYCLE_INTERFACE ApplicationLifeCycle

/**
 * \brief Macro para a definiçao das funcoes para carregar um modulo.
 * 
 * \param module Define o nome das funcoes para carregar um modulo.
 */
#define APPLICATION_MODULE_CLASS(module, cast) \
	extern "C" APPLICATIONLIFECYCLE_INTERFACE * CreateModule() { \
		APPLICATIONLIFECYCLE_INTERFACE *p = (cast *)new module(); \
		return p; \
	} \
	extern "C" void DestroyModule(APPLICATIONLIFECYCLE_INTERFACE *p) { \
		delete p; \
	} \

typedef APPLICATIONLIFECYCLE_INTERFACE * (* CreateApplicationModuleFunction)();

#endif

