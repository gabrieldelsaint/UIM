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

#pragma once

#include "stdafx.h"
#include "PluginPreferencesPageContainer.h"
#include "PluginPreferencesPage.h"
#include "UIMApplication.h"

#include <interfaces/IUOLMessengerImageButton.h>


CPluginPreferencesPageContainer::CPluginPreferencesPageContainer()
{
}


CPluginPreferencesPageContainer::~CPluginPreferencesPageContainer()
{
}


void CPluginPreferencesPageContainer::RegisterObserver(CPluginPreferencesPageContainerObserver* pObserver)
{
	POSITION posFind = m_listObservers.Find(pObserver);

	if (!posFind)
	{
		m_listObservers.AddTail(pObserver);
	}
}


void CPluginPreferencesPageContainer::UnregisterObserver(CPluginPreferencesPageContainerObserver* pObserver)
{
	POSITION posFind = m_listObservers.Find(pObserver);

	if (posFind != NULL)
	{
		m_listObservers.RemoveAt(posFind);
	}
}


BOOL CPluginPreferencesPageContainer::AddPage(CString strPageName, 
                                              IUOLMessengerPreferencesPage2Ptr pPreferencesPage,
                                              IUOLMessengerImagePtr pImage)
{
	CPluginPreferencesPagePtr pPage = new CPluginPreferencesPage(strPageName, pPreferencesPage, pImage);
	
	BOOL bAdded = FALSE;

	if (pPage != NULL)
	{
		{
			CComCritSecLock<CComAutoCriticalSection> lock(m_csPages);

			IUOLMessengerPluginPreferencesPagePtr pFindPage = FindPageImpl(pPage->GetName());

			if (!pFindPage)
			{
				m_listPages.AddTail(pPage);
				bAdded = TRUE;
			}
		}

		if (bAdded)
		{
			NotifyObservers(&CPluginPreferencesPageContainerObserver::OnAddPage, pPage);
		}
	}

	return bAdded;
}


BOOL CPluginPreferencesPageContainer::RemovePage(const CString& strPageName)
{
	BOOL bRemoved = FALSE;
	IUOLMessengerPluginPreferencesPagePtr pRemovedPage;

	{
		CComCritSecLock<CComAutoCriticalSection> lock(m_csPages);

		for (POSITION pos = m_listPages.GetHeadPosition(); pos; m_listPages.GetNext(pos))
		{
			IUOLMessengerPluginPreferencesPagePtr pPage = m_listPages.GetAt(pos);

			if (MatchPage(strPageName, pPage))
			{
				pRemovedPage = pPage;			
				m_listPages.RemoveAt(pos);
				break;
			}
		}
	}

	if (pRemovedPage != NULL)
	{
		NotifyObservers(&CPluginPreferencesPageContainerObserver::OnRemovePage, pRemovedPage);
		bRemoved = TRUE;
	}

	return bRemoved;
}


IUOLMessengerPluginPreferencesPagePtr CPluginPreferencesPageContainer::FindPage(const CString& strPageName)
{
	CComCritSecLock<CComAutoCriticalSection> lock(m_csPages);

	return FindPageImpl(strPageName);
}


void CPluginPreferencesPageContainer::GetPages(CAtlList<IUOLMessengerPluginPreferencesPagePtr>& listPages)
{
	listPages.RemoveAll();

	CComCritSecLock<CComAutoCriticalSection> lock(m_csPages);

	for (POSITION pos = m_listPages.GetHeadPosition(); pos; )
	{
		IUOLMessengerPluginPreferencesPagePtr pPage = m_listPages.GetNext(pos);
		listPages.AddTail(pPage);
	}
}


void CPluginPreferencesPageContainer::NotifyObservers(void (CPluginPreferencesPageContainerObserver::*pfnHandler)(IUOLMessengerPluginPreferencesPagePtr), IUOLMessengerPluginPreferencesPagePtr pPage)
{
	CPluginPreferencesPageContainerObserver* pObserver;

	for (POSITION pos = m_listObservers.GetHeadPosition(); pos; )
	{
		pObserver = m_listObservers.GetNext(pos);

		if (FALSE == ::IsBadReadPtr(pObserver, sizeof(CPluginPreferencesPageContainerObserver*)))
		{
			(pObserver->*pfnHandler)(pPage);
		}
	}
}


BOOL CPluginPreferencesPageContainer::MatchPage(const CString& strPageName, IUOLMessengerPluginPreferencesPagePtr pPage)
{
	return (0 == strPageName.Compare(pPage->GetName()));
}


IUOLMessengerPluginPreferencesPagePtr CPluginPreferencesPageContainer::FindPageImpl(const CString& strPageName)
{
	IUOLMessengerPluginPreferencesPagePtr pFindPage;

	for (POSITION pos = m_listPages.GetHeadPosition(); pos; )
	{
		IUOLMessengerPluginPreferencesPagePtr pPage = m_listPages.GetNext(pos);

		if (MatchPage(strPageName, pPage))
		{
			pFindPage = pPage;
			break;
		}
	}

	return pFindPage;
}
