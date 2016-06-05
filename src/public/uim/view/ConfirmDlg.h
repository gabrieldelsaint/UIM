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

class CConfirmDlg : public CMainDialog,
					public CWinDataExchange<CConfirmDlg>,
					public CTransparentControls<CConfirmDlg>
{
public:
	CConfirmDlg(void);
	virtual ~CConfirmDlg(void);

	BOOL DoModal();

protected:	
	BEGIN_MSG_MAP(CConfirmDlg)		
		CHAIN_MSG_MAP(CTransparentControls<CConfirmDlg>)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		COMMAND_RANGE_HANDLER(IDOK, IDNO, OnCloseCmd)
		CHAIN_MSG_MAP(CMainDialog)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CConfirmDlg)
		DDX_TEXT(IDC_STATIC_CONFIRM_TEXT, m_strText);
		DDX_CHECK(IDC_CHECK_CONFIRM, m_bCheck)
		DDX_TEXT(IDC_CHECK_CONFIRM, m_strCheckText);
		DDX_TEXT(IDOK, m_strOKButton);
		DDX_TEXT(IDCANCEL, m_strCancelButton);
	END_DDX_MAP()

	LRESULT OnInitDialog(HWND, LPARAM);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void OnDestroy();

public:	
	CString		m_strText;
	CString		m_strCaption;
	CString		m_strCheckText;
	CString		m_strOKButton;
	CString		m_strCancelButton;

	BOOL		m_bCheck;

	CTransparentStatic	m_labelTransparencyApplier;
};
MAKEAUTOPTR(CConfirmDlg);
