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
#include "../../resource.h"

#include <interfaces/IUOLMessengerProfileManager.h>
#include <interfaces/IUOLMessengerAccount.h>

#include "UOLPropPageImpl.h"
#include "../transparentstatic.h"


class CWizardMSNAccountDialog : public CUOLPropPageImpl,
    public CWinDataExchange<CWizardMSNAccountDialog>
{
public:
    enum { IDD = IDD_DIALOG_WIZARD_MSN_ACCOUNT };
	DECLARE_ELEMENT_NAME("WizardMSNAccountDialog");

	CWizardMSNAccountDialog();
	~CWizardMSNAccountDialog();

    BEGIN_MSG_MAP(CWizardMSNAccountDialog)
        MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CTLCOLORSTATIC(OnCtlColor) 
		COMMAND_HANDLER_EX(IDC_BUTTON_WIZARD_MSN_ADD_ACCOUNT, BN_CLICKED, OnClickButton)
		COMMAND_HANDLER_EX(IDC_LIST_WIZARD_MSN_ACCOUNTS, LBN_SELCHANGE, OnSelectChange)
        CHAIN_MSG_MAP(CUOLPropPageImpl)
    END_MSG_MAP()

    BEGIN_DDX_MAP(CWizardMSNAccountDialog)
		DDX_TEXT(IDC_EDIT_WIZARD_MSN_ID, m_strEmail)
		DDX_TEXT(IDC_EDIT_WIZARD_MSN_PASSWORD, m_strPassword)
    END_DDX_MAP()

	void SetAccountsList(CAtlList<IUOLMessengerAccountPtr>* pAccountsList);
	void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);	
	CString GetName() const;

	void SetUOLWizard(CUOLWizard* pWizard);

    BOOL OnInitDialog (HWND hwndFocus, LPARAM lParam);	
    LRESULT OnCtlColor(HDC hDC, HWND hwnd);

	CString GetCancelBtnText();
	BOOL OnBtnNext();
	BOOL HasNextPage();
	BOOL OnBtnCancel();

	BOOL CaptureMSNAccounts();

	CUOLPropPagePtr GetNextPage(CUOLPropPagePtr pCurrentProp);

    void OnClickButton(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
    void OnSelectChange(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
    void OnChange(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);

    BOOL CheckDuplicateAccount(const CString& strUserId, const CString& strProtocolId, IUOLMessengerAccountPtr pCurrentAccount);

protected:
	int GetDlgID(){	return IDD_DIALOG_WIZARD_MSN_ACCOUNT; }

private:
	static const CString m_strIdentitiesKey;
	static const CString m_strProtocolId;

	CListBox m_lstbCaptured;

	IUOLMessengerProfileManagerPtr	m_pProfileManager;
    IUOLMessengerAccountPtr m_pAccount;
	AccountsList* m_pAccountsList;  

	COLORREF			m_bkg;			
	WTL::CBrush			m_brushStatic;

	CIMProtocol* m_pProtocol;

	CString m_strEmail;
	CString m_strPassword;

	CTransparentStatic m_staticEmail;		
	CTransparentStatic m_staticPass;
	CTransparentStatic m_staticHeader;
	CTransparentStatic m_staticSubHeader;
	CTransparentStatic m_staticInfo;
};

MAKEAUTOPTR(CWizardMSNAccountDialog);