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
#include "AppCloseAlertElement.h"


CAppCloseAlertElement::CAppCloseAlertElement()
{
}


CAppCloseAlertElement::~CAppCloseAlertElement()
{
}


CStaticIconElementPtr CAppCloseAlertElement::GetWindowStaticIcon()
{
	return m_pStaticIconWindow;
}


CStaticIconElementPtr CAppCloseAlertElement::GetXPTraySampleStaticIcon()
{
	return m_pStaticIconXPTraySample;
}


CStaticIconElementPtr CAppCloseAlertElement::Get2kTraySampleStaticIcon()
{
	return m_pStaticIcon2kTraySample;
}


CStaticIconElementPtr CAppCloseAlertElement::GetVistaTraySampleStaticIcon()
{
	return m_pStaticIconVistaTraySample;
}


CString CAppCloseAlertElement::GetName() const
{
	return _T("__AppCloseAlertInstance");
}


void CAppCloseAlertElement::SetParameters(CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	__super::SetParameters(pMapParams, pElementTable);

	m_pStaticIconWindow = GetStaticIconElement(_T("alerticon"), pMapParams, pElementTable);
	m_pStaticIconXPTraySample = GetStaticIconElement(_T("traysamplexp"), pMapParams, pElementTable);;
	m_pStaticIcon2kTraySample = GetStaticIconElement(_T("traysample2k"), pMapParams, pElementTable);;
	m_pStaticIconVistaTraySample = GetStaticIconElement(_T("traysamplevista"), pMapParams, pElementTable);;
}


CStaticIconElementPtr CAppCloseAlertElement::GetStaticIconElement(const CString& strParameterName, CString2StringMapPtr& pMapParams, IElementTable* pElementTable)
{
	CStaticIconElementPtr pStaticIconElement;

	try
	{
		CString strStaticIcon;
		GetParameterValue(strStaticIcon, pMapParams, strParameterName);

		IElementPtr pElement = pElementTable->GetElement(strStaticIcon);

		if (pElement)
		{
			pStaticIconElement = ap_dynamic_cast<CStaticIconElementPtr>(pElement);
		}
	}
	catch (const CSkinException&)
	{
	}

	return pStaticIconElement;
}

