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

#include "Settings.h"
#include "AccountSettingsProcessor.h"
#include "ContactListProcessor.h"
#include "MessageProcessor.h"
#include "StatusProcessor.h"
#include "SoundProcessor.h"
#include "SettingsTraits.h"

CSettings::CSettings()
{
}


CSettings::~CSettings()
{
}

CAccountSettings* CSettings::GetAccountSettings()
{
	return &m_accountSettings;
}

void CSettings::ProcessAccounts(MSXML::IXMLDOMNodePtr& pNode, const CString& strKey, BOOL bSave)
{
	CAccountSettingsProcessor accountSettingsProcessor(&m_accountSettings);

	if (bSave)
	{
		IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(pNode, strKey);
		accountSettingsProcessor.Save(pChild);
	}
	else
	{
		accountSettingsProcessor.Load(pNode);
	}
}

CContactListSettings* CSettings::GetContactListSettings()
{
	return &m_contactListSettings;
}

void CSettings::ProcessContactList(MSXML::IXMLDOMNodePtr& pNode, const CString& strKey, BOOL bSave)
{
	CContactListProcessor contactListProcessor(&m_contactListSettings);

	if (bSave)
	{
		IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(pNode, strKey);
		contactListProcessor.Save(pChild);
	}
	else
	{
		contactListProcessor.Load(pNode);
	}
}

CMessageSettings* CSettings::GetMessageSettings()
{
	return &m_messageSettings;
}

void CSettings::ProcessMessage(MSXML::IXMLDOMNodePtr& pNode, const CString& strKey, BOOL bSave)
{
	CMessageProcessor messageProcessor(&m_messageSettings);

	if (bSave)
	{
		IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(pNode, strKey);
		messageProcessor.Save(pChild);
	}
	else
	{
		messageProcessor.Load(pNode);
	}
}

CStatusSettings* CSettings::GetStatusSettings()
{
	return &m_statusSettings;
}

void CSettings::ProcessStatus(MSXML::IXMLDOMNodePtr& pNode, const CString& strKey, BOOL bSave)
{
	CStatusProcessor statusProcessor(&m_statusSettings);

	if (bSave)
	{
		IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(pNode, strKey);
		statusProcessor.Save(pChild);
	}
	else
	{
		statusProcessor.Load(pNode);
	}
}

CSoundSettings* CSettings::GetSoundSettings()
{
	return &m_soundSettings;
}

void CSettings::ProcessSound(MSXML::IXMLDOMNodePtr& pNode, const CString& strKey, BOOL bSave)
{
	CSoundProcessor soundProcessor(&m_soundSettings);

	if (bSave)
	{
		IXMLDOMNodePtr pChild = CSettingsTraits::OpenGroup(pNode, strKey);
		soundProcessor.Save(pChild);
	}
	else
	{
		soundProcessor.Load(pNode);
	}
}