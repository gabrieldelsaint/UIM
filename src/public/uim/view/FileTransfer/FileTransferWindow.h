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

#include <interfaces/IUOLMessengerRemoteContactList.h>
#include <interfaces/IUOLMessengerSettingsManager.h>
#include <interfaces/IUOLMessengerGeneralSettings.h>
#include <interfaces/IUOLMessengerSettingsEventListener.h>

#include "../DummyWindow.h"
#include "../MainFrm.h"
#include "../UOLToolbar.h"
#include "FileTransferListCtrl.h"
#include "../../controller/FileTransferList.h"

class CFileTransferWindow;
typedef CWindowElement<CFileTransferWindow, CDummyWindow<CWindowImpl<CFileTransferWindow> > > CFileTransferWindowBase;


class CFileTransferWindow : public CFileTransferWindowBase,
							public CUOLMessengerImageButtonEventListener2, 
							public IUOLMessengerSettingsEventListener
{
public:
	DECLARE_WND_CLASS_EX("FileTransferWindow", CS_DBLCLKS, COLOR_WINDOW);

	CFileTransferWindow(CMainFrame* pParentFrame);
	virtual ~CFileTransferWindow();

protected:
	BEGIN_MSG_MAP(CFileTransferWindow)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		CHAIN_MSG_MAP(CFileTransferWindowBase)
	END_MSG_MAP()

	LRESULT OnCreate(LPCREATESTRUCT lpCreatestruct);
	void OnDestroy();
	
	virtual void UpdateLayout(BOOL bResizeBars = TRUE);
	virtual void GetMinSize(CSize& size);

	void CreateToolbar();
	void OpenFolder();
	void UpdateToolbarButtons();

	// CImageButtonEventListener methods.
	virtual void OnLButtonUp(IUOLMessengerImageButton* pButton, const CPoint &ptClick);
	
	// IUOLMessengerSettingsEventListener methods.
	virtual void OnSettingChanged(IUOLMessengerSettingsEventSource* pSource, UINT nSettingId);

private:
	CMainFrame*							m_pParentFrame;
	IUOLMessengerFileTransferListPtr	m_pFileTransferList;
	CFileTransferListCtrlPtr			m_pFileTransferListCtrl;
	CUOLToolBarPtr			            m_pToolbar;
	
	IUOLMessengerMessageSettings3Ptr	m_pMessageSettings3;
}; 

MAKEAUTOPTR(CFileTransferWindow);
