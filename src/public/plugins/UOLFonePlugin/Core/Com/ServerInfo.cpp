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
#include "ServerInfo.h"


CServerInfo::CServerInfo()
{
	//ATLTRACE(_T("%s\n"), __FUNCTION__);
}


CServerInfo::~CServerInfo()
{
	//ATLTRACE(_T("%s\n"), __FUNCTION__);
}


STDMETHODIMP CServerInfo::GetServerHost(BSTR* pbstrHost)
{
	if (pbstrHost != NULL)
	{
		*pbstrHost = GetHost().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CServerInfo::GetServerPort(LONG* plPort)
{
	if (plPort != NULL)
	{
		*plPort = GetPort();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CServerInfo::GetUsername(BSTR* pbstrUsername)
{
	if (pbstrUsername != NULL)
	{
		*pbstrUsername = GetUsername().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CServerInfo::GetPassword(BSTR* pbstrPassword)
{
	if (pbstrPassword != NULL)
	{
		*pbstrPassword = GetPassword().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CServerInfo::GetSipRealm(BSTR* pbstrSipRealm)
{
	if (pbstrSipRealm != NULL)
	{
		*pbstrSipRealm = GetSipRealm().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


void CServerInfo::SetHost(const CString& strHost)
{
	m_strHost = strHost;
}


void CServerInfo::SetPort(LONG lPort)
{
	m_lPort = lPort;
}


void CServerInfo::SetUsername(const CString& strUsername)
{
	m_strUsername = strUsername;
}


void CServerInfo::SetPassword(const CString& strPassword)
{
	m_strPassword = strPassword;
}


void CServerInfo::SetSipRealm(const CString& strSipRealm)
{
	m_strSipRealm = strSipRealm;
}


CString CServerInfo::GetHost()
{
	return m_strHost;
}


LONG CServerInfo::GetPort()
{
	return m_lPort;
}


CString CServerInfo::GetUsername()
{
	return m_strUsername;
}


CString CServerInfo::GetPassword()
{
	return m_strPassword;
}


CString CServerInfo::GetSipRealm()
{
	return m_strSipRealm;
}
