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
 

#include "Stdafx.h"
#include "MainFrameFocusNotifier.h"



CMainFrameFocusObserverWrapper::CMainFrameFocusObserverWrapper(CUOLMessengerMainFrameFocusObserver* pWrapped) :
		CObserverWrapper<CUOLMessengerMainFrameFocusObserver>(pWrapped)
{
}


void CMainFrameFocusObserverWrapper::OnSetFocus(HWND lostFocusWnd)
{
	BEGIN_HANDLER_CALL();

	m_pObserver->OnSetFocus(lostFocusWnd);

	END_HANDLER_CALL();
}


void CMainFrameFocusObserverWrapper::OnKillFocus(HWND newFocusWnd)
{
	BEGIN_HANDLER_CALL();

	m_pObserver->OnKillFocus(newFocusWnd);

	END_HANDLER_CALL();
}





void CMainFrameFocusNotifier::SetFocus(HWND lostFocusWnd)
{
	CAtlList<CMainFrameFocusObserverWrapperPtr> listObservers;
	
	{
		CComCritSecLock<CComAutoCriticalSection> lock(m_csObservers);
		
		listObservers.AddTailList(&m_listObservers);
	}
	
	CMainFrameFocusObserverWrapperPtr pObserver;
	
	for (POSITION pos = listObservers.GetHeadPosition(); pos; )
	{
		pObserver = listObservers.GetNext(pos);
		
		(pObserver.get())->OnSetFocus(lostFocusWnd);
	}
}


void CMainFrameFocusNotifier::KillFocus(HWND newFocusWnd)
{
	CAtlList<CMainFrameFocusObserverWrapperPtr> listObservers;
	
	{
		CComCritSecLock<CComAutoCriticalSection> lock(m_csObservers);
		
		listObservers.AddTailList(&m_listObservers);
	}
	
	CMainFrameFocusObserverWrapperPtr pObserver;
	
	for (POSITION pos = listObservers.GetHeadPosition(); pos; )
	{
		pObserver = listObservers.GetNext(pos);
		
		(pObserver.get())->OnKillFocus(newFocusWnd);
	}
}


void CMainFrameFocusNotifier::RegisterObserver(CUOLMessengerMainFrameFocusObserver* pObserver)
{
	if (pObserver != NULL)
	{	
		CComCritSecLock<CComAutoCriticalSection> lock(m_csObservers);
		
		for (POSITION pos = m_listObservers.GetHeadPosition(); pos; )
		{
			CMainFrameFocusObserverWrapperPtr pObserverWrapper = m_listObservers.GetNext(pos);
			
			if (pObserver == pObserverWrapper->GetWrappedObserver())
			{
				// Already registered!!!!
				ATLASSERT(FALSE);
				
				return;
			}
		}
		
		m_listObservers.AddTail(new CMainFrameFocusObserverWrapper(pObserver));
	}
}


void CMainFrameFocusNotifier::UnregisterObserver(CUOLMessengerMainFrameFocusObserver* pObserver)
{
	if (pObserver != NULL)
	{	
		CMainFrameFocusObserverWrapperPtr pRemovedObserverWrapper;
		
		{
			CComCritSecLock<CComAutoCriticalSection> lock(m_csObservers);
			
			for (POSITION pos = m_listObservers.GetHeadPosition(); pos; m_listObservers.GetNext(pos))
			{
				CMainFrameFocusObserverWrapperPtr pObserverWrapper = m_listObservers.GetAt(pos);

				if (pObserver == pObserverWrapper->GetWrappedObserver())
				{
					// Listener found!!!
					pRemovedObserverWrapper = pObserverWrapper;
					
					m_listObservers.RemoveAt(pos);
					
					break;
				}
			}
		}
		
		//ATLASSERT(pRemovedObserverWrapper);
		if (pRemovedObserverWrapper)
		{
			pRemovedObserverWrapper->DisableNotifications();
		}
	}
}

