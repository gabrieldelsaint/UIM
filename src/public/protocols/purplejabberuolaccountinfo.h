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


#ifndef _PURPLE_JABBER_UOL_ACCOUNT_INFO_H_
#define _PURPLE_JABBER_UOL_ACCOUNT_INFO_H_

#include <blist.h>
#include <string>

#include "protocolsettings.h"


class CPurpleJabberUOLAccountInfo
{
public:
	CPurpleJabberUOLAccountInfo(const std::string& strUsername);
	virtual ~CPurpleJabberUOLAccountInfo();

	std::string GetUsername() const;

	void SetUserExtendedCapabilities(CProtocolSettings2* pExtendedCapabilities);
	CProtocolSettings2* GetUserExtendedCapabilities() const;

	void SetUserCurrentStatus(int nStatus);
	int  GetUserCurrentStatus() const;

	void SetUserCurrentStatusMessage(const std::string& strStatusMessage);
	std::string GetUserCurrentStatusMessage() const;

	void SetContactExtendedCapabilities(const std::string& strContact, CProtocolSettings2* pExtendedCapabilities);
	CProtocolSettings2* GetContactExtendedCapabilities(const std::string& strContact) const;

private:
	void ReleaseAll();

private:
	typedef std::map<std::string, CProtocolSettings2*> CProtocolSettingsMap;

	std::string				m_strUsername;
	std::string				m_strStatusMessage;
	int						m_nStatus;
	CProtocolSettings2*		m_pUserExtendedCapabilities;
	CProtocolSettingsMap	m_mapContactExtendedCapabilities;
};

#endif /* _PURPLE_JABBER_UOL_ACCOUNT_INFO_H_ */