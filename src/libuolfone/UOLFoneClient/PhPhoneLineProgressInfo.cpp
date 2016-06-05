/* UOL Fone
 * Copyright (c) 2006 Universo Online S/A
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
 * Universo Online S/A - A/C: UOL Fone 5o. Andar
 * Avenida Brigadeiro Faria Lima, 1.384 - Jardim Paulistano
 * S�o Paulo SP - CEP 01452-002 - BRASIL  */


#include "stdafx.h"
#include "PhPhoneLineProgressInfo.h"


CPhPhoneLineProgressInfo::CPhPhoneLineProgressInfo(const phRegStateInfo_t* pRegStateInfo)
{
	ATLASSERT(pRegStateInfo != NULL);
	m_pRegStateInfo = pRegStateInfo;
}


CPhPhoneLineProgressInfo::~CPhPhoneLineProgressInfo()
{
}


LONG CPhPhoneLineProgressInfo::GetLineId() const
{
	return m_pRegStateInfo->regid;
}


EnumPhoneLineState CPhPhoneLineProgressInfo::GetState() const
{
	EnumPhoneLineState state = UFC_PHONE_LINE_STATE_UNKNOWN;

	switch (m_pRegStateInfo->regStatus)
	{
	case 401:	// Unauthorized
	case 407:	// Proxy authentication required
		state = UFC_PHONE_LINE_STATE_UNAUTHORIZED;
		break;

	case 404:	// Not found
	case 500:	// Server error
		state = UFC_PHONE_LINE_STATE_SERVER_ERROR;
		break;

	case 408:	// Request timeout
		state = UFC_PHONE_LINE_STATE_TIMEOUT;
		break;
		
	case 0:		// Register OK
		state = UFC_PHONE_LINE_STATE_REGISTERED;
		break;
		
	case 32768:	// Unregister OK
		state = UFC_PHONE_LINE_STATE_UNREGISTERED;
		break;

	case -1:	// PhApi finalized
	case -5:	// Server connection timeout (line id == 0)
		ATLASSERT(GetLineId() == 0);
		state = UFC_PHONE_LINE_STATE_CONNECTION_TIMEOUT;
		break;

	default:
		state = UFC_PHONE_LINE_STATE_UNKNOWN;
	}

	return state;
}


BOOL CPhPhoneLineProgressInfo::HasExtraHeaders() const
{
	return (m_pRegStateInfo->custom_headers != NULL);
}


void CPhPhoneLineProgressInfo::GetExtraHeaders(CAtlList<CHeaderDataPtr>& listHeaderInfo) const
{
	struct phCustomHeaderInfo *custom_header;

	listHeaderInfo.RemoveAll();

	for (custom_header = m_pRegStateInfo->custom_headers; custom_header != NULL; custom_header = custom_header->next)
	{
		if ((custom_header->name) && (custom_header->value))
		{
			CHeaderDataPtr pHeaderInfo = new CHeaderData(custom_header->name, custom_header->value);
			listHeaderInfo.AddTail(pHeaderInfo);
		}
	}
}