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
#include "ChatMenu.h"

#include "../../resource.h"
#include "../../controller/UIMApplication.h"
#include <interfaces/IUOLMessengerGroup.h>
#include <commands/sendfilecommand.h>
#include <commands/launchinfowindowcommand.h>
#include <commands/BlockContactCommand.h>
#include <commands/UnblockContactCommand.h>
#include <commands/ShowContactDialogCommand.h>


using namespace std;


CChatMenu::CChatMenu() :
	m_bBusy(FALSE)
{
}


CChatMenu::~CChatMenu()
{
}


IUOLMessengerContact3Ptr CChatMenu::GetContact()
{
	return m_pContact;
}


BOOL CChatMenu::IsBusy() const
{
	return m_bBusy;
}


void CChatMenu::CreateMenu(IUOLMessengerContact3Ptr pContact)
{
	if ((pContact != NULL) && (!m_bBusy))
	{
		m_pContact = pContact;

		CreateContextMenu();
	}
}


void CChatMenu::ShowMenu(const CPoint& ptPoint)
{
	if ((m_pMainMenu != NULL) && (!m_bBusy))
	{
		m_pMainMenu->ShowMenu(ptPoint);
	}
}


void CChatMenu::DestroyMenu()
{
	if (m_pMainMenu != NULL)
	{
		m_pMainMenu->DestroyMenu();
		m_pMainMenu.reset();
	}
}


CContextMenuPtr CChatMenu::GetContextMenu()
{
	return m_pMainMenu;
}


void CChatMenu::OnCommand(IUOLMessengerContextMenuItem* pItem)
{
	if (!m_pContact)
	{
		return;
	}

	m_bBusy = TRUE;

	CString strAlias;
	CString name;
	string m_protocol;
	CString account;

	IUOLMessengerAccountPtr pAccount = m_pContact->GetAccount();
	IUOLMessengerGroupPtr pGroup;

	IUOLMessengerCommandPtr pCommand;

	CString strMessage;
	CString strInputCaption, strInputLabel;

	if (pAccount)
	{
		switch (pItem->GetCommand())
		{
		case CC_TURN_VISIBLE:
		case CC_TURN_INVISIBLE:
			// Visibility
			if (CUIMApplication::GetApplication()->GetPrivacyManager()->IsPermited(pAccount, m_pContact->GetName()))
			{
				CUIMApplication::GetApplication()->GetPrivacyManager()->RemovePermitedContact(pAccount, m_pContact->GetName());
			}
			else
			{
				CUIMApplication::GetApplication()->GetPrivacyManager()->AddPermitedContact(pAccount, m_pContact->GetName());
			}
			break;

		case CC_BLOCK_CONTACT:
			pCommand = new CBlockContactCommand(pAccount, m_pContact->GetName(), CUIMApplication::GetApplication()->GetUIManager()->GetAppWindow());
			pCommand->Execute();
			break;

		case CC_UNBLOCK_CONTACT:
			pCommand = new CUnblockContactCommand(pAccount, m_pContact->GetName(), CUIMApplication::GetApplication()->GetUIManager()->GetAppWindow());
			pCommand->Execute();
			break;
		
		case CC_ADD_CONTACT:
			// Add Contact
            IUOLMessengerCommandPtr pCommand = new CShowContactDialogCommand(pAccount, m_pContact->GetName());
            IUOLMessengerFacade* pApplication = CUIMApplication::GetApplication();

            if (pCommand)
            {
                pApplication->ExecuteCommand(pCommand);
            }
            break;
		}
	}

	m_bBusy = FALSE;
}


void CChatMenu::CreateContextMenu()
{
	IUOLMessengerAccountPtr pAccount = m_pContact->GetAccount();

	if (!pAccount)
	{
		return;
	}

	CIMProtocol* pProtocol = pAccount->GetProtocol();

	if (!pProtocol)
	{
		return;
	}

	CString strMenuText;

	if (m_pMainMenu != NULL)
	{
		m_pMainMenu->DestroyMenu();
	}

	m_pMainMenu = new CContextMenu();

	CAtlList<IUOLMessengerGroupPtr> listGroups;
	IUOLMessengerContactListPtr pContactList = CUIMApplication::GetApplication()->GetContactList();

	pContactList->GetGroupList(listGroups);

	if (m_pMainMenu->CreateMenu())
	{
		IUOLMessengerContextMenuItemPtr pMenuItem;

        UOLLib::ISettings* pStringLoader =  static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->GetStringLoader();
	
		if (!m_pContact->IsContact())
        {
            strMenuText = pStringLoader->GetValue("uol.resource.IDS_CONTACT_NODE_ADDCONTACT_CAPTION");
            pMenuItem = new CContextMenuItem(CC_ADD_CONTACT, strMenuText, this);
            m_pMainMenu->AddItem(pMenuItem);

            m_pMainMenu->AddSeparator();
        }

        // Block/unblock
		if (pProtocol->HasContactBlockingSupport())
		{
			

			if (!CUIMApplication::GetApplication()->GetPrivacyManager()->IsDenied(pAccount, m_pContact->GetName()))
			{
				strMenuText = pStringLoader->GetValue("uol.resource.IDS_CONTACT_NODE_BLOCKCONTACT_CAPTION");

				pMenuItem = new CContextMenuItem(CC_BLOCK_CONTACT, strMenuText, this);
				m_pMainMenu->AddItem(pMenuItem);
			}
			else
			{
				strMenuText = pStringLoader->GetValue("uol.resource.IDS_CONTACT_NODE_UNBLOCKCONTACT_CAPTION");

				pMenuItem = new CContextMenuItem(CC_UNBLOCK_CONTACT, strMenuText, this);
				m_pMainMenu->AddItem(pMenuItem);
			}

			if (!(pProtocol->GetPrivacyFlags() & PRIVACY_FLAGS_NO_LIST_INTERSECTION))
			{
				if (!CUIMApplication::GetApplication()->GetPrivacyManager()->IsPermited(pAccount, m_pContact->GetName()))
				{
					strMenuText = pStringLoader->GetValue("uol.resource.IDS_CONTACT_NODE_INVISIBLE_CAPTION");

					pMenuItem = new CContextMenuItem(CC_TURN_INVISIBLE, strMenuText, this);
					m_pMainMenu->AddItem(pMenuItem);
				}
				else
				{
					strMenuText = pStringLoader->GetValue("uol.resource.IDS_CONTACT_NODE_VISIBLE_CAPTION");

					pMenuItem = new CContextMenuItem(CC_TURN_VISIBLE, strMenuText, this);
					m_pMainMenu->AddItem(pMenuItem);
				}
			}
		}
	}
}

void CChatMenu::AddItens(CAtlList<IUOLMessengerContextMenuItemPtr>& listItens)
{
	for (POSITION pos = listItens.GetHeadPosition(); pos;)
	{
		IUOLMessengerContextMenuItemPtr pMenuItem = listItens.GetNext(pos);
		
		if (pMenuItem)
		{
			m_pMainMenu->AddItem(pMenuItem);
		}
	}
}

void CChatMenu::AddSeparator()
{
	m_pMainMenu->AddSeparator();
}