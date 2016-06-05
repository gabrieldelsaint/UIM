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
#include ".\bitmapbackgroundelement.h"
#include "../image/Image.h"
#include "../image/ImageBuilder.h"

CBitmapBackgroundElement::CBitmapBackgroundElement(void)
{
	m_pImage = NULL;
}

CBitmapBackgroundElement::~CBitmapBackgroundElement(void)
{
	if (m_pImage)
	{
		delete m_pImage;
	}
}

void CBitmapBackgroundElement::SetImage(IUOLMessengerImagePtr& pImageBackground)
{
	m_pImageBackground = pImageBackground;
}

HBITMAP CBitmapBackgroundElement::GetBitmap()
{
	if (m_pImage)
	{
		HBITMAP hBitmap(*m_pImage);
	
		return hBitmap;
	}
	else
	{
		return NULL;
	}
}

void CBitmapBackgroundElement::SetDrawStrategy(IUOLMessengerImageDrawStrategyPtr& pDrawStrategy)
{
	m_pDrawStrategy = pDrawStrategy;
}

void CBitmapBackgroundElement::SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	__super::SetParameters(pMapParams, pElementTable);

	SetImageParameter(pMapParams, pElementTable);
	SetDrawStrategy(pMapParams, pElementTable);
}

void CBitmapBackgroundElement::Draw(CDCHandle& dc, const CRect& rect)
{
	ATLASSERT(m_pImageBackground.get());

	m_pImageBackground->Draw(dc, rect.left, rect.top, rect.Width(), rect.Height(), m_pDrawStrategy);
}

void CBitmapBackgroundElement::SetImageParameter(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	GetParameterValue(m_strImage, pMapParams, "image");
	
	m_pImageBackground = UOLMessengerImage::CImageBuilder::LoadImage(m_strImage);
	ATLASSERT(m_pImageBackground.get());

	// Also load image as CImage to get HBITMAP, useful in some special cases like transparent checkboxes
	m_pImage = UOLMessengerImage::CImageBuilder::LoadImage2(m_strImage); 	
	ATLASSERT(m_pImage);
}

void CBitmapBackgroundElement::SetDrawStrategy(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	CString strMode;
	GetParameterValue(strMode, pMapParams, "mode");

	if (0 == strMode.CompareNoCase("tile"))
	{
		m_pDrawStrategy = new UOLMessengerImage::CPatternStrategy();
	}
	else if (0 == strMode.CompareNoCase("normal"))
	{
		m_pDrawStrategy = new UOLMessengerImage::CDrawOpaqueStrategy();
	}
	else if (0 == strMode.CompareNoCase("stretch"))
	{
		m_pDrawStrategy = new UOLMessengerImage::CDrawStretchOpaqueStrategy();
	}
	else
	{
		ATLASSERT(FALSE);
	}

}