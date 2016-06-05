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

#include <interfaces/IUOLMessengerPluginCustomPanel.h>
#include "SampleTooltipProvider.h"


class CSamplePanel : 
	public IUOLMessengerPluginCustomPanel,
	public CWindowImpl<CSamplePanel>
{
public:
	DECLARE_WND_CLASS("SamplePanel");

	CSamplePanel(const CString& strPanelName, const CString& strPluginInternalName);

	// IUOLMessengerPluginCustomPanel implementation
	CString GetPanelName() const;
	CString GetPluginInternalName() const;
	void GetMinSize(CSize& size);
	HWND CreatePanel(HWND hWndParent, const CRect& rectPanel, DWORD dwWindowStyle = WS_CHILDWINDOW);
	void DestroyPanel(HWND hWndPanel);
	IUOLMessengerTooltipProviderPtr GetTooltipProvider() const;

protected:
	enum
	{
		ID_BUTTON_ENABLE_NOTIFY_POPUP = 0x2001,
		ID_BUTTON_DISABLE_NOTIFY_POPUP,
	};

	static int TIMER_SHOW_NOTIFY_POPUP;

	BEGIN_MSG_MAP(CSamplePanel)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_SIZE(OnSize)
		MSG_WM_TIMER(OnTimer)
		COMMAND_RANGE_HANDLER_EX(ID_BUTTON_ENABLE_NOTIFY_POPUP, ID_BUTTON_DISABLE_NOTIFY_POPUP, OnClickedButtonTest)
	END_MSG_MAP()

	LRESULT OnCreate(LPCREATESTRUCT lpCs);
	void OnDestroy();
	void OnSize(UINT nType, const CSize& size);
	void OnTimer(UINT nTimerId, TIMERPROC timerProc);
	void OnClickedButtonTest(UINT /*uCode*/, int /*nID*/, HWND /*hwndCtrl*/);

private:
	CString		m_strPanelName;
	CString		m_strPluginInternalName;

	IUOLMessengerImagePtr	m_pIcon;

	CSampleTooltipProviderPtr m_pTooltipProvider;
	WTL::CButton	m_btnTest1;
	WTL::CButton	m_btnTest2;

	UINT_PTR		m_nTimerNotifyPopUp;
};
