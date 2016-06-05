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
#include "PluginProperties.h"


CPluginProperties::CPluginProperties(const CString& strPluginName) : 
		m_strPluginName(strPluginName)
{
}


CPluginProperties::~CPluginProperties()
{
	RemoveAllPluginProperties();
}


CString CPluginProperties::GetPluginName() const
{
	return m_strPluginName;
}


BOOL CPluginProperties::AddPluginProperty(
		const CString& strPropertyName, const CString& strPropertyValue)
{
	m_propertiesMap.SetAt(strPropertyName, strPropertyValue);
	
	return TRUE;
}


BOOL CPluginProperties::RemovePluginProperty(
		const CString& strPropertyName)
{
	if (m_propertiesMap.RemoveKey(strPropertyName) == true)
	{
		return TRUE;
	}
	
	return FALSE;
}


BOOL CPluginProperties::RemoveAllPluginProperties()
{
	m_propertiesMap.RemoveAll();
	
	return TRUE;
}


int CPluginProperties::GetPluginPropertiesCount()
{
	return m_propertiesMap.GetCount();
}


CString CPluginProperties::GetPluginPropertyName(int iIndex)
{
	CPropertiesMap::CPair* pPair = NULL;
	int index = 0;
	
	for (POSITION mapPos = m_propertiesMap.GetStartPosition(); mapPos; index++)
	{
		pPair = m_propertiesMap.GetNext(mapPos);
		
		if ( (pPair != NULL) && (index == iIndex) )
		{
			return pPair->m_key;
		}
	}
	
	return "";
}


CString CPluginProperties::GetPluginPropertyValue(CString strPropertyName)
{
	CPropertiesMap::CPair* pPair = m_propertiesMap.Lookup(strPropertyName);
	
	if (pPair != NULL)
	{
		return pPair->m_value;
	}
	
	return "";
}
