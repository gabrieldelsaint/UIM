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

#include "IconSettings.h"
#include "SettingsTraits.h"

// CIconSettings
CIconSettings::CIconSettings() 
{
	InitTagProcessMap();
}

CIconSettings::~CIconSettings(void)
{
	CIconDestructor iconDestructor;
	m_tstEmoticons.SortStrings(iconDestructor);
}

void CIconSettings::InitTagProcessMap()
{
	init_helper ih[] = 
	{	
		{"Icon", NEW_SETTINGS_CALLBACK(Icon, this)}
	};

	int nSize = sizeof(ih) / sizeof(ih[0]);

	for (int nInd = 0; nInd < nSize; nInd++)
	{
		ms_tagProcess[ih[nInd].str]= ih[nInd].pCallback;
	}
}

void CIconSettings::Load(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Load(pNode, ms_tagProcess, this);
}

void CIconSettings::Save(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Save(pNode, ms_tagProcess, this);
}

CEmoticonPtr CIconSettings::GetIcon(const CString& strSymbol)
{
	CEmoticonPtr pIcon = *(CEmoticonPtr*)m_tstEmoticons.Match(strSymbol);

	if (pIcon)
	{
		return pIcon;
	}
	
	return CEmoticonPtr();
}

CTernarySearchTree* CIconSettings::GetIconSearchTree()
{
	return &m_tstEmoticons;
}

CIconWriter::CIconWriter(IXMLDOMNodePtr pNode, const CString& strKey) :
m_pNode(pNode), m_strKey(strKey)
{
}

CIconWriter::~CIconWriter()
{
}

void CIconWriter::Visit(LPCTSTR szItem, LPVOID lpVoid)
{
	CEmoticon* pIcon = (CEmoticon*)lpVoid;

	if (pIcon)
	{
		IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(m_pNode, m_strKey);
		pIcon->Save(pChild, m_strKey);
	}

}

CIconDestructor::CIconDestructor()
{
}

CIconDestructor::~CIconDestructor()
{
}

void CIconDestructor::Visit(LPCTSTR szItem, LPVOID lpVoid)
{
	CEmoticon* pIcon = (CEmoticon*)lpVoid;

	if (pIcon)
	{
		delete pIcon;
	}

}

IMPLEMENT_SETTINGS_CALLBACK(CIconSettings, Icon)
{
	CEmoticon* pIcon;
	CString		 strSymbol;

	if (bSave)
	{
		CIconWriter iconVisitor(pNode, strKey);
		m_pThis->m_tstEmoticons.SortStrings(iconVisitor);
	}
	else
	{
		// TODO set a real ID
		pIcon = new CEmoticon(0);

		if (pIcon)
		{
			strSymbol.Empty();
			pIcon->Load(pNode, strKey);

			strSymbol = pIcon->GetSymbol();
			strSymbol.Append("*");
			m_pThis->m_tstEmoticons.Insert(strSymbol, pIcon);
		}
	}
}
