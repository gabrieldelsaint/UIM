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
#include "NetworkProxy.h"

#include <interfaces/IUOLMessengerNetworkSettings.h>
#include "SettingsTraits.h"


CNetworkProxy::CNetworkProxy() : 
	m_nProxyType(IUOLMessengerNetworkSettings::PT_PROXY_NONE),
	m_nProxyPort(-1)
{
	InitTagProcessMap();
}


CNetworkProxy::~CNetworkProxy()
{
}


int CNetworkProxy::GetProxyType()
{
	return m_nProxyType;
}


void CNetworkProxy::SetProxyType(int nType)
{
	m_nProxyType = nType;
}


CString CNetworkProxy::GetProxyHost()
{
	return m_strProxyHost;
}


void CNetworkProxy::SetProxyHost(const CString& strHost)
{
	m_strProxyHost = strHost;
}


int CNetworkProxy::GetProxyPort()
{
	return m_nProxyPort;
}


void CNetworkProxy::SetProxyPort(int nPort)
{
	m_nProxyPort = nPort;
}


CString CNetworkProxy::GetProxyUsername()
{
	return m_strProxyUsername;
}


void CNetworkProxy::SetProxyUsername(const CString& strUsername)
{
	m_strProxyUsername = strUsername;
}


CString CNetworkProxy::GetProxyPassword()
{
	return m_strProxyPassword;
}


void CNetworkProxy::SetProxyPassword(const CString& strPassword)
{
	m_strProxyPassword = strPassword;
}


void CNetworkProxy::InitTagProcessMap()
{
	init_helper ih[] = 
	{	
		{"Type", NEW_SETTINGS_CALLBACK(Type, this)},
		{"Host", NEW_SETTINGS_CALLBACK(Host, this)},
		{"Port", NEW_SETTINGS_CALLBACK(Port, this)},
		{"Username", NEW_SETTINGS_CALLBACK(Username, this)},
		{"Password", NEW_SETTINGS_CALLBACK(Password, this)}
	};

	int nSize = sizeof(ih) / sizeof(ih[0]);

	for (int nInd = 0; nInd < nSize; nInd++)
	{
		m_tagProcess[ih[nInd].str]= ih[nInd].pCallback;
	}
}


void CNetworkProxy::Load(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Load(pNode, m_tagProcess, this);
}


void CNetworkProxy::Save(MSXML::IXMLDOMNodePtr pNode, const CString& strKey)
{
	CSettingsTraits::Save(pNode, m_tagProcess, this);
}


IMPLEMENT_SETTINGS_CALLBACK(CNetworkProxy, Type)
{
	if (bSave)
	{
		CSettingsTraits::SetDWORDValue(pNode, strKey, (DWORD) m_pThis->m_nProxyType);
	}
	else
	{
		CSettingsTraits::GetDWORDValue(pNode, strKey, (DWORD&) m_pThis->m_nProxyType);
	}
}


IMPLEMENT_SETTINGS_CALLBACK(CNetworkProxy, Host)
{
	if (bSave)
	{
		CSettingsTraits::SetStringValue(pNode, strKey, (CString)m_pThis->m_strProxyHost);
	}
	else
	{
		CSettingsTraits::GetStringValue(pNode, strKey, (CString&)m_pThis->m_strProxyHost);
	}
}


IMPLEMENT_SETTINGS_CALLBACK(CNetworkProxy, Port)
{
	if (bSave)
	{
		CSettingsTraits::SetIntValue(pNode, strKey, m_pThis->m_nProxyPort);
	}
	else
	{
		CSettingsTraits::GetIntValue(pNode, strKey, m_pThis->m_nProxyPort);
	}
}


IMPLEMENT_SETTINGS_CALLBACK(CNetworkProxy, Username)
{
	if (bSave)
	{
		CSettingsTraits::SetStringValue(pNode, strKey, (CString)m_pThis->m_strProxyUsername);
	}
	else
	{
		CSettingsTraits::GetStringValue(pNode, strKey, (CString&)m_pThis->m_strProxyUsername);
	}
}


IMPLEMENT_SETTINGS_CALLBACK(CNetworkProxy, Password)
{
	if (bSave)
	{
		CSettingsTraits::SetStringValue(pNode, strKey, (CString)m_pThis->m_strProxyPassword);
	}
	else
	{
		CSettingsTraits::GetStringValue(pNode, strKey, (CString&)m_pThis->m_strProxyPassword);
	}
}