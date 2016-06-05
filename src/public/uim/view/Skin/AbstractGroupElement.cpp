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
#include "AbstractGroupElement.h"

#include "../image/Image.h"
#include "../image/ImageBuilder.h"


CAbstractGroupElement::CAbstractGroupElement() : 
m_nHeight(0)
{
	m_pTextFont = new CFontElement();
	m_pDropTargetTextFont = m_pTextFont;
}


CAbstractGroupElement::~CAbstractGroupElement()
{
}


int CAbstractGroupElement::GetHeight() const
{
	return m_nHeight;
}


IUOLMessengerImagePtr CAbstractGroupElement::GetCollapsedImage() const
{
	return m_pImageGroupCollapserCollapsed;
}


IUOLMessengerImagePtr CAbstractGroupElement::GetExpandedImage() const
{
	return m_pImageGroupCollapserExpanded;
}


CFontElementPtr CAbstractGroupElement::GetFont() const
{
	return m_pTextFont;
}


COLORREF CAbstractGroupElement::GetTextColor() const
{
	return m_clrText;
}


CFontElementPtr CAbstractGroupElement::GetDropTargetFont() const
{
	return m_pDropTargetTextFont;
}


COLORREF CAbstractGroupElement::GetDropTargetTextColor() const
{
	return m_clrDropTargetText;
}


void CAbstractGroupElement::SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{	
	GetParameterValue(m_nHeight, pMapParams, "Height");

	CString strImage;
	GetParameterValue(strImage, pMapParams, "collapsedImage");

	m_pImageGroupCollapserCollapsed = UOLMessengerImage::CImageBuilder::LoadImage(strImage);
	ATLASSERT(m_pImageGroupCollapserCollapsed.get());


	GetParameterValue(strImage, pMapParams, "expandedImage");

	m_pImageGroupCollapserExpanded = UOLMessengerImage::CImageBuilder::LoadImage(strImage);
	ATLASSERT(m_pImageGroupCollapserExpanded.get());

	try
	{
		CString strFontName;
		GetParameterValue(strFontName, pMapParams, "font");

		m_pTextFont = ap_dynamic_cast<CFontElementPtr>(pElementTable->GetElement(strFontName));
		ATLASSERT(m_pTextFont.get());
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "font");
		// use default system font
		m_pTextFont = new CFontElement();
	}

	try
	{
		CString strColor;
		GetParameterValue(strColor, pMapParams, "TextColor");		

		m_clrText.SetColor(strColor);
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "TextColor");
		// Use font color
		m_clrText = m_pTextFont->GetColor();
	}

	try
	{
		CString strFontName;
		GetParameterValue(strFontName, pMapParams, "DropTargetFont");

		m_pDropTargetTextFont = ap_dynamic_cast<CFontElementPtr>(pElementTable->GetElement(strFontName));
		ATLASSERT(m_pDropTargetTextFont.get());
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "DropTargetFont");
		// use default system font
		m_pDropTargetTextFont = m_pTextFont;
	}

	try
	{
		CString strColor;
		GetParameterValue(strColor, pMapParams, "DropTargetTextColor");		

		m_clrDropTargetText.SetColor(strColor);
	}
	catch(const CSkinException&)
	{
		ATLTRACE(_T("%s - %s\n"), __FUNCTION__, "DropTargetTextColor");
		// Use font color
		m_clrDropTargetText = m_pDropTargetTextFont->GetColor();
	}
}
