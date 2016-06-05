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


#include "stdafx.h"
#include "ListSplitPanel.h"

#include "../controller/UIMApplication.h"


CListSplitPanel::CListSplitPanel() :
m_nSplitterHeight(0),
m_bSplitterPositioned(FALSE),
m_nBottomPanelHeight(-1)
{
}


CListSplitPanel::~CListSplitPanel()
{
}



CString CListSplitPanel::GetName() const
{
	return _T("__ListSplitPanelInstance");
}


void CListSplitPanel::SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	__super::SetParameters(pMapParams, pElementTable);

	try
	{
		GetParameterValue(m_nSplitterHeight, pMapParams, "SplitterHeight");
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "SplitterHeight");
		m_nSplitterHeight = 1;
	}

	try
	{
		CString strFileName;
		GetParameterValue(strFileName, pMapParams, "CenterImage");
		m_pCenterImage = UOLMessengerImage::CImageBuilder::LoadImage(strFileName);
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "CenterImage");
	}	
}


void CListSplitPanel::DoPaint(CDCHandle& dc)
{
	if (m_nSinglePane == SPLIT_PANE_NONE && m_xySplitterPos == -1)
	{
		SetSplitterPos();
	}

	DrawSplitterBar(dc);
}


void CListSplitPanel::UpdateLayout()
{
	SetSplitterRect();

	if (!m_bSplitterPositioned)
	{
		CRect rect;
		GetClientRect(&rect);

		if (rect.Height() > 0)
		{
			m_bSplitterPositioned = TRUE;

			int nPos = CUIMApplication::GetApplication()->GetSettingsManager()->GetGeneralSettings()->GetListSplitterPosition();
			
			if (-1 == nPos)
			{
				nPos = GetDefaultSplitterPosition();
			}

			SetSplitterPos(nPos);
		}
	}
}


LRESULT CListSplitPanel::OnCreate(LPCREATESTRUCT /*lpcs*/)
{
	m_cxySplitBar = m_nSplitterHeight;
	m_cxyBarEdge = 0;

	m_nProportionalPos = 0;
	m_bUpdateProportionalPos = FALSE;

	return 0L;
}


void CListSplitPanel::OnDestroy()
{
	DWORD dwSplitterPos = GetSplitterPos();

	CUIMApplication::GetApplication()->GetSettingsManager()->GetGeneralSettings()->SetListSplitterPosition(dwSplitterPos);
}


void CListSplitPanel::OnLButtonDblClick(UINT nFlags, CPoint& ptClick)
{
	DWORD dwSplitterPos = GetSplitterPos();

	ATLTRACE(_T("%s - Splitter position=%d\n"), __FUNCTION__, dwSplitterPos);

	int nMaxPos = m_rcSplitter.bottom - m_cxySplitBar - m_cxyBarEdge;

	if (0 == (nMaxPos - dwSplitterPos))
	{
		if (m_nBottomPanelHeight != -1)
		{
			ATLTRACE(_T("Restore splitter position\n"));

			SetSplitterPos(nMaxPos - m_nBottomPanelHeight);
		}
		else
		{
			ATLTRACE(_T("Default splitter position\n"));

			SetSplitterPos(GetDefaultSplitterPosition());
		}
	}
	else
	{
		ATLTRACE(_T("Save splitter position\n"));

		m_nBottomPanelHeight = nMaxPos - dwSplitterPos;

		SetSplitterPos(nMaxPos);
	}

	//SetMsgHandled(FALSE);
}


void CListSplitPanel::DrawSplitterBar(CDCHandle& dc)
{
	CRect rect;
	if (GetSplitterBarRect(&rect))
	{
		if ((m_pActiveBackground != NULL) && (m_pCenterImage != NULL))
		{
			m_pActiveBackground->Draw(dc, rect);

			int x = (rect.Width() - m_pCenterImage->GetWidth()) / 2;
			int cx = m_pCenterImage->GetWidth();
			int y = rect.top;
			int cy = m_pCenterImage->GetHeight();
			
			IUOLMessengerImageDrawStrategyPtr pStrategy = new UOLMessengerImage::CDrawOpaqueStrategy();

			m_pCenterImage->Draw(dc, x, y, cx, cy, pStrategy);
		}
		else
		{
			__super::DrawSplitterBar(dc);
		}
	}
}


int CListSplitPanel::GetDefaultSplitterPosition()
{
	CRect rect;
	GetClientRect(&rect);

	int nPos = rect.Height();

	const int DOWN_PANEL_HEIGHT = 70;

	if (nPos > (2 * DOWN_PANEL_HEIGHT))
	{
		nPos = nPos - DOWN_PANEL_HEIGHT;
	}
	else
	{
		nPos = nPos / 2;
	}

	return nPos;
}