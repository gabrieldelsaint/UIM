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

#include "imagebuttoncontainer.h"

template <typename T, typename TBase>
class CImageTextButtonContainer :  public CImageButtonContainer<T, TBase > 
{
public:
	void SetCaption(const CString& caption) 
	{
		m_caption = caption;
	}
	
	CString GetCaption() 
	{
		return m_caption;
	}
	
	void SetFont(CFontElementPtr pfont) 
	{
		m_pFont = pfont;
	}

protected:		
	virtual void DrawButton(CDCHandle& dc, CImageButtonBasePtr&	pButton, int x, int y, int cx, int cy, CImageButton::MouseState state);
	virtual int GetNextButtonPosition(int x, CImageButtonBasePtr& pButton);

protected:
	CFontElementPtr m_pFont;	
};


template <typename T, typename TBase>
void CImageTextButtonContainer<T, TBase>::DrawButton(CDCHandle& dc, 
													 CImageButtonBasePtr& pButton, 
													 int x, int y, 
													 int cx, int cy, 
													 CImageButton::MouseState state)
{
	__super::DrawButton(dc, pButton, x, y,
						cx, cy, state);

	CString strCaption = pButton->GetCaption();
	
	if (strCaption.GetLength()) 
	{
		CSize size;
		GetMinSize(size);

		CSize sizeText;
		int nButtonWidth = pButton->GetWidth();

		if (m_pFont.get()) 
		{
			m_pFont->GetTextWidth(dc, strCaption, sizeText);					
		} 
		else 
		{
			dc.GetTextExtent(strCaption, strCaption.GetLength(), &sizeText);
		}

		
		CRect rectText;

		rectText.top = y + cy - sizeText.cy - 3;
		rectText.left = x + (cx - sizeText.cx) / 2;
		rectText.right = rectText.left + sizeText.cx;
		rectText.bottom = rectText.top + sizeText.cy;

		pButton->SetTextRect(rectText);
		
		int nOldMode = dc.SetBkMode(TRANSPARENT);

		if (m_pFont.get()) 
		{
			m_pFont->DrawColoredText(dc, rectText, strCaption, RGB(0,0,0),  DT_END_ELLIPSIS);			
		}
		else 
		{
			dc.DrawText(strCaption, strCaption.GetLength(), rectText, DT_END_ELLIPSIS);
		}
		
		dc.SetBkMode(nOldMode);
	} 	
}

template <typename T, typename TBase>
int CImageTextButtonContainer<T, TBase>::GetNextButtonPosition(int x, CImageButtonBasePtr& pButton)
{		
	return __super::GetNextButtonPosition(x, pButton);	
}