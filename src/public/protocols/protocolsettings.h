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
 
#ifndef _PROTOCOL_SETTINGS_H_
#define _PROTOCOL_SETTINGS_H_

#include <string>
#include <map>
#include <list>


class CProtocolSettings
{
public:
	virtual ~CProtocolSettings();

	void SetInteger(const std::string& strSetting, int nValue);
	bool GetInteger(const std::string& strSetting, int& nValue) const;

	void SetString(const std::string& strSetting, const std::string& strValue);
	bool GetString(const std::string& strSetting, std::string& strValue) const;

	void SetBoolean(const std::string& strSetting, bool bValue);
	bool GetBoolean(const std::string& strSetting, bool& bValue) const;

protected:
	typedef std::map<std::string, int> CIntegerMap;
	typedef std::map<std::string, std::string> CStringMap;
	typedef std::map<std::string, bool> CBooleanMap;

	CIntegerMap		m_mapInteger;
	CStringMap		m_mapString;
	CBooleanMap		m_mapBoolean;
};


class CProtocolSettings2 : public CProtocolSettings
{
public:
	virtual ~CProtocolSettings2();

	CProtocolSettings2* Clone() const;
};


class CProtocolSettings3 : public CProtocolSettings2
{
public:
	
	typedef std::list<std::string>	CStringList;
	typedef std::list<int>			CIntegerList;
	typedef std::list<bool>			CBooleanList;
	
public:
	virtual ~CProtocolSettings3();
	
	void GetIntegerSettingsList(
			CStringList& settingList, CIntegerList& valueList);
	
	void GetStringSettingsList(
			CStringList& settingList, CStringList& valueList);
	
	void GetBooleanSettingsList(
			CStringList& settingList, CBooleanList& valueList);
};


#endif // _PROTOCOL_SETTINGS_H_
