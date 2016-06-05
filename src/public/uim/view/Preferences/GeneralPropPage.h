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

#include "PreferencesPropPage.h"
#include "../../resource.h"
#include <interfaces/IUOLMessengerThemeManager.h>
#include <interfaces/IUOLMessengerSettingsManager.h>
#include <interfaces/IUOLMessengerGeneralSettings.h>


// CMessagesPropPage dialog

class CGeneralPropPage : public CPreferencesPropPage,
					   public CWinDataExchange<CGeneralPropPage>

{
public:
	CGeneralPropPage();
	virtual ~CGeneralPropPage();

	void FillSkinCombo();
	void FillThemeCombo();

	virtual void OnApply();

protected:
	BEGIN_MSG_MAP(CGeneralPropPage)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_ID_HANDLER_EX(IDC_CHECK_OPEN_IE, OnCheckButtonClicked)
		COMMAND_ID_HANDLER_EX(IDC_CHECK_AUTO_STARTUP, OnCheckButtonClicked)
		COMMAND_ID_HANDLER_EX(IDC_CHECK_DEFAULT_PROFILE, OnCheckButtonClicked)
		COMMAND_HANDLER_EX(IDC_GENERAL_PASSWORD_CHANGE, BN_CLICKED, OnGeneralPasswordChange)
		CHAIN_MSG_MAP(CPreferencesPropPage)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CGeneralPropPage)
		DDX_CONTROL_HANDLE(IDC_CHECK_AUTO_STARTUP, m_btnAutoStartup)
		DDX_CONTROL_HANDLE(IDC_CHECK_DEFAULT_PROFILE, m_btnDefautProfile)
	END_DDX_MAP()

	LRESULT OnCtlColor(HDC hdc, HWND hwnd);
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	LRESULT OnComboThemeChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCheckButtonClicked(UINT /*uCode*/, int nID, HWND hwndCtrl);

protected:
	IUOLMessengerSettingsManagerPtr	m_pSettingManager;

	CButton			m_btnOpenIE;
	CButton			m_btnAutoStartup;
	CButton			m_btnDefautProfile;

	CString			m_strProfile;
	CString			m_strNewTheme;

	enum NotifyListener
	{
		NL_AUTO_STARTUP				= 1,
		NL_OPEN_IE					= 2,
		NL_DEFAULT_PROFILE			= 4,
		NL_THEME_CHANGED			= 8
	};

	DWORD m_dwToNotify;


public:
	LRESULT OnGeneralPasswordChange(WORD wNotifyCode, WORD wID, HWND hWndCtl);
};
MAKEAUTOPTR(CGeneralPropPage);