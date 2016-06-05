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
#include "PhoneLineConfig.h"


CPhoneLineConfig::CPhoneLineConfig() : 
	m_lConnectionPort(DEFAULT_CONNECTION_PORT)
{
}


CPhoneLineConfig::~CPhoneLineConfig()
{
}


STDMETHODIMP CPhoneLineConfig::GetConnectionPort(LONG* plPort)
{
	HRESULT hr = E_POINTER;

	if (plPort)
	{
		*plPort = GetConnectionPort();
		hr = S_OK;
	}

	return hr;
}


STDMETHODIMP CPhoneLineConfig::GetServerNetworkConfig(IUOLFoneClientNetworkConfig** ppNetworkConfig)
{
	HRESULT hr = E_POINTER;

	if (ppNetworkConfig)
	{
		*ppNetworkConfig = m_spServerNetworkConfig;

		if (ppNetworkConfig)
		{
			(*ppNetworkConfig)->AddRef();
		}

		hr = S_OK;
	}

	return hr;
}


STDMETHODIMP CPhoneLineConfig::GetMediaNetworkConfig(IUOLFoneClientNetworkConfig** ppNetworkConfig)
{
	HRESULT hr = E_POINTER;

	if (ppNetworkConfig)
	{
		*ppNetworkConfig = m_spMediaNetworkConfig;

		if (ppNetworkConfig)
		{
			(*ppNetworkConfig)->AddRef();
		}

		hr = S_OK;
	}

	return hr;
}


STDMETHODIMP CPhoneLineConfig::GetAudioCodecsPrecedence(BSTR* pbstrAudioCodecsPrecedence)
{
	HRESULT hr = E_POINTER;

	if (pbstrAudioCodecsPrecedence)
	{
		*pbstrAudioCodecsPrecedence = GetAudioCodecsPrecedence().AllocSysString();
		hr = S_OK;
	}

	return hr;
}


STDMETHODIMP CPhoneLineConfig::GetVideoCodecsPrecedence(BSTR* pbstrVideoCodecsPrecedence)
{
	HRESULT hr = E_POINTER;

	if (pbstrVideoCodecsPrecedence)
	{
		*pbstrVideoCodecsPrecedence = GetVideoCodecsPrecedence().AllocSysString();
		hr = S_OK;
	}

	return hr;
}


void CPhoneLineConfig::SetConnectionPort(LONG lPort)
{
	m_lConnectionPort = lPort;
}


STDMETHODIMP CPhoneLineConfig::SetServerNetworkConfig(IUOLFoneClientNetworkConfig* pNetworkConfig)
{
	HRESULT hr = E_POINTER;

	if (pNetworkConfig)
	{
		m_spServerNetworkConfig = pNetworkConfig;
		hr = S_OK;
	}

	return hr;
}


STDMETHODIMP CPhoneLineConfig::SetMediaNetworkConfig(IUOLFoneClientNetworkConfig* pNetworkConfig)
{
	HRESULT hr = E_POINTER;

	if (pNetworkConfig)
	{
		m_spMediaNetworkConfig = pNetworkConfig;
		hr = S_OK;
	}

	return hr;
}


void CPhoneLineConfig::SetAudioCodecsPrecedence(const CString& strAudioCodecsPrecedence)
{
	m_strAudioCodecsPrecedence = strAudioCodecsPrecedence;
}


void CPhoneLineConfig::SetVideoCodecsPrecedence(const CString& strVideoCodecsPrecedence)
{
	m_strVideoCodecsPrecedence = strVideoCodecsPrecedence;
}


LONG CPhoneLineConfig::GetConnectionPort()
{
	return m_lConnectionPort;
}


CString CPhoneLineConfig::GetAudioCodecsPrecedence()
{
	return m_strAudioCodecsPrecedence;
}


CString CPhoneLineConfig::GetVideoCodecsPrecedence()
{
	return m_strVideoCodecsPrecedence;
}