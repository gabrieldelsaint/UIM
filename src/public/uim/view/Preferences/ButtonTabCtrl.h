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

#include "TabItem.h"
#include "../skin/windowelement.h"
#include "../Skin/COLORREF.h"
#include "../dummywindow.h"
#include "../skin/FontElement.h"

class CButtonTabCtrl;
typedef CWindowElement<CButtonTabCtrl, CDummyWindow<CWindowImpl<CButtonTabCtrl> > > CButtonTabCtrlBase;

class CButtonTabCtrl : public CButtonTabCtrlBase
{
public:
	CButtonTabCtrl();
	virtual ~CButtonTabCtrl();

	int GetControlHeight() const;
	
	void InsertItem(int nIndex, const CString& strText, IUOLMessengerImagePtr pImage, BOOL bDrawTransparent);
	void RemoveItem(int nIndex);
	void RemoveAll();

	int GetItemCount();

	int GetCurSel();
	void SetCurSel(int nIndex);

protected:
	BEGIN_MSG_MAP(CButtonTabCtrl)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		CHAIN_MSG_MAP(CButtonTabCtrlBase)
	END_MSG_MAP()

	// WindowElement methods
	virtual void UpdateLayout(BOOL bResizeBars = TRUE);
	virtual void DoPaint(CDCHandle& dc);
	virtual void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
	CString GetName() const;

	void OnLButtonDown(UINT nFlags, CPoint& ptClick);


private:
	void UpdateImageAreaHeight();

	void DrawTabItems(CDCHandle& dc);

	int GetTabItem(CPoint& pt);

	int GetTextAreaHeight() const;

protected:
	CFontElementPtr	m_pFont;
	CCOLORREF	m_clrSelectionBackground;
	int	m_nHorizontalSpacement;
	int m_nVerticalSpacement;
	int m_nImageAreaHeight;

	int	m_nSelectedItem;

private:
	CAtlArray<CTabItemPtr>	m_arTabItems;
};
MAKEAUTOPTR(CButtonTabCtrl);