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

#include "mainfrm.h"
#include "../resource.h"
#include "../controller/commandfactory.h"
#include <commands/ShowPreferencesCommand.h>
#include "../controller/UIMApplication.h"

//#include "UOLToolbar.h"
#include "ContactListTab.h"
#include "../controller/MainFrameFocusNotifier.h"
#include "../controller/MainWindowEventsNotifier.h"
#include "TabView.h"


class CAppWindow : public CMainFrame
{
public:
	CAppWindow(void);
	virtual ~CAppWindow(void);

	DECLARE_ELEMENT_NAME("AppWindow");

	HWND CreateAppWindow();
	
	CTabViewPtr GetAppTabViewCtrl();
	CContactListTabPtr GetContactListTab();
	CMainFrameFocusNotifierPtr GetMainFrameFocusNotifier();
	CMainWindowEventsNotifierPtr GetMainWindowEventsNotifier();
	
	void UpdateAccountInfoPanel(IUOLMessengerAccountPtr pAccount);
	
	CContextMenuPtr GetSystrayContextMenu();
	
protected:
	BEGIN_MSG_MAP(CAppWindow)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_TIMER(OnTimer)
		MSG_WM_ENDSESSION(OnEndSession)
		//COMMAND_ID_HANDLER(ID_ACCELERATOR_PREFERENCE, OnAccelaratorPreference)
		//COMMAND_ID_HANDLER(ID_ACCELERATOR_ADDCONTACT, OnAccelaratorAddContact)
		//COMMAND_ID_HANDLER(ID_ACCELERATOR_PRIVACY, OnAccelaratorPrivacy)
		//COMMAND_ID_HANDLER(ID_ACCELERATOR_ONLINE, OnAccelaratorOnline)
		//COMMAND_ID_HANDLER(ID_ACCELERATOR_OFFLINE, OnAccelaratorOffline)
		//COMMAND_ID_HANDLER(ID_ACCELERATOR_HELP, OnAccelaratorHelp)
		
		CHAIN_MSG_MAP(CMainFrame)
	END_MSG_MAP()
 	/*virtual BOOL PreTranslateMessage(MSG* pMsg);*/
	LRESULT OnCreate(LPCREATESTRUCT lpCreatestruct);
	LRESULT OnClose();
	void OnDestroy();
	void OnTimer(UINT nTimerId, TIMERPROC tp);
	void OnEndSession(BOOL bEndSession, UINT uReason);

	LRESULT OnAccelaratorPreference(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAccelaratorAddContact(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAccelaratorPrivacy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAccelaratorOnline(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAccelaratorOffline(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAccelaratorHelp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	virtual CString GetName() const;
	virtual IUOLMessengerCommandPtr GetCommand(const CString& strCommand);
private:

protected:
	enum
	{
		AUTO_AWAY_CHECK_TIMER = 0x500,
		IDLE_REPORT_TIMER,
		IDLE_REPORT_INTERVAL = 60	// seconds
	};

private:
	BOOL		m_bGotAway;
	HACCEL    m_haccelerator;
	UINT		m_nIdleReportTimer;		
};

MAKEAUTOPTR(CAppWindow);

class CAppWindowCommandFactory
{
public:
	//static IUOLMessengerCommandPtr GetCommand(const CString , CWindow*);
	static IUOLMessengerCommandPtr GetCommand(const CString& strCommand, CWindow* pWindow);
};