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
#include "../skin/FontElement.h"
#include "../../model/PluginInfo.h"
#include "../../controller/UOLMessengerPluginManager.h"
#include "../PluginList/PluginListCtrl.h"


class CPluginsPropPage :
	public CPreferencesPropPage,
	public CPluginInfoListObserver
{
public:
	CPluginsPropPage(void);
	virtual ~CPluginsPropPage(void);

	virtual void OnApply();

	virtual CString GetInternalName() const
	{
		return "__PluginsPropPage";
	}

	// CPluginInfoListObserver
	virtual void OnPluginInfoListChanged();

protected:
	void PopulatePluginList();

	BEGIN_MSG_MAP(CPluginsPropPage)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_PAINT(OnPaint)
		MESSAGE_HANDLER_EX(WM_USER_PREFS_CHANGED, OnPrefsChanged);		
		CHAIN_MSG_MAP(CPreferencesPropPage)
	END_MSG_MAP()
	
	LRESULT OnInitDialog(HWND, LPARAM);
	LRESULT OnCtlColor(HDC hdc, HWND hwnd);	
	void OnDestroy();
	void OnPaint(HDC hdc);
	LRESULT OnPrefsChanged(UINT uMsg, WPARAM wParam, LPARAM lParam);


	enum
	{
		HEADER_HEIGHT = 16,
		FOOTER_HEIGHT = 24,
		ACTIVE_COLUMN_WIDTH = 30,
		DESCRIPTION_COLUMN_WIDTH = 30,
		BORDER_SIZE = 1,
	};
	
private:
	void PaintHeader(CDCHandle& dc, const CRect& rect);

protected:
	CFontElementPtr		m_pFontHeader;
	COLORREF			m_clrBorder;
	COLORREF			m_clrHeader;

	CPluginListCtrlPtr	m_pPluginListCtrl;
};

MAKEAUTOPTR(CPluginsPropPage);

