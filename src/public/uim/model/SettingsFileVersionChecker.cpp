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
#include "SettingsFileVersionChecker.h"

#include "SettingsTraits.h"
#include "../controller/SettingsManager.h"


CSettingsFileVersionChecker::CSettingsFileVersionChecker(const CString& strMainTag, const CString& strFilePath) : 
		m_userSettingsHandler(strFilePath, FALSE, FALSE)
{
	// Initialize settings processing map
	InitTagProcessMap();
	
	m_userSettingsHandler.AddSetting(strMainTag, this);
	
	m_bFileLoaded = m_userSettingsHandler.LoadSettings(FALSE);
}


CSettingsFileVersionChecker::~CSettingsFileVersionChecker()
{
}


BOOL CSettingsFileVersionChecker::GetFileLoaded()
{
	return m_bFileLoaded;
}


BOOL CSettingsFileVersionChecker::GetFileVersion(CString& strFileVersion)
{
	strFileVersion = m_strFileVersion;
	
	return m_bGotFileVersion;
}


void CSettingsFileVersionChecker::InitTagProcessMap()
{
	init_helper ih[] = 
	{	
		{"Version", NEW_SETTINGS_CALLBACK(Version, this)}
	};
	
	int nSize = sizeof(ih) / sizeof(ih[0]);
	
	for (int nInd = 0; nInd < nSize; nInd++)
	{
		ms_tagProcess[ih[nInd].str]= ih[nInd].pCallback;
	}
}


void CSettingsFileVersionChecker::Load(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Load(pNode, ms_tagProcess, this);
}


void CSettingsFileVersionChecker::Save(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Save(pNode, ms_tagProcess, this);
}


IMPLEMENT_SETTINGS_CALLBACK(CSettingsFileVersionChecker, Version)
{
	if (bSave)
	{
		CSettingsTraits::SetStringAttributeValue(pNode, strKey, m_pThis->m_strFileVersion);
	}
	else
	{
		m_pThis->m_bGotFileVersion = CSettingsTraits::GetStringAttibuteValue(
				pNode, strKey, m_pThis->m_strFileVersion);
	}
}

