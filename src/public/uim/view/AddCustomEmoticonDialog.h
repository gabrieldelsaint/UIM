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
#include "UOLFoneMultiStateButton.h"

#include <interfaces/IUOLMessengerAccount.h>
#include <interfaces/IUOLMessengerCustomEmoticon.h>
#include <interfaces/IUOLMessengerEmoticonSettings.h>
#include <interfaces/IUOLMessengerEmoticon.h>
#include <interfaces/IUOLMessengerAddCustomEmoticonWindow.h>

#include "./Preferences/PictureExWnd.h"


class CAddCustomEmoticonDialog : 
		public CMainDialog,
		public CWinDataExchange<CAddCustomEmoticonDialog>,
		public IUOLMessengerAddCustomEmoticonWindow
{
public:
	
	CAddCustomEmoticonDialog();
	virtual ~CAddCustomEmoticonDialog(void);
	
	void InitializeAddCustomEmoticonInfo(IUOLMessengerAccountPtr pAccount, 
			const CString& strAddingEmoticonShortcut, const CString& strAddingEmoticonFileName, 
			OperationModeId nOperationModeId, 
			IEmoticonChangingInfoFinder* pEmoticonChangingInfoFinder);
	
    void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
	
protected:
	
	/*
	enum
	{
		ID_BUTTON_OPEN_IMAGE = 0x2514,
	};
	*/
	
	BEGIN_MSG_MAP(CAddCustomEmoticonDialog)	
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		COMMAND_ID_HANDLER_EX(IDOK, OnBnClickedButtonOK)
		COMMAND_ID_HANDLER_EX(IDCANCEL, OnBnClickedButtonCancel)
		COMMAND_ID_HANDLER_EX(ID_BUTTON_OPEN_IMAGE, OnBnClickedOpenImage)
        CHAIN_MSG_MAP(CMainDialog)
        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	
	BEGIN_DDX_MAP(CAddCustomEmoticonDialog)
		DDX_TEXT(IDC_EDIT_SHORTCUT, m_strAddingEmoticonShortcut)
	END_DDX_MAP()
	
	virtual LRESULT OnInitDialog(HWND hwnd, LPARAM lParam);
	virtual LRESULT OnDestroy();
	
	void OnBnClickedButtonOK(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	void OnBnClickedButtonCancel(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	void OnBnClickedOpenImage(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);
	
	// Interface IUOLMessengerAddCustomEmoticonWindow.
	virtual INT_PTR ShowModal();
	virtual CString GetCustomEmoticonShortcut();
	virtual CString GetCustomEmoticonFileName();
	
private:
	
	BOOL IsValidData();
	
private:
	
	IUOLMessengerAccountPtr		m_pAccount;
	CString						m_strAddingEmoticonShortcut;
	CString						m_strAddingEmoticonFileName;
	
	CPictureExWnd				m_customEmoticonDrawer;
	
	CTransparentStatic			m_userTransparencyApplier;
	CTransparentStatic			m_shortcutTransparencyApplier;
	
	CCOLORREF					m_cBackgroundColor;
	
	CString						m_strOpenFileButtomImage;

	WTL::CEdit					m_wndEditShortcut;
	WTL::CButton				m_openFileButton;
	//CUOLFoneMultiStateButton	m_openFileMultiStateButton;
	CRect						m_emoticonRect;
	
	OperationModeId				m_nOperationModeId;
	
	IUOLMessengerEmoticonSettings3Ptr m_pEmoticonSettings3;
	
	IUOLMessengerEmoticonPtr	m_pChangingEmoticon;
	
	IEmoticonChangingInfoFinder*	m_pEmoticonChangingInfoFinder;
};

MAKEAUTOPTR(CAddCustomEmoticonDialog);

