/* UOL Messenger
 * Copyright (c) 2005 Universo Online S/A
 *
 * Direitos Autorais Reservados
 * All rights reserved
 *
 * Este programa � software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * sob os termos da Licen�a P�blica Geral GNU conforme publicada pela Free
 * Software Foundation; tanto a vers�o 2 da Licen�a, como (a seu crit�rio)
 * qualquer vers�o posterior.
 * Este programa � distribu�do na expectativa de que seja �til, por�m,
 * SEM NENHUMA GARANTIA; nem mesmo a garantia impl�cita de COMERCIABILIDADE
 * OU ADEQUA��O A UMA FINALIDADE ESPEC�FICA. Consulte a Licen�a P�blica Geral
 * do GNU para mais detalhes. 
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral do GNU junto
 * com este programa; se n�o, escreva para a Free Software Foundation, Inc.,
 * no endere�o 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA. 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Universo Online S/A - A/C: UOL Messenger 5o. Andar
 * Avenida Brigadeiro Faria Lima, 1.384 - Jardim Paulistano
 * S�o Paulo SP - CEP 01452-002 - BRASIL  */
 

#include "stdafx.h"
#include "PhoneCallStateChangeHandler.h"

#include "../_UOLFoneClient.h"
#include "../FacadeWrapper.h"


CPhoneCallStateChangeHandler::CPhoneCallStateChangeHandler()
{
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_DIALING, CPhoneCall::PhoneCallStateDialing);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_CLOSED, CPhoneCall::PhoneCallStateClosed);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_TALKING, CPhoneCall::PhoneCallStateTalking);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_ERROR, CPhoneCall::PhoneCallStateError);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_UNKNOWN, CPhoneCall::PhoneCallStateError);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_RINGING, CPhoneCall::PhoneCallStateRinging);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_INCOMING, CPhoneCall::PhoneCallStateIncoming);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_BUSY, CPhoneCall::PhoneCallStateBusy);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_NO_ANSWER, CPhoneCall::PhoneCallStateNoAnswer);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_RESUMED, CPhoneCall::PhoneCallStateResumed);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_HOLD, CPhoneCall::PhoneCallStateHold);
	m_mapStates.SetAt(UFC_PHONE_CALL_STATE_REDIRECTED, CPhoneCall::PhoneCallStateRedirected);
}


CPhoneCallStateChangeHandler::~CPhoneCallStateChangeHandler()
{
	m_mapStates.RemoveAll();
}


CPhoneCall::PhoneCallState CPhoneCallStateChangeHandler::MapPhoneCallState(LONG lPhoneCallState)
{
	CPhoneCallStateMap::CPair* pPair = NULL;

	pPair = m_mapStates.Lookup(lPhoneCallState);

	if (pPair)
	{
		return pPair->m_value;
	}

	return CPhoneCall::PhoneCallStateUnknown;
}
