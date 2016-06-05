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
#include "UserInfo.h"


CUserInfo::CUserInfo()
{
	//ATLTRACE(_T("%s\n"), __FUNCTION__);
}


CUserInfo::~CUserInfo()
{
	//ATLTRACE(_T("%s\n"), __FUNCTION__);
}


STDMETHODIMP CUserInfo::GetDisplayName(BSTR* pbstrDisplayName)
{
	if (pbstrDisplayName != NULL)
	{
		*pbstrDisplayName = GetDisplayName().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CUserInfo::GetUsername(BSTR* pbstrUsername)
{
	if (pbstrUsername != NULL)
	{
		*pbstrUsername = GetUsername().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CUserInfo::GetIdentity(BSTR* pbstrIdentity)
{
	if (pbstrIdentity != NULL)
	{
		*pbstrIdentity = GetIdentify().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CUserInfo::GetPassword(BSTR* pbstrPassword)
{
	if (pbstrPassword != NULL)
	{
		*pbstrPassword = GetPassword().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CUserInfo::GetRealm(BSTR* pbstrRealm)
{
	if (pbstrRealm != NULL)
	{
		*pbstrRealm = GetRealm().AllocSysString();

		return S_OK;
	}

	return E_FAIL;
}


void CUserInfo::SetDisplayName(const CString& strDisplayName)
{
	m_strDisplayName = strDisplayName;
}


void CUserInfo::SetUsername(const CString& strUserName)
{
	m_strUsername = strUserName;
}


void CUserInfo::SetIdentify(const CString& strIdentity)
{
	m_strIdenytity = strIdentity;
}


void CUserInfo::SetPassword(const CString& strPassword)
{
	m_strPassword = strPassword;
}


void CUserInfo::SetRealm(const CString& strRealm)
{
	m_strRealm = strRealm;
}


CString CUserInfo::GetDisplayName()
{
	return m_strDisplayName;
}


CString CUserInfo::GetUsername()
{
	return m_strUsername;
}


CString CUserInfo::GetIdentify()
{
	return m_strIdenytity;
}


CString CUserInfo::GetPassword()
{
	return m_strPassword;
}


CString CUserInfo::GetRealm()
{
	return m_strRealm;
}