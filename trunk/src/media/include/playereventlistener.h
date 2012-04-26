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
#ifndef LWUIT_PLAYEREVENTLISTENER_H
#define LWUIT_PLAYEREVENTLISTENER_H

#include "playerevent.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class PlayerEventListener {

	private:
		/**
		 * \brief
		 *
		 */
		PlayerEventListener();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~PlayerEventListener();

		/**
		 * \brief Este método recebe eventos MediaPlayerEvent do tipo STARTED_EVENT. Este tipo 
		 * de evento indica o início da reprodução de mídia.
		 *
		 * O objeto <i>event</i> recebido no parâmetro não deve ser removido da memória
		 * dentro deste método. É papel da fonte disparadora de eventos remover os eventos 
		 * criados. Além disso, o ouvinte não deve guardar referência para o evento fora do 
		 * contexto de execução de <i>MediaStarted</i> pois o disparador de evento é livre 
		 * para remover o evento da memória a qualquer momento após o retorno do método <i>
		 * MediaStarted</i>.
		 *
		 * \param event O objeto <i>MediaPlayerEvent</i> carregando informações a respeito do evento
		 */
		virtual void MediaStarted(PlayerEvent *event);

		/**
		 * \brief Este método recebe eventos MediaPlayerEvent do tipo RESUMED_EVENT. Este tipo 
		 * de evento indica o início da reprodução de mídia.
		 *
		 * O objeto <i>event</i> recebido no parâmetro não deve ser removido da memória
		 * dentro deste método. É papel da fonte disparadora de eventos remover os eventos 
		 * criados. Além disso, o ouvinte não deve guardar referência para o evento fora do 
		 * contexto de execução de <i>MediaResumed</i> pois o disparador de evento é livre 
		 * para remover o evento da memória a qualquer momento após o retorno do método <i>
		 * MediaResumed</i>.
		 *
		 * \param event O objeto <i>MediaPlayerEvent</i> carregando informações a respeito do evento
		 */
		virtual void MediaResumed(PlayerEvent *event);

		/**
		 * \brief Este método recebe eventos MediaPlayerEvent do tipo PAUSED_EVENT. Este tipo 
		 * de evento indica o início da reprodução de mídia.
		 *
		 * O objeto <i>event</i> recebido no parâmetro não deve ser removido da memória
		 * dentro deste método. É papel da fonte disparadora de eventos remover os eventos 
		 * criados. Além disso, o ouvinte não deve guardar referência para o evento fora do 
		 * contexto de execução de <i>MediaPaused</i> pois o disparador de evento é livre 
		 * para remover o evento da memória a qualquer momento após o retorno do método <i>
		 * MediaPaused</i>.
		 *
		 * \param event O objeto <i>MediaPlayerEvent</i> carregando informações a respeito do evento
		 */
		virtual void MediaPaused(PlayerEvent *event);

		/**
		 * \brief Este método recebe eventos MediaPlayerEvent do tipo STOPPED_EVENT. Este tipo 
		 * de evento indica o início da reprodução de mídia.
		 *
		 * O objeto <i>event</i> recebido no parâmetro não deve ser removido da memória
		 * dentro deste método. É papel da fonte disparadora de eventos remover os eventos 
		 * criados. Além disso, o ouvinte não deve guardar referência para o evento fora do 
		 * contexto de execução de <i>MediaStopped</i> pois o disparador de evento é livre 
		 * para remover o evento da memória a qualquer momento após o retorno do método <i>
		 * MediaStopped</i>.
		 *
		 * \param event O objeto <i>MediaPlayerEvent</i> carregando informações a respeito do evento
		 */
		virtual void MediaStopped(PlayerEvent *event);

		/**
		 * \brief Este método recebe eventos MediaPlayerEvent do tipo FINISHED_EVENT. Este tipo 
		 * de evento indica o início da reprodução de mídia.
		 *
		 * O objeto <i>event</i> recebido no parâmetro não deve ser removido da memória
		 * dentro deste método. É papel da fonte disparadora de eventos remover os eventos 
		 * criados. Além disso, o ouvinte não deve guardar referência para o evento fora do 
		 * contexto de execução de <i>MediaFinished</i> pois o disparador de evento é livre 
		 * para remover o evento da memória a qualquer momento após o retorno do método <i>
		 * MediaFinished</i>.
		 *
		 * \param event O objeto <i>MediaPlayerEvent</i> carregando informações a respeito do evento
		 */
		virtual void MediaFinished(PlayerEvent *event);

};

}

#endif
