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

#include <interfaces/IUOLMessengerContact.h>
#include <interfaces/IUOLMessengerRemoteContactList.h>

#include "DummyWindow.h"
#include "MainFrm.h"
#include "DetailsWindow.h"


class CInfoWindow;
typedef CWindowElement<CInfoWindow, CDummyWindow<CWindowImpl<CInfoWindow> > > CInfoWindowBase;


class CInfoWindow : public CInfoWindowBase,
					public CUOLMessengerRemoteContactListObserver,
					public CUOLMessengerImageButtonEventListener
{
public:
	DECLARE_WND_CLASS_EX("InfoWindow", CS_DBLCLKS, COLOR_WINDOW);

	CInfoWindow(CMainFrame* pParentFrame, IUOLMessengerContactPtr pContact);
	virtual ~CInfoWindow();

	IUOLMessengerContactPtr GetContact();

	void OnContactGotInfo(IUOLMessengerAccountPtr pAccount, const CString& strContact, const CString& strInfo);

protected:
	enum 
	{
		WM_USER_CONTACT_INFO_RECEIVED = WM_USER + 0x400
	};

	typedef struct _CONTACTINFOEVENT
	{
		CString		strInfo;
	} CONTACTINFOEVENT, * LPCONTACTINFOEVENT;
	

	BEGIN_MSG_MAP(CInfoWindow)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		//MSG_WM_SIZE(OnSize)
		MESSAGE_HANDLER(WM_USER_CONTACT_INFO_RECEIVED, OnContactInfoReceivedEvent)
		CHAIN_MSG_MAP(CInfoWindowBase)
	END_MSG_MAP()

	LRESULT OnCreate(LPCREATESTRUCT lpCreatestruct);
	void OnDestroy();
	LRESULT OnContactInfoReceivedEvent(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	virtual void UpdateLayout(BOOL bResizeBars = TRUE);

private:
	CMainFrame*			m_pParentFrame;

	IUOLMessengerContactPtr		m_pContact;
	
	CDetailsWindowPtr	m_pDetailsWindow;
}; 
MAKEAUTOPTR(CInfoWindow);