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

#include "Skin/BitmapBackgroundElement.h"

template<class T>
class CTransparentControls
{
public:

	BEGIN_MSG_MAP(CTransparentControls<T>)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColor)
	END_MSG_MAP()

protected:

	inline CTransparentControls()
	{
		m_pT = (T*)this;
		m_pBitmapBackground = NULL;
	}


	inline ~CTransparentControls()
	{
		m_BrushesList.RemoveAll();
	}


	inline void SetBitmapBackground(CBackgroundElementPtr pBackground)
	{
		CBitmapBackgroundElementPtr pBitmapBackground;
		pBitmapBackground = ap_dynamic_cast<CBitmapBackgroundElementPtr>(pBackground);
		
		if (pBitmapBackground)
		{
			m_pBitmapBackground = pBitmapBackground;
		}
	}


	inline void RegisterControl(HWND hwndCtrl)
	{
		HBRUSH hBrush = NULL;
		m_BrushesList.AddTail(hwndCtrl);
	}


	inline void SetParentWindow(HWND hwndParent)
	{
		m_hParentWindow = hwndParent;
	}


	inline LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HWND hwndCtrl = (HWND)(lParam);
		HDC hDC = (HDC)(wParam);

		ATLASSERT(m_hParentWindow != NULL);
		ATLASSERT(hwndCtrl != NULL);
		ATLASSERT(m_pBitmapBackground != NULL);

		HBRUSH hBrush = NULL;

		POSITION pos = m_BrushesList.Find(hwndCtrl);
		if (pos)
		{
			CComCritSecLock<CComAutoCriticalSection> lock(m_cs);
			
			CRect ctrlRect;
			::GetWindowRect(hwndCtrl, &ctrlRect);
			
			CPoint ctrlPoint(ctrlRect.left, ctrlRect.top);
			ScreenToClient(m_hParentWindow, &ctrlPoint);

			if ((hBrush == NULL) && (m_pBitmapBackground != NULL))
			{
				hBrush = ::CreatePatternBrush(m_pBitmapBackground->GetBitmap());
			}			

			// Adjust the position of the brush for this control
			::SetBrushOrgEx(hDC, -ctrlPoint.x, -ctrlPoint.y, NULL);
			
			::SetBkMode(hDC, TRANSPARENT);
		}

		bHandled = TRUE;

		return (LRESULT) hBrush;
	}

private:
	typedef CAtlList<HWND> CBrushList;

	CComAutoCriticalSection m_cs;

	T*				m_pT;
	CBrushList		m_BrushesList;
	HWND			m_hParentWindow;
	CBitmapBackgroundElementPtr m_pBitmapBackground;
};

