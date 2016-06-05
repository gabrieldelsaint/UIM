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


#include "WTLWndComponentsOrganizer.h"
#include "IUOLMessengerPluginCustomTabChildWindow.h"
#include "UOLFoneOrganizedColoredPanel.h"
#include "UOLFoneChildWindowInfo.h"




/////////////////////////////////////////////////////////////////////
// CUOLFoneAccountConnectionErrorUserPanel
/////////////////////////////////////////////////////////////////////


class CUOLFoneAccountConnectionErrorUserPanel : public CUOLFoneOrganizedColoredPanel
{
public:
	
	CUOLFoneAccountConnectionErrorUserPanel(void);
	~CUOLFoneAccountConnectionErrorUserPanel(void);
	
	void UpdateWindowData();
	
protected:
	
	BEGIN_MSG_MAP(CUOLFoneAccountConnectionErrorUserPanel)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		CHAIN_MSG_MAP(CUOLFoneOrganizedColoredPanel)
		FORWARD_NOTIFICATIONS()
	END_MSG_MAP()
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(HDC hDc);
	LRESULT OnEraseBkgnd(HDC hDc);

private:
	
	WTL::CStatic	m_callUserImage;
	WTL::CStatic	m_lineSeparator;
	WTL::CStatic	m_sidesFiller;
	WTL::CStatic	m_callUserName;
	
	WTL::CFont		m_userNameFont;
	
	COLORREF		m_backgroundColor;
	COLORREF		m_textColor;
};




/////////////////////////////////////////////////////////////////////
// CUOLFoneAccountConnectionErrorStatusPanel
/////////////////////////////////////////////////////////////////////


class CUOLFoneAccountConnectionErrorStatusPanel : public CUOLFoneOrganizedColoredPanel
{
public:
	
	CUOLFoneAccountConnectionErrorStatusPanel(void);
	~CUOLFoneAccountConnectionErrorStatusPanel(void);
	
	void SetStatusString(LPCTSTR statusStr);
	
protected:
	
	BEGIN_MSG_MAP(CUOLFoneAccountConnectionErrorStatusPanel)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		CHAIN_MSG_MAP(CUOLFoneOrganizedColoredPanel)
		FORWARD_NOTIFICATIONS()
	END_MSG_MAP()
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
private:
	
	WTL::CStatic		m_accountConnectionErrorImage;
	WTL::CStatic		m_accountConnectionErrorText;
	
	WTL::CBitmap		m_accountConnectionErrorBitmap;
	
	WTL::CFont			m_textFont;
	
	COLORREF			m_backgroundColor;
	COLORREF			m_textColor;
};




/////////////////////////////////////////////////////////////////////
// CUOLFoneAccountConnectionErrorWindow
/////////////////////////////////////////////////////////////////////


class CUOLFoneAccountConnectionErrorWindow;

typedef CWinTraits<WS_CHILD | WS_CLIPCHILDREN, WS_EX_TOPMOST> CTopMostControlWinTraits;


class CUOLFoneAccountConnectionErrorWindow : 
		public CWindowImpl<CUOLFoneAccountConnectionErrorWindow, CWindow, CTopMostControlWinTraits>,
		public IUOLMessengerPluginCustomTabChildWindow
{
public:
	
	DECLARE_WND_CLASS(NULL)
	
	CUOLFoneAccountConnectionErrorWindow();
	~CUOLFoneAccountConnectionErrorWindow();
	
	virtual void GetMinSize(CSize& size);
	virtual void UpdateAccountInfo(CUOLFoneAccountPtr pAccount);
	virtual void UpdatePhoneCallInfo(CPhoneCallPtr pPhoneCall);
	virtual void SetChildWindowInfo(CUOLFoneChildWindowInfo childWindowInfo);
	
protected:
	
	BEGIN_MSG_MAP(CUOLFoneAccountConnectionErrorWindow27)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_RANGE_HANDLER(WM_CTLCOLOREDIT, WM_CTLCOLORSTATIC, OnCtlColor)
	END_MSG_MAP()
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCtlColor(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
private:
	
	// Interface elements.
	CUOLFoneAccountConnectionErrorUserPanel		m_userPanel;
	
	WTL::CStatic	m_lineSeparator;
	WTL::CStatic	m_centerFiller;
	
	CUOLFoneAccountConnectionErrorStatusPanel	m_statusPanel;
	
	CWTLWndComponentsOrganizer	m_componentsOrganizer;
};

MAKEAUTOPTR(CUOLFoneAccountConnectionErrorWindow);

