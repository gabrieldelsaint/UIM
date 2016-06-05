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
#include "UIMProtocolCallback.h"
#include "../view/IMContact.h"
#include "../view/IMGroup.h"

#include "../view/image/imagebuilder.h"
#include "../view/usermessages.h"


using namespace std;
using namespace Image;

CUIMProtocolCallback::CUIMProtocolCallback(CIMProtocol* pProtocol, CGroupListCtrl* pGroupListCtrl, CUserStatusPanel* pUserStatusPanel) : 
m_pProtocol(pProtocol),
m_pGroupListCtrl(pGroupListCtrl), 
m_pUserStatusPanel(pUserStatusPanel), 
m_pApplication(CUIMApplication::GetApplication())
{
	ATLASSERT(NULL != m_pApplication);
}


CUIMProtocolCallback::~CUIMProtocolCallback(void)
{
}


/*
void CUIMProtocolCallback::OnIMReceived(const string& strToUser, const string& strFromUser, const string& strText)
{
	ATLTRACE("CUIMProtocolCallback::OnIMReceived() - %s - %s - %s\n", strToUser.c_str(), strFromUser.c_str(), strText.c_str());

	CIMContactPtr pContact =  static_cast<CIMContactPtr>(m_pGroupListCtrl->GetEntryByName(strFromUser.c_str()));

	CThemePtr pTheme = CUIMApplication::GetApplication()->GetCurrentTheme();
	CIMContactBackgroundPainterPtr pPainter;

	if (pTheme != NULL)
	{
		pPainter = pTheme->GetPainter(CTheme::CL_CONTACT_ONMESSAGE_BGPAINTER);
	}

	if (pContact)
	{
		if (pPainter)
		{
			// TODO: Trocar o painter apenas se a aplica��o n�o estiver com o foco
            pContact->SetBkPainter(pPainter);
			pContact->Invalidate();
			pContact->Redraw();
			// TODO: Usar o timeout � ser definido pelo tema atual
			pContact->RestorePainter(5);
		}

		AddMessage(pContact, strText);
	}
}


void CUIMProtocolCallback::OnIMSent(const string& strFromUser, const string& strToUser, const string& strText)
{
	ATLTRACE("CUIMProtocolCallback::OnIMSent() - %s - %s - %s\n", strToUser.c_str(), strFromUser.c_str(), strText.c_str());

	CIMContactPtr pContact =  static_cast<CIMContactPtr>(m_pGroupListCtrl->GetEntryByName(strFromUser.c_str()));

	if (pContact)
	{
		AddMessage(pContact, strText);
	}
}


void CUIMProtocolCallback::OnIMSendError(const string& strFromUser, const string& strToUser, IMProtocolError sendError)
{
	ATLTRACE("CUIMProtocolCallback::OnIMSendError() - %s - %s - %d\n", strToUser.c_str(), strFromUser.c_str(), sendError);
}


void CUIMProtocolCallback::OnContactTyping(const string& strAccountUser, const string& strContact, TypingState state)
{
	ATLTRACE("CUIMProtocolCallback::OnContactTyping() - %s - %s\n", strAccountUser.c_str(), strContact.c_str());

	CIMContactPtr pContact = m_pGroupListCtrl->GetEntryByName(strContact.c_str());

	if (pContact != NULL)
	{
		CString strStatusBarText = _T("");
		if (state == TYPING)
		{
			CThemePtr pTheme = CUIMApplication::GetApplication()->GetCurrentTheme();
			CIMContactBackgroundPainterPtr pPainter;

			if (pTheme != NULL)
			{
				pPainter = pTheme->GetPainter(CTheme::CL_CONTACT_TYPING_BGPAINTER);
			}

			if (pPainter)
			{
				pContact->SetBkPainter(pPainter);
				pContact->Invalidate();
				pContact->Redraw();
				// TODO: Usar o timeout � ser definido pelo tema atual
				pContact->RestorePainter(1);
			}

			// TODO: Move to resource
			CString strContactTypingTemplate = _T("%s is typing...");
			strStatusBarText.Format(strContactTypingTemplate, pContact->GetName());
		}

		CConversationWindowPtr pConversationWindow;
		CMessageWindowPtr pMessageWindow = CMessageWindow::GetMessageWindow(pContact->GetName(), pConversationWindow);

		if (pMessageWindow != NULL)
		{
			pMessageWindow->SetStatusBarText(strStatusBarText);
		}
	}
}
*/


void CUIMProtocolCallback::AddMessage(CIMContactPtr pContact, const string& strText)
{
	CConversationWindowPtr pConversationWindow;

	do
	{
		CMessageWindowPtr pMessageWindow = CMessageWindow::GetMessageWindow(pContact->GetName(), pConversationWindow);

		if (!pMessageWindow)
		{
			// Create message window on main window message loop...
			CWindow wndMain = CUIMApplication::GetApplication()->GetMainWindow();

			CREATEMESSAGEWINDOWPARAM cmwp;
			cmwp.pContact = pContact;

			wndMain.SendMessage(WM_USER_CREATE_MESSAGE_WINDOW, (WPARAM) &cmwp);

			pMessageWindow = cmwp.pMessageWindow;
		}
		
		if ((pConversationWindow != NULL) &&
			(pMessageWindow != NULL))
		{
			pMessageWindow->ShowWindow(SW_NORMAL);
			pMessageWindow->SetFocus();

			pConversationWindow->AddReceivedMessage(strText.c_str());
		}
		
	} while (!pConversationWindow);
}