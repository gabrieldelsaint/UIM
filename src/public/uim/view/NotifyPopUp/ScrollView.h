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

#include "NotifyPopUpHyperLink.h"
#include "../skin/WindowElement.h"
#include "../skin/BorderElement.h"
#include "../skin/FontElement.h"
#include "../skin/COLORREF.h"
#include <interfaces/IUOLMessengerImage.h>


class CScrollView;
typedef CWindowElement<CScrollView, CScrollWindowImpl<CScrollView> > _CScrollViewBase;

class CScrollView: public _CScrollViewBase
{
public:

private:

	CAtlArray<CNotifyPopUpStaticTextPtr>	m_statics;
	CAtlArray<CNotifyPopUpHyperLinkPtr>		m_links;
	CAtlArray<CString>						m_titles;

	CScrollBar								m_scrollBar;
	CFont									m_staticFont;

	CBorderElementPtr		m_pBorderInternal;
	CFontElementPtr 		m_pFontLink;
	CCOLORREF				m_clrLink;
	CCOLORREF				m_clrVisitedLink;

	IUOLMessengerImagePtr	m_pMessageIcon;
	IUOLMessengerImagePtr	m_pWindowIcon;
	IUOLMessengerImageDrawStrategyPtr	m_pMessageIconDrawStrategy;
	IUOLMessengerImageDrawStrategyPtr	m_pWindowIconDrawStrategy;

public:
	BEGIN_MSG_MAP(CScrollView)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_CTLCOLORSTATIC(OnCtlColor)
		MSG_WM_DESTROY(OnDestroy)

		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnMouseDown)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnMouseDown)

		MESSAGE_HANDLER(CNotifyPopUpHyperLink::WM_USER_HYPERLINKLBUTTONDOWN, OnHyperlinkButtonDown)
		MESSAGE_HANDLER(CNotifyPopUpHyperLink::WM_USER_HYPERLINKRBUTTONDOWN, OnHyperlinkButtonDown)

		CHAIN_MSG_MAP(_CScrollViewBase)
	END_MSG_MAP()

	CScrollView();
	~CScrollView();

	void AddLink(const CString& strTitle, const CString& strUrl);
	
	void SetMessageIcon(IUOLMessengerImagePtr pMessageIcon);
	void SetWindowIcon(IUOLMessengerImagePtr pWindowIcon);
	void SetMessageIconDrawStrategy(IUOLMessengerImageDrawStrategyPtr pMessageIconDrawStrategy);
	void SetWindowIconDrawStrategy(IUOLMessengerImageDrawStrategyPtr pWindowIconDrawStrategy);

	LRESULT OnCreate(LPCREATESTRUCT lpcs);
	HBRUSH OnCtlColor(HDC hdc, HWND hWnd);
	void DoPaint(CDCHandle dc);
	LRESULT OnMouseDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHyperlinkButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnDestroy();

	//void DoScroll(int nType, int nScrollCode, int& cxyOffset, int cxySizeAll, int cxySizePage, int cxySizeLine);

	CString GetName() const;
	void SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable);
};