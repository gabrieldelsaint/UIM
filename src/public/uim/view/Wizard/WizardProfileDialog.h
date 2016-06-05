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


#include "../../resource.h"

#include <interfaces/IUOLMessengerProfileManager.h>

#include "UOLPropPageImpl.h"
#include "..\transparentstatic.h"
#include "..\TransparentControls.h"

class CWizardProfileDialog : public CUOLPropPageImpl,
    public CWinDataExchange<CWizardProfileDialog>,
	public CTransparentControls<CWizardProfileDialog>
{
public:
    enum { IDD = IDD_DIALOG_WIZARD_PROFILE };
	DECLARE_ELEMENT_NAME("WizardProfileDialog");

	CWizardProfileDialog();
	~CWizardProfileDialog();

    BEGIN_MSG_MAP(CWizardProfileDialog)
		CHAIN_MSG_MAP(CTransparentControls<CWizardProfileDialog>)
        MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(CUOLPropPage)
    END_MSG_MAP()

    BEGIN_DDX_MAP(CWizardProfileDialog)
		DDX_TEXT(IDC_EDIT_WIZARD_PROFILE_EMAIL, m_strEmail)
		DDX_TEXT(IDC_EDIT_WIZARD_PROFILE_PASSWORD, m_strPassword)
		DDX_TEXT(IDC_EDIT_WIZARD_PROFILE_CONFIRM, m_strConfirm)
	END_DDX_MAP()

	void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);	
	CString GetName() const;

	void SetUOLWizard(CUOLWizard* pWizard);

    BOOL OnInitDialog ( HWND hwndFocus, LPARAM lParam );
	LRESULT OnCommand(UINT, WPARAM, HWND);

	BOOL OnBtnNext();
	BOOL HasNextPage();	

    void OnCheckButtonClicked(UINT /*uCode*/, int nID, HWND hwndCtrl);

	BOOL SaveProfile(BOOL bEnableAuthentication);

protected:
	int GetDlgID(){	return IDD_DIALOG_WIZARD_PROFILE; }
	
	void UpdateWizardController();

private:
	CString m_strEmail;
	CString m_strPassword;
	CString m_strConfirm;
	CString m_strProfileBaseDir;

	static HWND hWndFinish;
	static int m_nStep;

	CWindow m_hWndDialog;
	
	IUOLMessengerProfileManagerPtr	m_pProfileManager;

	CFont m_font;

	CTransparentStatic	m_staticHeader;
	CTransparentStatic	m_staticInfo;
	CTransparentStatic	m_staticEmail;
	CTransparentStatic	m_staticPass;
    CTransparentStatic	m_staticConfirm;
	CTransparentStatic	m_staticSubcribe;
	CTransparentStatic	m_staticNetworks;
};

MAKEAUTOPTR(CWizardProfileDialog);