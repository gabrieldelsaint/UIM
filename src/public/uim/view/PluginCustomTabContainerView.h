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

#include "../controller/PluginCustomTabContainer.h"
#include "Tooltip/PluginTooltip.h"
#include "TabView.h"


class CPluginCustomTabContainerView : 
	public CWindowImpl<CPluginCustomTabContainerView>,
	public CPluginCustomTabContainerObserver
{
public:
	CPluginCustomTabContainerView();
	virtual ~CPluginCustomTabContainerView();

	DECLARE_WND_CLASS(_T("PluginCustomTabContainerView"))

	void Init(IUOLMessengerPluginCustomTabContainerPtr pTabContainer, CTabViewPtr pTabViewCtrl);
	void Finalize();

	virtual void GetMinSize(CSize& size);
	
	UINT GetTabsCount();
	void HideAllTabs();

protected:
	BEGIN_MSG_MAP_EX(CPluginCustomTabContainerView)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_SIZE(OnSize)
		MSG_WM_ERASEBKGND(OnEraseBackground)
		MSG_WM_SETCURSOR(OnSetCursor)
	ALT_MSG_MAP(1)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
	END_MSG_MAP()

	LRESULT OnCreate(LPCREATESTRUCT lpCs);
	void OnDestroy();
	void OnSize(UINT nType, const CSize& size);
	LRESULT OnEraseBackground(HDC hDc);
	LRESULT OnSetCursor(HWND hWnd, UINT nHitTest, UINT uMsg);
	void OnMouseHover(UINT nFlags, CPoint pt);
	void OnMouseLeave();

	virtual void OnAddTab(IUOLMessengerPluginCustomTabPtr pTab);
	virtual void OnRemoveTab(IUOLMessengerPluginCustomTabPtr pTab);
	virtual void OnShowTab(IUOLMessengerPluginCustomTabPtr pTab);

private:
	void CreateTabs();
	void DestroyTabs();
	CString GetTabId(IUOLMessengerPluginCustomTabPtr pTab);

	void OnSizeImpl(const CSize& size);
	void TrackMouseMove(HWND hWndChild);

private:
	struct TabInfo
	{
		IUOLMessengerPluginCustomTabPtr pTab;
		HWND hWndTab;
	};

	typedef CAtlMap<HWND, TabInfo*> CTabMap;

	CAtlList<TabInfo*>	m_listTabs;
	CTabMap				m_mapTabs;
	CPluginCustomTabContainerPtr	m_pTabContainer;

	TabInfo*	m_pTooltipTabInfo;
	BOOL		m_bHoverOn;
	CContainedWindow		m_wndTrackingWindow;
	CPluginTooltipPtr		m_pPluginTooltip;
	//CUOLToolBarPtr			m_pUolToolbarTab;
	CTabViewPtr				m_pTabViewCtrl;
};

MAKEAUTOPTR(CPluginCustomTabContainerView);