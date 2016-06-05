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
 
#include "StdAfx.h"
#include ".\uimstatusbarctrl.h"

CUIMStatusBarCtrl::CUIMStatusBarCtrl(void) : 
	m_cy(0), 
	m_nStatusBarHorMargin(0),
	m_nStatusBarVerMargin(0)
{
}

CUIMStatusBarCtrl::~CUIMStatusBarCtrl(void)
{
}

void CUIMStatusBarCtrl::SetText(const CString& strText)
{
	m_strText = strText;

	if (IsWindow())
	{
		Invalidate();
	}
}


CString CUIMStatusBarCtrl::GetText() const
{
	return m_strText;
}


LRESULT CUIMStatusBarCtrl::OnNcHitTest(const CPoint& pt)
{
	CPoint ptClient = pt;
	ScreenToClient(&ptClient);

	if (TRUE)
	{
		return HTTRANSPARENT;
	}

	return HTCLIENT;
}

void CUIMStatusBarCtrl::GetMinSize(CSize& size)
{
	size = CSize(0, m_cy);
}

void CUIMStatusBarCtrl::SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	__super::SetParameters(pMapParams, pElementTable);	

	GetParameterValue(m_cy, pMapParams, "Height");	

	try
	{
		CString strFontName;
		GetParameterValue(strFontName, pMapParams, "font");		

		m_pFont = ap_dynamic_cast<CFontElementPtr>(pElementTable->GetElement(strFontName));
		ATLASSERT(m_pFont.get());
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "font");
		// use default system font
		m_pFont = new CFontElement();
	}


	try
	{
		GetParameterValue(m_nStatusBarHorMargin, pMapParams, "StatusBarHorMargin");				
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "StatusBarHorMargin");
	}

	try
	{
		GetParameterValue(m_nStatusBarVerMargin, pMapParams, "StatusBarVerMargin");		
	}	
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "StatusBarVerMargin");
	}	

	try
	{
		CString strColor;
		GetParameterValue(strColor, pMapParams, "SizingGripColor");		

		m_clrSizingGrip.SetColor(strColor);
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "SizingGripColor");
	}

	try
	{
		CString strColor;
		GetParameterValue(strColor, pMapParams, "StatusBarTextColor");		

		m_clrStatusBarText.SetColor(strColor);
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "StatusBarTextColor");
		m_clrStatusBarText = m_pFont->GetColor();
	}	
}

void CUIMStatusBarCtrl::DoPaint(CDCHandle& dc)
{
	__super::DoPaint(dc);

	DrawText(dc);
	DrawSizingGrip(dc);	
}

BOOL CUIMStatusBarCtrl::HitTest(const CPoint& pt, int& nTest) const
{
	CPoint ptClient = pt;
	ScreenToClient(&ptClient);

	CRect rect;
	GetClientRect(&rect);

	int nStatusBarHeight = m_cy;

	CRect rectGripper(CPoint(rect.Width()- nStatusBarHeight, 0), 
					  CSize(nStatusBarHeight, nStatusBarHeight));	


	if (rectGripper.PtInRect(ptClient))
	{
		 nTest = HTBOTTOMRIGHT;
	}

	return TRUE;
}

void CUIMStatusBarCtrl::DrawText(CDCHandle& dc)
{
	CRect rect;
	GetClientRect(&rect);

	CRect rectText = CRect(
						CPoint(m_nStatusBarHorMargin, m_nStatusBarVerMargin), 
						CSize(rect.Width(), m_cy - m_nStatusBarVerMargin));	

	if (m_pFont.get())
	{
		m_pFont->DrawColoredText(dc, rectText, m_strText, m_clrStatusBarText);		
	}
}

void CUIMStatusBarCtrl::DrawSizingGrip(CDCHandle& dc)
{	
	//if (m_nSizeType != SIZE_MAXIMIZED)
	{
		CRect rect;
		GetClientRect(&rect);

		int nStatusBarHeight = m_cy;
		int nStatusBarWidth = rect.Width();

		CPen penLines;
		penLines.CreatePen(PS_SOLID, 2, m_clrSizingGrip);

		HPEN hOldPen = dc.SelectPen(penLines);

		int xBorder = nStatusBarWidth;
		int x = nStatusBarWidth - nStatusBarHeight + 5;
		int y = 5;

		while (x < xBorder)
		{
			dc.MoveTo(x, nStatusBarHeight);
			dc.LineTo(xBorder, y);

			x += 5;
			y += 5;
		}

		dc.SelectPen(hOldPen);
	}
}