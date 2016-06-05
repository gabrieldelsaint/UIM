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


#include "interfaces/IUOLMessengerContact.h"
#include "interfaces/IUOLMessengerUserIcon.h"
#include "interfaces/IUOLMessengerUIManager.h"

#include "WTLWndComponentsOrganizer.h"
#include "IUOLMessengerPluginCustomTabChildWindow.h"
#include "UOLFoneOrganizedColoredPanel.h"
#include "PictureExWnd.h"
#include "UOLFoneChildWindowInfo.h"




/////////////////////////////////////////////////////////////////////
// CUOLFoneAccountDisconnectedStatusPanel
/////////////////////////////////////////////////////////////////////


class CUOLFoneAccountDisconnectedStatusPanel : public CUOLFoneOrganizedColoredPanel
{
public:
	
	CUOLFoneAccountDisconnectedStatusPanel(void);
	~CUOLFoneAccountDisconnectedStatusPanel(void);
	
	void SetStatusString(LPCTSTR statusStr);
	
protected:
	
	BEGIN_MSG_MAP(CUOLFoneAccountDisconnectedStatusPanel)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP(CUOLFoneOrganizedColoredPanel)
		FORWARD_NOTIFICATIONS()
	END_MSG_MAP()
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
private:
	
	CPictureExWnd		m_pictureWnd;
	WTL::CStatic		m_initializingImage;
	WTL::CStatic		m_initializingText;
	
	WTL::CFont			m_textFont;
	
	COLORREF			m_backgroundColor;
	COLORREF			m_textColor;
};




/////////////////////////////////////////////////////////////////////
// CUOLFoneAccountDisconnectedWindow
/////////////////////////////////////////////////////////////////////


class CUOLFoneAccountDisconnectedWindow;

typedef CWinTraits<WS_CHILD | WS_CLIPCHILDREN, WS_EX_TOPMOST> CTopMostControlWinTraits;


class CUOLFoneAccountDisconnectedWindow : 
		public CWindowImpl<CUOLFoneAccountDisconnectedWindow, CWindow, CTopMostControlWinTraits>,
		public IUOLMessengerPluginCustomTabChildWindow
{
public:
	
	DECLARE_WND_CLASS(NULL)
	
	CUOLFoneAccountDisconnectedWindow();
	~CUOLFoneAccountDisconnectedWindow();
	
	virtual void GetMinSize(CSize& size);
	virtual void UpdateAccountInfo(CUOLFoneAccountPtr pAccount);
	virtual void UpdatePhoneCallInfo(CPhoneCallPtr pPhoneCall);
	virtual void SetChildWindowInfo(CUOLFoneChildWindowInfo childWindowInfo);
	
protected:
	
	BEGIN_MSG_MAP(CUOLFoneAccountDisconnectedWindow33)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_RANGE_HANDLER(WM_CTLCOLOREDIT, WM_CTLCOLORSTATIC, OnCtlColor)
	END_MSG_MAP()
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCtlColor(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
private:
	
	// Interface elements.
	WTL::CStatic						m_centerFiller;
	
	CUOLFoneAccountDisconnectedStatusPanel		m_statusPanel;
	
	CWTLWndComponentsOrganizer	m_componentsOrganizer;
	
	BOOL						m_destroyingWindow;
	CComAutoCriticalSection		m_destroyWindowLock;
};

MAKEAUTOPTR(CUOLFoneAccountDisconnectedWindow);

