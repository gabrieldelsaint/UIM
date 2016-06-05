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
#include "resource.h"
#include "CryptoPluginConfig.h"
#include "FacadeWrapper.h"

#define		LOG_MESSAGE_ENABLED			"LogMessageEnabled"


CCryptoPluginConfig::CCryptoPluginConfig(void) : 
		m_initialized(FALSE), 
		m_LogMessageEnabled(NULL),
		m_configLoaded(FALSE)
{
	if ( (!m_initialized) && Initialize() )
	{
		m_initialized = TRUE;
	}
}


CCryptoPluginConfig::~CCryptoPluginConfig(void)
{
	if (m_configLoaded)
	{
		SaveCryptoConfig();
	}
	
	if (m_LogMessageEnabled != NULL)
	{
		delete m_LogMessageEnabled;
		m_LogMessageEnabled = NULL;
	}
}


BOOL CCryptoPluginConfig::Initialize()
{
	BOOL result = FALSE;
	CString currentUserProfilePath;
	CString configFileStub;
	
	if (CFacadeWrapper::GetInstance()->GetCurrentUserProfilePath(currentUserProfilePath))
	{
		m_CryptoConfigFilePath.Format("%s%s", currentUserProfilePath, 
				"\\UOLCryptoPluginConfig.xml");
		
		if (PathFileExists(m_CryptoConfigFilePath))
		{
			result = m_CryptoPluginConfigDoc.Load(m_CryptoConfigFilePath);
		}
		else if ((result = CFacadeWrapper::GetInstance()->LoadConfigFileStub(
				MAKEINTRESOURCE(IDR_XML_CONFIG_STUB), configFileStub)) == TRUE)
		{
			if (m_CryptoPluginConfigDoc.LoadXML(configFileStub))
			{
				result = m_CryptoPluginConfigDoc.Save(m_CryptoConfigFilePath);
			}
		}
		
		if (result)
		{
			m_configLoaded = TRUE;
			
			CXmlNodeWrapper sourceNode(m_CryptoPluginConfigDoc.AsNode());
			
			m_LogMessageEnabled = new CXmlNodeWrapper(
					sourceNode.GetNode(LOG_MESSAGE_ENABLED));
			
			if ((m_LogMessageEnabled == NULL))
			{
				result = FALSE;
			}
		}
	}
	
	return result;
}


CCryptoPluginConfig* CCryptoPluginConfig::GetInstance()
{
	static CCryptoPluginConfig configInstance;
	
	return &configInstance;
}


BOOL CCryptoPluginConfig::IsLogMessageEnabled()
{
	if (!m_initialized)
	{
		return FALSE;
	}
	else
	{
		if (m_LogMessageEnabled->GetText().IsEmpty())
		{
			return FALSE; //Default value
		}
		else
		{
			return (m_LogMessageEnabled->GetText().Compare("1") == 0);
		}
	}
}


void CCryptoPluginConfig::SetLogMessageEnabled(BOOL bEnabled)
{
	if (!m_initialized)
	{
		return;
	}
	else
	{
		CString strEnabled;
		strEnabled.Format("%d", bEnabled);
		
		m_LogMessageEnabled->SetText(strEnabled);
	}
}


void CCryptoPluginConfig::SaveCryptoConfig()
{
	if (!m_initialized)
	{
		return;
	}
	else 
	{
		m_CryptoPluginConfigDoc.Save(m_CryptoConfigFilePath);
	}
}

