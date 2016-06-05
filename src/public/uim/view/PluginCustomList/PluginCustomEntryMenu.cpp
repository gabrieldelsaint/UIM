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
#include "PluginCustomEntryMenu.h"


CPluginCustomEntryMenu::CPluginCustomEntryMenu() :
	m_bBusy(FALSE)
{
}


CPluginCustomEntryMenu::~CPluginCustomEntryMenu()
{
}


IUOLMessengerPluginCustomListEntryPtr CPluginCustomEntryMenu::GetEntry()
{
	return m_pEntry;
}


BOOL CPluginCustomEntryMenu::IsBusy() const
{
	return m_bBusy;
}


void CPluginCustomEntryMenu::CreateMenu(IUOLMessengerPluginCustomListEntryPtr pEntry)
{
	if ((pEntry != NULL) && (!m_bBusy))
	{
		m_pEntry = pEntry;

		CreateContextMenu();
	}
}


void CPluginCustomEntryMenu::ShowMenu(const CPoint& ptPoint)
{
	if ((m_pMainMenu != NULL) && (!m_bBusy))
	{
		m_pMainMenu->ShowMenu(ptPoint);
	}
}


void CPluginCustomEntryMenu::DestroyMenu()
{
	if (m_pMainMenu != NULL)
	{
		m_pMainMenu->DestroyMenu();
		m_pMainMenu.reset();
	}
}


void CPluginCustomEntryMenu::OnCommand(IUOLMessengerContextMenuItem* pItem)
{
	m_bBusy = TRUE;

	int nCommand = pItem->GetCommand();

	CActionMap::CPair* pPair = m_mapActions.Lookup(nCommand);

	if (pPair != NULL)
	{
		IUOLMessengerPluginActionPtr pPluginAction = pPair->m_value;

		pPluginAction->DoAction();
	}

	m_bBusy = FALSE;
}


void CPluginCustomEntryMenu::CreateContextMenu()
{
	CString strMenuText;

	if (m_pMainMenu != NULL)
	{
		m_pMainMenu->DestroyMenu();
	}

	CAtlList<IUOLMessengerPluginActionPtr> listActions;
	m_pEntry->GetContextMenuActions(listActions);

	if (listActions.GetCount() > 0)
	{
		m_pMainMenu = new CContextMenu();

		if (m_pMainMenu->CreateMenu())
		{
			IUOLMessengerContextMenuItemPtr pMenuItem;
			int nCommandId = 0;

			for (POSITION pos = listActions.GetHeadPosition(); pos; )
			{
				IUOLMessengerPluginActionPtr pPluginAction = listActions.GetNext(pos);

				pMenuItem = new CContextMenuItem(nCommandId, pPluginAction->GetName(), this);
				m_pMainMenu->AddItem(pMenuItem);

				m_mapActions.SetAt(nCommandId, pPluginAction);
				nCommandId++;
			}
		}
	}
}