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

#include "../resource.h"
#include "MainDialog.h"
#include "TransparentStatic.h"
#include "TransparentControls.h"

#include <interfaces/IUOLMessengerAccount.h>


class CAuthorizeDialog :
	public CMainDialog,
	public CWinDataExchange<CAuthorizeDialog>,
	public CTransparentControls<CAuthorizeDialog>
{
public:
	CAuthorizeDialog(void);
	virtual ~CAuthorizeDialog(void);

	void Initialize(IUOLMessengerAccountPtr pAccount, const CString& strContact, BOOL bAlreadyAdded);

	BOOL IsContactAuthorized() const;
	BOOL GetAddContactFlag() const;
	CString GetContactGroup() const;

protected:
	BEGIN_MSG_MAP(CAuthorizeDialog)	
		CHAIN_MSG_MAP(CTransparentControls<CAuthorizeDialog>)
		MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CLOSE(OnClose)
		COMMAND_ID_HANDLER_EX(IDOK, OnBnClickedButtonOK)
		COMMAND_ID_HANDLER_EX(IDCANCEL, OnBnClickedButtonCancel)
		COMMAND_ID_HANDLER_EX(IDC_BUTTON_SHOW_INFO, OnBnClickedShowInfo)
		COMMAND_ID_HANDLER_EX(IDC_CHECK_ADD_CONTACT, OnCheckAddContact)
		CHAIN_MSG_MAP(CMainDialog)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CAuthorizeDialog)
		DDX_RADIO(IDC_RADIO_ALLOW_CONTACT, m_bBlockContact);
		DDX_CHECK(IDC_CHECK_ADD_CONTACT, m_bAddContact);
		DDX_CONTROL_HANDLE(IDC_COMBO_CONTACT_GROUP, m_wndComboGroups)
	END_DDX_MAP()

	virtual LRESULT OnInitDialog(HWND hwnd, LPARAM lParam);
    virtual LRESULT OnDestroy();
	virtual LRESULT OnClose();

	void OnBnClickedButtonOK(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	void OnBnClickedButtonCancel(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	void OnBnClickedShowInfo(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	void OnCheckAddContact(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);

	IUOLMessengerAccountPtr GetAccount();
	CString GetContact() const;

private:
	void FillGroupList();
	void ResetAddContactFlag();

private:
	IUOLMessengerAccountPtr	m_pAccount;
	CString				m_strContact;
	BOOL				m_bAlreadyAdded;
	BOOL				m_bBlockContact;
	BOOL				m_bAddContact;
	CString				m_strAddGroup;
	CComboBox			m_wndComboGroups;
	CTransparentStatic	m_labelTransparencyApplier;
};


MAKEAUTOPTR(CAuthorizeDialog);