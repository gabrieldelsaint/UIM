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
#include "UOLFoneCapabilitiesHandler.h"

#include "FacadeWrapper.h"


//#define UOL_XMLNS_ATTRIB "xmlns"
//#define UOL_NODE_ATTRIB "node"
//#define UOL_VER_ATTRIB "ver"
#define UOL_EXT_ATTRIB "ext"

#define UOL_EXT_VALUE "audio-v1"


CUOLFoneCapabilitiesHandler::CUOLFoneCapabilitiesHandler()
{
}


CUOLFoneCapabilitiesHandler::~CUOLFoneCapabilitiesHandler()
{
}


BOOL CUOLFoneCapabilitiesHandler::PublishCapabilities(IUOLMessengerAccountPtr pIMAccount)
{
	if (pIMAccount)
	{
		IUOLMessengerAccount2Ptr pIMAccount2 = ap_dynamic_cast<IUOLMessengerAccount2Ptr>(pIMAccount);

		if (pIMAccount2)
		{
			CProtocolSettings2Ptr pExtendedCapabilities = new CProtocolSettings2();

			if (pExtendedCapabilities)
			{
				pExtendedCapabilities->SetString(UOL_EXT_ATTRIB, UOL_EXT_VALUE);

				pIMAccount2->SetExtendedCapabilities(pExtendedCapabilities);

				IUOLMessengerAccountConnectionManager2Ptr pAccountConnectionManager2 = GetAccountConnectionManager();

				if (pAccountConnectionManager2)
				{
					ATLTRACE(_T("%s\n"), __FUNCTION__);

					return pAccountConnectionManager2->UpdateExtendedCapabilities(pIMAccount2);
				}
			}
		}
	}

	return FALSE;
}


BOOL CUOLFoneCapabilitiesHandler::RevokeCapabilities(IUOLMessengerAccountPtr pIMAccount)
{
	if (pIMAccount)
	{
		IUOLMessengerAccount2Ptr pIMAccount2 = ap_dynamic_cast<IUOLMessengerAccount2Ptr>(pIMAccount);

		if (pIMAccount2)
		{
			pIMAccount2->SetExtendedCapabilities(CProtocolSettings2Ptr());

			IUOLMessengerAccountConnectionManager2Ptr pAccountConnectionManager2 = GetAccountConnectionManager();

			if (pAccountConnectionManager2)
			{
				ATLTRACE(_T("%s\n"), __FUNCTION__);

				return pAccountConnectionManager2->UpdateExtendedCapabilities(pIMAccount2);
			}
		}
	}

	return FALSE;
}


BOOL CUOLFoneCapabilitiesHandler::CheckCapabilitiesCompatibility(IUOLMessengerContactPtr pContact)
{
	if (pContact)
	{
		IUOLMessengerAccountPtr pIMAccount = pContact->GetAccount();
		
		if (pIMAccount)
		{
			IUOLMessengerAccount2Ptr pIMAccount2 = ap_dynamic_cast<IUOLMessengerAccount2Ptr>(pIMAccount);
			IUOLMessengerContact2Ptr pContact2 = ap_dynamic_cast<IUOLMessengerContact2Ptr>(pContact);
			
			if (pIMAccount2 && pContact2)
			{
				CProtocolSettings2Ptr pUserExtendedCapabilities = pIMAccount2->GetExtendedCapabilities();
				CProtocolSettings2Ptr pContactExtendedCapabilities = pContact2->GetExtendedCapabilities();
				
				if (pContactExtendedCapabilities && pUserExtendedCapabilities)
				{
					std::string strUserAudioExt;
					std::string strContactAudioExt;
					if ( (pContactExtendedCapabilities->GetString(UOL_EXT_ATTRIB, strContactAudioExt)) &&
							(pUserExtendedCapabilities->GetString(UOL_EXT_ATTRIB, strUserAudioExt)) &&
							(0 == strContactAudioExt.compare(UOL_EXT_VALUE)) && 
							(0 == strContactAudioExt.compare(strUserAudioExt)) )
					{
						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;

	/*
	BOOL isCompactible = TRUE;
	
	if (pContact)
	{
		char firstChar = pContact->GetAlias().GetAt(0);
		
		if (tolower(firstChar) >= 'j')
		{
			isCompactible = FALSE;
		}
	}
	
	return isCompactible;
	*/
}


IUOLMessengerAccountConnectionManager2Ptr CUOLFoneCapabilitiesHandler::GetAccountConnectionManager()
{
	IUOLMessengerAccountConnectionManager2Ptr pAccountConnectionManager2;

	IUOLMessengerFacade* pFacade = CFacadeWrapper::GetFacadeInstance();

	if (pFacade)
	{
		IUOLMessengerAccountConnectionManagerPtr pAccountConnectionManager = pFacade->GetAccountConnectionManager();

		if (pAccountConnectionManager)
		{
			pAccountConnectionManager2 = ap_dynamic_cast<IUOLMessengerAccountConnectionManager2Ptr>(pAccountConnectionManager);
		}
	}

	return pAccountConnectionManager2;
}