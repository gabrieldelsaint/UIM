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
#include "MessageReceivingDialog.h"

#include "../controller/UIMApplication.h"
#include "../controller/UIManager.h"
#include "../controller/Message/MessageReceivingDialogController.h"


CMessageReceivingDialog::CMessageReceivingDialog() :
		CMainDialog(IDD_DIALOG_MESSAGE_RECEIVING_CONFIRM)
{
		
}


void CMessageReceivingDialog::Initialize(IUOLMessengerContactPtr pContact)
{
	m_pContact = pContact;
}


CMessageReceivingDialog::~CMessageReceivingDialog()
{
}


IUOLMessengerContactPtr CMessageReceivingDialog::GetContact()
{
	return m_pContact;
}


LRESULT CMessageReceivingDialog::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
	__super::OnInitDialog(NULL, NULL);

	CenterWindow();

	UOLLib::ISettings* pStringLoader = static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetStringLoader();
	ATLASSERT(pStringLoader);

	if (pStringLoader)
	{
		CString strTitle = pStringLoader->GetValue(_T("uol.resource.IDS_APP_NAME"));
		ATLASSERT(FALSE == strTitle.IsEmpty());

		SetTitle(strTitle);
	}

	CStatic wndStatic = GetDlgItem(IDC_STATIC_CONFIRM_TEXT);

	CString strMessage;
	strMessage.Format(IDS_CONFIRM_MESSAGE_RECEIVING_FORMAT, m_pContact->GetName());

	wndStatic.SetWindowText(strMessage);

	m_labelTransparencyApplier.SubclassWindow(GetDlgItem(IDC_STATIC_CONFIRM_TEXT));

	return 0L;
}


void CMessageReceivingDialog::OnClose()
{
	DestroyWindow();
}


void CMessageReceivingDialog::OnDestroy()
{
}


void CMessageReceivingDialog::OnClickedButtonYes(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/)
{
	IUOLMessengerMessageReceivingFilterPtr pMessageReceivingFilter = CUIMApplication::GetApplication()->GetMessageReceivingFilter();

	pMessageReceivingFilter->AuthorizeContactMessages(m_pContact);

	CMessageQueueController* pMessageQueueController = static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetMessageQueueController();

	CAtlList<CInstantMessagePtr> listMessages;
	pMessageQueueController->RemoveMessages(m_pContact, listMessages);

	LaunchMessageWindow(listMessages);

	PostMessage(WM_CLOSE);
}


void CMessageReceivingDialog::OnClickedButtonNo(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/)
{
	IUOLMessengerMessageReceivingFilterPtr pMessageReceivingFilter = CUIMApplication::GetApplication()->GetMessageReceivingFilter();

	pMessageReceivingFilter->DenyContactMessages(m_pContact);

	CMessageQueueController* pMessageQueueController = static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetMessageQueueController();

	CAtlList<CInstantMessagePtr> listMessages;
	pMessageQueueController->RemoveMessages(m_pContact);

	PostMessage(WM_CLOSE);
}


void CMessageReceivingDialog::OnClickedButtonShowInfo(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/)
{
	CUIMApplication::GetApplication()->GetUIManager()->LaunchInfoWindow(m_pContact);
}


void CMessageReceivingDialog::OnFinalMessage(HWND /*hWnd*/)
{
	CUIManager* pUIManager = dynamic_cast<CUIManager*>(CUIMApplication::GetApplication()->GetUIManager().get());

	if (pUIManager)
	{
		pUIManager->GetMessageReceivingDialogController()->RemoveNotifyDialog(this);
	}
}


void CMessageReceivingDialog::LaunchMessageWindow(CAtlList<CInstantMessagePtr>& listMessages)
{
	CUIMApplication::GetApplication()->GetUIManager()->LaunchMessageWindow(m_pContact, FALSE);

	IUOLMessengerConversationPtr pConversation = CUIMApplication::GetApplication()->GetConversationManager()->FindConversation(m_pContact);

	if (pConversation)
	{
		for (POSITION pos = listMessages.GetHeadPosition(); pos; )
		{
			CInstantMessagePtr pInstantMessage = listMessages.GetNext(pos);

			pConversation->AddReceivedMessage(pInstantMessage->GetText(), pInstantMessage->GetTime());
		}
	}
}