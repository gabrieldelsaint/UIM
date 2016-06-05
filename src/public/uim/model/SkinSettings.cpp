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

#include "SkinSettings.h"
#include "SettingsTraits.h"

#include "SkinAttributes.h"

CSkinSettings::CSkinSettings()
{
	InitTagProcessMap();
}

CSkinSettings::~CSkinSettings()
{
}

void CSkinSettings::InitTagProcessMap()
{
	init_helper ih[] = 
	{	
		{"Skin", NEW_SETTINGS_CALLBACK(Skin, this)},
		{"Selected", NEW_SETTINGS_CALLBACK(Selected, this)},
	};

	int nSize = sizeof(ih) / sizeof(ih[0]);

	for (int nInd = 0; nInd < nSize; nInd++)
	{
		ms_tagProcess[ih[nInd].str]= ih[nInd].pCallback;
	}
}

void CSkinSettings::Load(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Load(pNode, ms_tagProcess, this);
}

void CSkinSettings::Save(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Save(pNode, ms_tagProcess, this);
}

void CSkinSettings::GetSkinList(CSkinList& listSkin)
{
	for (POSITION p = m_mapSkin.GetStartPosition(); p;)
	{
		listSkin.AddHead(m_mapSkin.GetKeyAt(p));
		m_mapSkin.GetNext(p);
	}
}

BOOL CSkinSettings::GetSkinPath(const CString& strName, CString& strPath)
{
	CSkinMap::CPair* pPair = m_mapSkin.Lookup(strName);

	if (pPair != NULL)
	{
		strPath = pPair->m_value;
		return TRUE;
	}

	return FALSE;
}

CString CSkinSettings::GetSelected()
{
	return this->m_strSelected;
}

void CSkinSettings::SetSelected(const CString& strSelected)
{
	this->m_strSelected = strSelected;
}

IMPLEMENT_SETTINGS_CALLBACK(CSkinSettings, Skin)
{
	CSkinAttributesPtr pSkinAttributes;

	if (bSave)
	{
		for (POSITION pos = m_pThis->m_mapSkin.GetStartPosition(); pos;)
		{
			CSkinMap::CPair* pPair = m_pThis->m_mapSkin.GetNext(pos);

			if (pPair != NULL)
			{
				pSkinAttributes = new CSkinAttributes(pPair->m_key, pPair->m_value);

				IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(pNode, strKey);
				pSkinAttributes->Save(pChild, strKey);
			}
		}
	}
	else
	{
		pSkinAttributes = new CSkinAttributes();

		if (pSkinAttributes)
		{
			pSkinAttributes->Load(pNode, strKey);
			m_pThis->m_mapSkin.SetAt(pSkinAttributes->GetSkinName(), pSkinAttributes->GetSkinPath());
		}
	}
}

IMPLEMENT_SETTINGS_CALLBACK(CSkinSettings, Selected)
{
	if (bSave)
	{
		CSettingsTraits::SetStringValue(pNode, strKey, m_pThis->m_strSelected);
	}
	else
	{
		CSettingsTraits::GetStringValue(pNode, strKey, m_pThis->m_strSelected);
	}
}
