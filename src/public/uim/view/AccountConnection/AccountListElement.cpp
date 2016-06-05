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
#include "AccountListElement.h"

#include "../skin/SolidBackgroundElement.h"


CAccountListElement::CAccountListElement()
{
}


CAccountListElement::~CAccountListElement()
{
}


CBackgroundElementPtr CAccountListElement::GetNormalBackground1()
{
	return m_pBackgroundNormal1;
}


CBackgroundElementPtr CAccountListElement::GetNormalBackground2()
{
	return m_pBackgroundNormal2;
}


CBackgroundElementPtr CAccountListElement::GetSelectedBackground()
{
	return m_pBackgroundSelected;
}


CBackgroundElementPtr CAccountListElement::GetFocusBackground()
{
	return m_pBackgroundFocus;
}


CFontElementPtr CAccountListElement::GetNormalFont()
{
	return m_pFontNormal;
}


CFontElementPtr CAccountListElement::GetSelectedFont()
{
	return m_pFontSelected;
}


CString CAccountListElement::GetName() const
{
	return _T("__AccountListElementInstance");
}


void CAccountListElement::SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	__super::SetParameters(pMapParams, pElementTable);

	// itembackground1
	m_pBackgroundNormal1 = GetBackgroundElement(_T("itembackground1"), pMapParams, pElementTable);

	// itembackground2
	m_pBackgroundNormal2 = GetBackgroundElement(_T("itembackground2"), pMapParams, pElementTable );

	// selectedbackground
	m_pBackgroundSelected = GetBackgroundElement(_T("selectedbackground"), pMapParams, pElementTable);
	
	// focusbackground
	m_pBackgroundFocus = GetBackgroundElement(_T("focusbackground"), pMapParams, pElementTable);
	
	// font
	m_pFontNormal = GetFontElement(_T("font"), pMapParams, pElementTable);

	// fontselected
	m_pFontSelected = GetFontElement(_T("fontselected"), pMapParams, pElementTable);
}


CBackgroundElementPtr CAccountListElement::GetBackgroundElement(const CString& strParameterName, CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	CBackgroundElementPtr pBackgroundElement;

	try
	{
		CString strBackground;
		GetParameterValue(strBackground, pMapParams, strParameterName);

		IElementPtr pElement = pElementTable->GetElement(strBackground);

		if (pElement)
		{
			pBackgroundElement = ap_dynamic_cast<CBackgroundElementPtr>(pElement);
		}
	}
	catch (const CSkinException&)
	{
		pBackgroundElement = new CSolidBackgroundElement(RGB(255, 255, 255));
	}

	return pBackgroundElement;
}


CFontElementPtr CAccountListElement::GetFontElement(const CString& strParameterName, CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	CFontElementPtr pFontElement;

	try
	{
		CString strFontName;
		GetParameterValue(strFontName, pMapParams, strParameterName);

		pFontElement = ap_dynamic_cast<CFontElementPtr>(pElementTable->GetElement(strFontName));
	}
	catch (const CSkinException&)
	{
		// use default system font
		pFontElement = new CFontElement();
	}

	return pFontElement;
}
