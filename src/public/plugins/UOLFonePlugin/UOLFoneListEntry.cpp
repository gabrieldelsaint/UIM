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
#include "RadioListEntry.h"

#include "resource.h"
#include "FacadeWrapper.h"

#include <interfaces/IUOLMessengerUIManager.h>


CRadioListEntry::CRadioListEntry(const CString& strEntryName, const CString& strPluginInternalName) :
	m_strEntryName(strEntryName),
	m_strPluginInternalName(strPluginInternalName)
{
}


CRadioListEntry::~CRadioListEntry()
{
	if (m_pFrameWindow)
	{
		CWindow wndFrameWindow;

		wndFrameWindow = m_pFrameWindow->GetHWND();

		if (wndFrameWindow.IsWindow())
		{
			wndFrameWindow.DestroyWindow();
		}
	}
}


CString CRadioListEntry::GetEntryName() const
{
	return m_strEntryName;
}


CString CRadioListEntry::GetPluginInternalName() const
{
	return m_strPluginInternalName;
}


IUOLMessengerPainterPtr CRadioListEntry::GetPainter()
{
	// Return null pointer to use default painting
	return IUOLMessengerPainterPtr();
}


IUOLMessengerImagePtr CRadioListEntry::GetIcon(BOOL& bTransparent)
{
	bTransparent = TRUE;

	// Load image from DLL resource
	if (!m_pImage)
	{
		IUOLMessengerUIManagerPtr pUIManager = CFacadeWrapper::GetFacadeInstance()->GetUIManager();

		if (pUIManager)
		{
			m_pImage = pUIManager->LoadImage(ATL::_AtlBaseModule.GetModuleInstance(), IDB_RADIO_LIST_ENTRY);
		}
	}

	return m_pImage;
}


CString CRadioListEntry::GetDisplayName()
{
	return _T("Radio Plugin");
}


void CRadioListEntry::OnLButtonDoubleClick(const CPoint& ptClient)
{
	OnReturnKeyPressed();
}


void CRadioListEntry::OnReturnKeyPressed()
{
	ShowDialog();
}


void CRadioListEntry::OnSelectionChanged(BOOL bSelected)
{
}


void CRadioListEntry::GetContextMenuActions(CAtlList<IUOLMessengerPluginActionPtr>& listActions)
{
}
//#include "core/radiouolwindow.h"
//CRadioUOLWindow  m_view;
void CRadioListEntry::ShowDialog()
{
	IUOLMessengerUIManagerPtr pUIManager = CFacadeWrapper::GetFacadeInstance()->GetUIManager();

	if (pUIManager)
	{
		CWindow wndFrameWindow;

		if (m_pFrameWindow)
		{
			wndFrameWindow = m_pFrameWindow->GetHWND();

			if (wndFrameWindow.IsWindow())
			{
				wndFrameWindow.BringWindowToTop();
			}
		}

		if (!m_pView)
		{
			m_pView = new CSampleFrameWindowView();
		}

		m_pFrameWindow = pUIManager->CreateFrameWindow(m_pView, CRect(CPoint(0, 0), CSize(300, 250)));

		if (m_pFrameWindow)
		{

			//::GetWindowRect
			RECT rect;
			pUIManager->GetAppWindow().GetWindowRect(&rect);
			m_pFrameWindow->SetCaptionText(GetDisplayName());
			m_pFrameWindow->SetStatusBarText(_T("Ready"));

			wndFrameWindow = m_pFrameWindow->GetHWND();
			wndFrameWindow.CenterWindow(::GetDesktopWindow());
			wndFrameWindow.ShowWindow(SW_NORMAL);
		}

		(*m_pView)->Navigate(CComBSTR("C:\\Documents and Settings\\Cristiano.macedo\\Desktop\\canais.html"),NULL,   NULL,NULL,NULL);
		

	}
}