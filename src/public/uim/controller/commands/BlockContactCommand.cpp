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
#include <commands/BlockContactCommand.h>

#include "../../resource.h"
#include "../UIMApplication.h"


CBlockContactCommand::CBlockContactCommand(IUOLMessengerContactPtr pContact, CWindow wnd) :
	m_strContactName(pContact->GetName()),
	m_wnd(wnd)
{
	m_pAccount = pContact->GetAccount();
}


CBlockContactCommand::CBlockContactCommand(IUOLMessengerAccountPtr pAccount, const CString& strContact, CWindow wnd) : 
	m_strContactName(strContact),
	m_wnd(wnd)
{
	m_pAccount = pAccount;
}


CBlockContactCommand::~CBlockContactCommand()
{
}


void CBlockContactCommand::Execute()
{
	ATLASSERT(m_pAccount);
	CString strMessage;

	CIMProtocol* pProtocol = m_pAccount->GetProtocol();
	UOLLib::ISettings* pStringLoader =  static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetStringLoader();
	ATLASSERT(pStringLoader);

	if (pProtocol && pProtocol->HasContactBlockingSupport())
	{
		if (FALSE == CUIMApplication::GetApplication()->GetAccountConnectionManager()->IsConnected(m_pAccount))
		{
			strMessage = pStringLoader->GetValue("uol.resource.error.IDS_TOGGLE_DENIED_CONTACT_ACCOUNT_NOT_CONNECTED_MSG");

			CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONERROR);

			return;
		}

		if (CUIMApplication::GetApplication()->GetPrivacyManager()->IsDenied(m_pAccount, m_strContactName))
		{
			strMessage = pStringLoader->GetValue("uol.resource.error.IDS_CONTACT_ALREADY_BLOCKED");

			CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONSTOP);
		}
		else
		{
			BOOL bCancelCommand = FALSE;

			CString strUser = m_pAccount->GetUserId();

			if (pProtocol->GetPrivacyFlags() & PRIVACY_FLAGS_REMOVE_DENIED_CONTACT)
			{
				strMessage.Format(IDS_REMOVE_TO_BLOCK, m_strContactName);

				if (CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_YESNO | MB_ICONQUESTION) != IDYES)
				{
					return;
				}
			}

			pProtocol->AddDenyContact((LPCTSTR) strUser, (LPCTSTR) m_strContactName);
		}
	}
	else
	{
		CString strFormat;
		strFormat = pStringLoader->GetValue("uol.resource.error.IDS_BLOCKING_NOT_SUPPORTED");
		strMessage.Format(strFormat, m_strContactName, m_pAccount->GetProtocolName());

		CUIMApplication::GetApplication()->GetUIManager()->ShowMessageBox(m_wnd, strMessage, MB_OK | MB_ICONSTOP);
	}
}