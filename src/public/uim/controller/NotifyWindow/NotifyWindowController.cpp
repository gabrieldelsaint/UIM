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
#include "NotifyWindowController.h"		  


CNotifyWindowController CNotifyWindowController::m_windowController;



CNotifyWindowController::~CNotifyWindowController()
{
}


CNotifyWindowController* CNotifyWindowController::GetInstance()
{
	return &m_windowController;
}


CNotifyAddedDialogPtr CNotifyWindowController::GetWindow(IUOLMessengerContactPtr pContact, BOOL bAlreadyAdded)
{
	CNotifyAddedDialogPtr pWindow;
	
	if (pContact != NULL)
	{
		pWindow = FindWindow(pContact);

		if (!pWindow)
		{
			pWindow = new CNotifyAddedDialog(pContact, bAlreadyAdded);

			if (pWindow)
			{
				pWindow->Create(::GetDesktopWindow());
				pWindow->ShowWindow(SW_HIDE);

				m_listWindow.AddTail(pWindow);
			}
		}
	}

	return pWindow;
}


BOOL CNotifyWindowController::RemoveWindow(CNotifyAddedDialog* pWindow)
{
	if (!pWindow)
	{
		return FALSE;
	}

	IUOLMessengerContactPtr pTargetContact = pWindow->GetContact();

	CString strContactName = pTargetContact->GetName();
	CString strAccountUser = pTargetContact->GetAccount()->GetUserId();
	CString strAccountProtocol = pTargetContact->GetAccount()->GetProtocolId();

	for (POSITION pos = m_listWindow.GetHeadPosition(); pos; m_listWindow.GetNext(pos))
	{	
		CNotifyAddedDialogPtr pTempWindow = m_listWindow.GetAt(pos);

		if (pTempWindow.get() != NULL)
		{
			IUOLMessengerContactPtr pContact = pTempWindow->GetContact();

			if ((0 == strContactName.Compare(pContact->GetName())) &&
				(0 == strAccountUser.Compare(pContact->GetAccount()->GetUserId())) &&
				(0 == strAccountProtocol.Compare(pContact->GetAccount()->GetProtocolId())))
			{
				m_listWindow.RemoveAt(pos);

				return TRUE;
			}
		}
	}

	return FALSE;
}


BOOL CNotifyWindowController::DestroyWindow(CNotifyAddedDialogPtr pWindow)
{
	POSITION pos = m_listWindow.Find(pWindow);

	if (pos)
	{
		CNotifyAddedDialogPtr pRemovedInfoWindow = m_listWindow.GetAt(pos);

		ATLASSERT(pRemovedInfoWindow.get() == pWindow.get());

		if (pRemovedInfoWindow->IsWindow())
		{
			pRemovedInfoWindow->DestroyWindow();
		}

		m_listWindow.RemoveAt(pos);

		return TRUE;
	}

	return FALSE;
}


void CNotifyWindowController::DestroyAllWindows()
{
	while ((int) m_listWindow.GetCount() > 0)
	{
		CNotifyAddedDialogPtr pWindow = m_listWindow.RemoveHead();

		if (pWindow->IsWindow())
		{
			pWindow->DestroyWindow();
		}
	}
}


CNotifyAddedDialogPtr CNotifyWindowController::FindWindow(IUOLMessengerContactPtr pContact)
{
	if (pContact != NULL)
	{
		return FindWindow(pContact->GetAccount(), pContact->GetName());
	}

	return CNotifyAddedDialogPtr();
}


CNotifyAddedDialogPtr CNotifyWindowController::FindWindow(IUOLMessengerAccountPtr pAccount, const CString& strContactName)
{
	CString strAccountUser = pAccount->GetUserId();
	CString strAccountProtocol = pAccount->GetProtocolId();

	for (POSITION pos = m_listWindow.GetHeadPosition(); pos;)
	{
		CNotifyAddedDialogPtr pWindow = m_listWindow.GetNext(pos);

		if (pWindow)
		{
			IUOLMessengerContactPtr pContact = pWindow->GetContact();
			if ((0 == strContactName.Compare(pContact->GetName())) &&
				(0 == strAccountUser.Compare(pContact->GetAccount()->GetUserId())) &&
				(0 == strAccountProtocol.Compare(pContact->GetAccount()->GetProtocolId())))
			{
				return pWindow;
			}
		}
	}

	return CNotifyAddedDialogPtr();
}

CNotifyWindowController::CNotifyWindowController()
{
}
