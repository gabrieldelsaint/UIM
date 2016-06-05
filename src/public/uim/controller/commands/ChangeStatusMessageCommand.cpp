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
 
#include "StdAfx.h"
#include <commands/ChangeStatusMessagecommand.h>
#include <interfaces/IUOLMessengerAccount.h>

#include "../../controller/UIManager.h"
#include "../../controller/UIMApplication.h"

#include "../../view/InputDialog.h"


CChangeStatusMessageCommand::CChangeStatusMessageCommand(CWindow wnd, CString OldStatusMessage, IUOLMessengerAccountPtr pAccount) : 
	m_wnd(wnd),
	m_OldStatusMessage(OldStatusMessage),
	m_pAccount(pAccount)
{
}

CChangeStatusMessageCommand::~CChangeStatusMessageCommand(void)
{
}

void CChangeStatusMessageCommand::Execute()
{
	UOLLib::ISettings* pStringLoader =  static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetStringLoader();
	ATLASSERT(pStringLoader);

	CString strCaption;
	CString strMessage;
	CString strStatusMessage;
	
	strCaption = pStringLoader->GetValue("uol.resource.IDS_CHANGE_STATUS_MESSAGE_TITLE");
	strMessage = pStringLoader->GetValue("uol.resource.IDS_CHANGE_STATUS_MESSAGE_LABEL");
		
	CUIManagerPtr pUIManager = ap_dynamic_cast<CUIManagerPtr>(
			CUIMApplication::GetApplication()->GetUIManager());
    ATLASSERT(pUIManager);

    CInputDialogPtr pdlg = pUIManager->GetInputDialog();
	pdlg->Initialize(strCaption, strMessage, IUOLMessengerAccount::MAX_ACCOUNT_STATUS_MESSAGE_LENGTH, 0, m_OldStatusMessage);

	if (pdlg)
	{
		strStatusMessage.Empty();

		if (IDOK == pdlg->DoModal(m_wnd))
		{
			strStatusMessage = pdlg->GetText();
			strStatusMessage.Trim();

			if (m_pAccount.get() == NULL)
			{
				CAtlList<IUOLMessengerAccountPtr> listAccounts;
				CUIMApplication::GetApplication()->GetAccountManager()->GetAccountList(listAccounts);

				for (POSITION pos = listAccounts.GetHeadPosition(); pos;)
				{
					IUOLMessengerAccount3Ptr pAccount3;
					pAccount3 = ap_dynamic_cast<IUOLMessengerAccount3Ptr>(listAccounts.GetNext(pos));

					if (pAccount3)
					{
						pAccount3->SetStatusMessage(strStatusMessage);
					}

					IUOLMessengerAccountConnectionManagerPtr pAccountConnectionManager = CUIMApplication::GetApplication()->GetAccountConnectionManager();
					ATLASSERT(pAccountConnectionManager);
					if (pAccountConnectionManager->IsConnected(pAccount3))
					{
						// Refresh user status to set new status message
						DWORD dwStatus = pAccountConnectionManager->GetStatus(pAccount3);
						pAccountConnectionManager->SetStatus(pAccount3, dwStatus);
					}
				}
			}
			else
			{
				if (m_pAccount.get() != NULL)
				{
					IUOLMessengerAccount3Ptr pAccount3;
					pAccount3 = ap_dynamic_cast<IUOLMessengerAccount3Ptr>(m_pAccount);

					if (pAccount3)
					{
						pAccount3->SetStatusMessage(strStatusMessage);
					}

					IUOLMessengerAccountConnectionManagerPtr pAccountConnectionManager = CUIMApplication::GetApplication()->GetAccountConnectionManager();
					ATLASSERT(pAccountConnectionManager);
					if (pAccountConnectionManager->IsConnected(m_pAccount))
					{
						// Refresh user status to set new status message
						DWORD dwStatus = pAccountConnectionManager->GetStatus(m_pAccount);
						pAccountConnectionManager->SetStatus(m_pAccount, dwStatus);
					}
				}
			}
		}
	}
}