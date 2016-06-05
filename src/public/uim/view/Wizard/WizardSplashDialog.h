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

#include "UOLPropPageImpl.h"
#include "..\transparentstatic.h"
#include "..\TransparentControls.h"


class CWizardSplashDialog : public CUOLPropPageImpl,
    public CWinDataExchange<CWizardSplashDialog>,
	public CTransparentControls<CWizardSplashDialog>
{
public:
    enum { IDD = IDD_DIALOG_WIZARD_SPLASH };
	DECLARE_ELEMENT_NAME("WizardSplashDialog");

	CWizardSplashDialog();

    BEGIN_MSG_MAP(CWizardSplashDialog)
		CHAIN_MSG_MAP(CTransparentControls<CWizardSplashDialog>)
		COMMAND_HANDLER_EX(IDC_COMBO_WIZARD_SPLASH_PROFILE, LBN_SELCHANGE, OnSelectChange)
		COMMAND_ID_HANDLER_EX(IDC_CHECK_SPLASH_REMEMBER_PASSWORD, OnCheckButtonClicked)
		COMMAND_ID_HANDLER_EX(IDC_CHECK_SPLASH_OPEN_AUTO, OnCheckButtonClicked)
		MSG_WM_INITDIALOG(OnInitDialog)		
        CHAIN_MSG_MAP(CUOLPropPage)
    END_MSG_MAP()

    BEGIN_DDX_MAP(CWizardSplashDialog)
		DDX_CONTROL_HANDLE(IDC_COMBO_WIZARD_SPLASH_PROFILE, m_wndComboProfile)
		DDX_TEXT(IDC_EDIT_WIZARD_SPLASH_PASSWORD, m_strPassword)
		DDX_CONTROL_HANDLE(IDC_CHECK_SPLASH_REMEMBER_PASSWORD, m_btnRememberPass)
		DDX_CONTROL_HANDLE(IDC_CHECK_SPLASH_OPEN_AUTO, m_btnAutoOpen)
	END_DDX_MAP()

	void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);	
	CString GetName() const;

	void SetUOLWizard(CUOLWizard* pWizard);

    BOOL OnInitDialog ( HWND hwndFocus, LPARAM lParam );	

	BOOL OnBtnNext();
	BOOL HasNextPage();
	BOOL OnBtnCancel();
	CUOLPropPagePtr GetNextPage(CUOLPropPagePtr pCurrentProp);
	CString GetNextBtnText();

	void OnCheckButtonClicked(UINT /*uCode*/, int nID, HWND hwndCtrl);
    void OnSelectChange(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	void OnBtnCustom(CUOLPropPagePtr pCurrentProp, UINT nCmdId);
	void SetOptions(IUOLMessengerProfileElementPtr pProfileElement);

	BOOL SaveProfile();

protected:
	int GetDlgID(){	return IDD_DIALOG_WIZARD_SPLASH; }

private:
	IUOLMessengerProfileManagerPtr	m_pProfileManager; 

	CComboBox m_wndComboProfile;

	BOOL m_bSave;

	CString m_strDefaultProfile;
	CString m_strPassword;

	CButton m_btnRememberPass;
	CButton m_btnAutoOpen;

	CTransparentStatic	m_staticEmail;
	CTransparentStatic	m_staticPass;
};

MAKEAUTOPTR(CWizardSplashDialog);